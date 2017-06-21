# cordova-plugin-uxinsdk
cordova-plugin-uxinsdk    
有信网络通话cordova插件     

###背景
由于公司业务需求，需要接入有信通话sdk，
有信没有cordova版本的插件，所以公司大牛自己封装了一下

###作者   
福州拼单网电子商务有限公司 技术总监：袁世安

###使用说明
npm install   

declare var uxin:any;
uxin.sdk.calling(tick, callPhone, success_callback, error_callback)
