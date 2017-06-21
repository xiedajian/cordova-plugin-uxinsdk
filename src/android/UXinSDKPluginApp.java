package com.ipvp.master.SDK;

import android.app.Application;
import android.content.Context;

import com.yx.api.USDKCommonManager;
import com.yx.api.dial.USDKIDialStateCallbackDefaultImpl;
import com.yx.api.dial.USDKIDialParam;
import com.yx.api.login.USDKLoginParam;
import com.yx.login.USDKIAppLoginCallback;

public class UXinSDKPluginApp extends Application {
	private static Context mContext; //设备上下文
	public static final String app_Id = "pr4q0sxo";
	public static final String app_Key = "7d7bd0a2b1a87cf15f68ce013807d81a75109845";

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		mContext = getApplicationContext();

		initUXin();
	}

	/*
	 * 获取context
	 */
	public static Context getContext() {
		return mContext;
	}

	/**
	 * 初始化有信平台的参数
	 */
	public static void initUXin() {
		// PluginResult mPlugin;
		// try {
		// 	// 注册app
		// 	USDKCommonManager.registerApp(this.cordova.getActivity(), appKey, appId);
		// 	mPlugin = new PluginResult(PluginResult.Status.OK, "Init UXin Succeed.");
		// } catch (Exception e) {
		// 	mPlugin = new PluginResult(PluginResult.Status.OK, "Init UXin Error." + e.getMessage());
		// }

		// mPlugin.setKeepCallback(true);
		// this.callback.sendPluginResult(mPlugin);

		// 环境模式（调试建议PUBLIC， 发版建议RELEASE）
		USDKCommonManager.build(USDKCommonManager.RELEASE);
		// 注册app
		USDKCommonManager.registerApp(mContext, app_Key, app_Id);
	}
}