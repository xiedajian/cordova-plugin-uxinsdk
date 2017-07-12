# cordova-plugin-uxinsdk

# 有信网络通话cordova插件     

### 背景
由于公司业务需求，需要接入有信通话sdk，
有信没有cordova版本的插件，所以公司大牛自己封装了一下

### 作者   
福州拼单网电子商务有限公司 技术总监：袁世安

### 使用说明
1.安装插件    

```  
ionic cordova plugin add cordova-plugin-uxinsdk    
```
2.在platforms\android\AndroidManifest.xml文件中加入android:name="com.ipvp.master.SDK.UXinSDKPluginApp"    

```
 <application android:hardwareAccelerated="true" android:icon="@mipmap/icon" android:label="@string/app_name" android:name="com.ipvp.master.SDK.UXinSDKPluginApp" android:supportsRtl="true">

```

3.使用
```
declare var uxin:any;   


let account_id = "3_1512_18073118015";
//登陆
uxin.sdk.signIn(account_id, callPhone, success_callback, error_callback)

//呼叫
uxin.sdk.calling(tick, callPhone, success_callback, error_callback)
```

 


