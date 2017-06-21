package com.ipvp.master.SDK;

/*import com.ipvp.master.SDK.UXinSDKPluginApp;*/

import android.util.Log;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.yx.api.USDKCommonManager;
import com.yx.api.crm.USDKCrmNoticeImplDefault;
import com.yx.api.dial.USDKIDialParam;
import com.yx.api.dial.USDKIDialStateCallbackDefaultImpl;
import com.yx.api.login.USDKLoginParam;
import com.yx.crm.USDKCrmAppCallback;
import com.yx.crm.USDKCrmAppCallbackData;
import com.yx.crm.USDKCrmNoticeData;
import com.yx.common.interfaces.USDKCallBack;
import com.yx.common.net.interfaces.IUSDKHttpCallback;
import com.yx.login.USDKIAppLoginCallback;
import com.yx.test.USDKTest;
import com.yx.ytx.call.dial.USDKOnIncomingCustomizedParam;
import com.yx.ytx.call.dial.interfaces.USDKOnDialEventCustomiedListener;

import java.lang.Override;
import java.lang.String;

/**
 * This class echoes a string called from JavaScript.
 */
public class uxinsdk extends CordovaPlugin {
    private static Activity cordovaActivity;
	private static boolean isInited = false;
	private static uxinsdk instance;
	private static String account_Id;
	private static String caller_Phone;
	private CallbackContext callback;

    public static String TAG = "TAG_USDK";

    public uxinsdk() {
        instance = this;
    }

	@Override
	public void initialize(CordovaInterface cordova, CordovaWebView webView) {
		super.initialize(cordova, webView);
		// your init code here
        Log.i(TAG, "初始化Plugin.");

        cordovaActivity = cordova.getActivity();
	}

    @Override
    public void onDestroy() {
        super.onDestroy();
        cordovaActivity = null;
        instance = null;
    }
	/**
	 * 执行Cordova中的Js请求。
	 */
	@Override
	public boolean execute(String action, JSONArray args, final CallbackContext callbackContext) throws JSONException {
		this.callback = callbackContext;
		/**
		 * 其实没有必要调用这个方法获取这个Token 这个Token可以从我们自己的服务器端获取，我们的服务器端会自动帮我们去有信服务器注册
		 * 而我们只要在Ionic里调用我们自己的服务接口，从而不用该方法处理
		 */
		if ("signin".equals(action)) {
			// 保存登陆参数
			account_Id = args.getString(0);
			caller_Phone = args.getString(1);
			//initUXin();
			loginUXinSDK();
			return true;
		} else if ("calling".equals(action)) {
			this.dialogUXinPhone(args.getString(0), args.getString(1));
			return true;
		} else if ("signout".equals(action)) {
			logoutUxinSDK();
			return true;
		} else if ("showmsg".equals(action)) {
			String title = args.getString(0);
			String msg = args.getString(1);
			this.showMsg(title, msg);
			return true;
		}
		return false;
	}

	/**
	 * 登陆UXinSDK
	 */
	private void loginUXinSDK() {
		boolean isLogin = USDKCommonManager.isloginUxinSDK();
		final Context context = this.cordova.getActivity();

		if(isLogin && USDKCommonManager.getAccountId(context) != account_Id) {
			USDKCommonManager.logoutUxinSDK(context);
			isLogin = false;
		}

		if (!isLogin) {
			USDKLoginParam loginParam = new USDKLoginParam();
			loginParam.accountId = account_Id;
			loginParam.phone = caller_Phone;

			USDKCommonManager.loginUxinSDK(context, loginParam, new USDKIAppLoginCallback() {
				@Override
				public void onSuccess(Object result) {
					PluginResult mPlugin = new PluginResult(PluginResult.Status.OK, "Login UXinSDK Succeed.");
					mPlugin.setKeepCallback(true);
					uxinsdk.this.callback.sendPluginResult(mPlugin);
				}

				@Override
				public void onFailed(Object result) {
					PluginResult mPlugin = new PluginResult(PluginResult.Status.ERROR, "Login UXinSDK Faild.");
					mPlugin.setKeepCallback(true);
					uxinsdk.this.callback.sendPluginResult(mPlugin);
				}
			});
		}
	}

	/**
	 * 拨打语音
	 **/
	private void dialogUXinPhone(String calledNickName, String calledPhone) {
		USDKIDialParam param = new USDKIDialParam();
		param.setCalledPhone(calledPhone);
		param.setNeedRecord(true);
		param.setLimitTalkTime(120);
		param.setCalledNickName(calledNickName);
		USDKCommonManager.dialPhoneByUxinSDK(cordovaActivity, param, new USDKIDialStateCallbackDefaultImpl() {
			@Override
			public void onConnecting(int code, String data) {
				/*Toast.makeText(ct, "正在接通 code=" + code + "  data=" + data, Toast.LENGTH_LONG).show();*/

				PluginResult mPlugin = new PluginResult(PluginResult.Status.OK, String.format("{\"event\": 0, \"msg\":\"%s(%d)\"}", data, code));
				mPlugin.setKeepCallback(true);
				uxinsdk.this.callback.sendPluginResult(mPlugin);
			}

			@Override
			public void onRing(int code, String data) {
				//Toast.makeText(ct, "对方响铃 code=" + code + "  data=" + data, Toast.LENGTH_LONG).show();
				PluginResult mPlugin = new PluginResult(PluginResult.Status.OK, String.format("{\"event\": 1, \"msg\":\"%s(%d)\"}", data, code));
				mPlugin.setKeepCallback(true);
				uxinsdk.this.callback.sendPluginResult(mPlugin);
			}

			@Override
			public void onTalking(int code, String data) {
				//Toast.makeText(ct, "对方接通 code=" + code + "  data=" + data, Toast.LENGTH_LONG).show();
				PluginResult mPlugin = new PluginResult(PluginResult.Status.OK, String.format("{\"event\": 2, \"msg\":\"%s(%d)\"}", data, code));
				mPlugin.setKeepCallback(true);
				uxinsdk.this.callback.sendPluginResult(mPlugin);
			}

			@Override
			public void onHangUp(final int code, final String data) {
				//Toast.makeText(ct, "挂断 code=" + code + "  data=" + data, Toast.LENGTH_LONG).show();
				int event = 6;
				if (code == 98) event = 3;
				if (code == 30) event = 4;
				if (code == 31) event = 5;
				PluginResult mPlugin = new PluginResult(PluginResult.Status.OK, String.format("{\"event\": %d, \"msg\":\"%s(%d)\"}", event, data, code));
				mPlugin.setKeepCallback(true);
				uxinsdk.this.callback.sendPluginResult(mPlugin);
			}

			@Override
			public void onFail(final int code, final String data) {
				//Toast.makeText(ct, "拨打失败 code=" + code + "  msg=" + data, Toast.LENGTH_LONG).show();
				PluginResult mPlugin = new PluginResult(PluginResult.Status.ERROR, String.format("%s(%d)", data, code));
				mPlugin.setKeepCallback(true);
				uxinsdk.this.callback.sendPluginResult(mPlugin);
			}
		});
	}

	/**
	 * 登陆有信平台
	 *
	 * @Param callerPhone 主叫号码
	 * @Param callbackContext 调用的上下文
	 */
	private void logoutUxinSDK() {
		final Context ct = cordovaActivity;
		USDKCommonManager.logoutUxinSDK(ct);
	}

	/**
	 * 显示信息弹框
	 *
	 * @param msg 显示的内容
	 * @Param title 标题
	 */
	private void showMsg(String title, String msg) {
		final Context ct = cordovaActivity;
		Toast.makeText(ct, msg, Toast.LENGTH_LONG).show();
	}
}
