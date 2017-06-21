var exec = require('cordova/exec');
var uxinSdk = function () {
};
/**
 * 登陆到有信平台
 * accountId：第三方平台的账号Id
 * callerPhone: 主叫者的手机号码
 *
 * success: 执行成功时的回调
 * error: 执行过程出错时的回调
 * */
uxinSdk.prototype.signIn = function (account_id, callerPhone, success, error) {
	exec(success, error, "uxinsdk", "signin", [account_id, callerPhone]);
};
/**
 * 呼叫客户的电话
 * nickName: 呼出时,显示的客户的称呼
 * callPhone: 客户的电话号码
 *
 * success: 执行成功时的回调
 * error: 执行过程出错时的回调
 * */
uxinSdk.prototype.calling = function (nickName, callPhone, success, error) {
	exec(success, error, "uxinsdk", "calling", [nickName, callPhone]);
};
/**
 * 注销登陆（更换登陆用户时,需要先退出登陆）
 *
 * */
uxinSdk.prototype.signOut = function () {
	exec(null, null, "uxinsdk", "signout", null);
};
/**
 * 原生的弹框函数
 * title: 显示的标题
 * msg: 显示的内容主题
 *
 * success: 执行成功时的回调
 * error: 执行过程出错时的回调
 * */
uxinSdk.prototype.showMsg = function (title, msg, success, error) {
	exec(success, error, "uxinsdk", "showmsg", [title, msg]);
};

/**
 * 扩展插件
 * */
module.exports = new uxinSdk();
