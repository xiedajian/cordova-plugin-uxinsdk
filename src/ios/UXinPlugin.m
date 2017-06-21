#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>
#import "UXinSDK.h"
#import "UXinPlugin.h"

#define APP_ID  @"pr4q0sxo"
#define APP_KEY @"7d7bd0a2b1a87cf15f68ce013807d81a75109845"

@implementation UXinPlugin

/**
 * 初始化UXinSDK。
 */
- (void)initApp {
	
/*	[UXinSDK setLogToConsoleEnable:NO];*/
	[UXinSDK setDefaultCallingUIEnable:YES];
	
	[UXinSDK registerApp4FastAccessMode:APP_ID appKey:APP_KEY delegate:self];
    UXinSDKSetting *wbSetting = [[UXinSDKSetting alloc] init];
    wbSetting.isPlayRing = YES;
    wbSetting.isVibration = YES;
    [UXinSDK setSetting:wbSetting];
	
	/* 登陆UXinSDK平台
	[self loginUXin];
	*/
}

/**
 *  登陆UXinSDK平台
 */
- (void)signin:(CDVInvokedUrlCommand *)command {
	_callbackId = command.callbackId;
	_accountId = [command.arguments objectAtIndex:0];
	_callerPhone = [command.arguments objectAtIndex:1];
	
	if(self.isInitedApp != YES)
	{
		[self initApp];
		self.isInitedApp = YES;
	}

	[self loginUXin];
}

/**
 *  拨号UXinSDK平台
 */
- (void)calling:(CDVInvokedUrlCommand *)command {
	_callbackId = command.callbackId;
	__weak __typeof (self) weakSelf = self;
	NSString *nickName = [command.arguments objectAtIndex:0];
	NSString *callPhone = [command.arguments objectAtIndex:1];
	
	if (callPhone != nil && [callPhone length] > 0 && nickName != nil && [nickName length] > 0) {
        [UXinSDK callPhoneNumber:callPhone maxTime:120 isRecord:YES nickName:nickName callEventBlock:^(UXinSDKCallEvent event) {
            __strong __typeof (weakSelf) strongSelf = weakSelf;
            [strongSelf uxinSDKCallEvent:event];
        }];

		// [UXinSDK callPhoneNumber:callPhone isRecord:YES maxTime:120 nickName:nickName callEventBlock:^(UXinSDKCallEvent event) {
		// 	//当次通话当前的状态
		// 	NSLog(@"event = %d", (int) event);
		// 	CDVPluginResult *pResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"{\"event\":%d, \"msg\":\"%@\"}", (int) event, @"Calling Succeed.", nil]];
		// 	[pResult setKeepCallbackAsBool:YES];
		// 	[self.commandDelegate sendPluginResult:pResult callbackId:command.callbackId];
		// }];
	} else {
		CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Calling UXin Error."];
		[pluginResult setKeepCallbackAsBool:YES];
		[self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
	}
}

/**
 *  退出登陆UXinSDK平台
 */
- (void)signout:(CDVInvokedUrlCommand *)command {
	[UXinSDK logout];
}

/**
 * 重新登陆有信平台
 * */
- (void)loginUXin {
	NSLog(@"Token = %@, Caller = %@", _accountId, _callerPhone, nil);
	if (_accountId != nil && [_accountId length] > 0 && _callerPhone != nil && [_callerPhone length] > 0) {
		[UXinSDK loginWithAccountID:_accountId phoneNumber:_callerPhone nickName:nil headerUrl:nil ];
	}
}

/**
 * 在原生的View界面显示弹框信息
 * */
- (void)showmsg:(CDVInvokedUrlCommand *)command {
	NSString *title = [command.arguments objectAtIndex:0];
	NSString *msg = [command.arguments objectAtIndex:1];
	UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:msg delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
	[alertView show];
}

/**
 * SDK登录结果回调
 * */
- (void) uxinSDKLoginResult:(UXinSDKLoginResult)resultCode{
	NSString *resultStr = @"登陆状态：";
	switch (resultCode) {
		case UXinSDKLoginResult_Success: {
			resultStr = [NSString stringWithFormat:@"登陆成功. accountId=%@, phoneNumber=%@", _accountId, _callerPhone, nil];
		} break;
		case UXinSDKLoginResult_InvalidAccountID: {
			resultStr = [NSString stringWithFormat:@"无效的AccountId. accountId=%@, phoneNumber=%@", _accountId, _callerPhone, nil];
		} break;
		case UXinSDKLoginResult_InvalidPhoneNumber: {
			resultStr = [NSString stringWithFormat:@"无效的电话号码. accountId=%@, phoneNumber=%@", _accountId, _callerPhone, nil];
		} break;
		case UXinSDKLoginResult_CanNotGetToken: {
			resultStr = [NSString stringWithFormat:@"无法获取Token. accountId=%@, phoneNumber=%@", _accountId, _callerPhone, nil];
		} break;
	}
	NSLog(@"%@", resultStr);
	if(_callbackId != nil){
		CDVPluginResult *pResult;
		if( resultCode == UXinSDKLoginResult_Success) {
			pResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:resultStr];
		}
		else {
			pResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:resultStr];
		}
		[pResult setKeepCallbackAsBool:YES];
		[self.commandDelegate sendPluginResult:pResult callbackId:_callbackId];
	}
} 

/**
 * 当用户登陆成功之后，就会调用这个协议中的方法。(已作废)
 * */
- (void)uxinSDKstatus:(UXinSDKStatus)status {
	NSLog(@"status = %ld, callbackId = %@", (long) status, _callbackId);
	/*CDVInvokedUrlCommand *command = _contextCommand;*/
	if (status == UXinSDKStatusOnline) {
		NSLog(@"在线");
	} else {
		NSLog(@"离线");
	}
}

- (void)uxinSDKTokenInvalid {
	//实现这个协议方法并调用获取token然后登陆sdk
	[self loginUXin];
}

- (void)uxinSDKLimitHangup {
	//通话时长限制挂断，此时你们可以做你们需要做的事
	NSLog(@"通话已经被限制");
	if(_callbackId != nil){
		CDVPluginResult *pResult;
		pResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"通话已经被限制"];
		[pResult setKeepCallbackAsBool:YES];
		[self.commandDelegate sendPluginResult:pResult callbackId:_callbackId];
	}
}

- (void)uxinSDKCRM:(NSString *)CRMId CRMString:(void (^)(NSString *))block {
	//轻量crm功能
	//crmid是主叫手机号
	//拿着主叫手机号去你们服务器获取crm信息
	//获取之后调用block
	block(@"客满分客服关怀");
}

- (void)callEvent2String:(UXinSDKCallEvent)event {
	int code = 0;
	NSString *message = nil;
    switch (event) {
        case UXinSDKCallEventConnecting:
            code = 0;
			message = @"正在接通";
			break;
        case UXinSDKCallEventRinging:
			code = 1;
            message = @"正在响铃";
        case UXinSDKCallEventAnswerByCalled:
        case UXinSDKCallEventAnswerByCaller:
			code = 2;
            message = @"已接听";
			break;
        case UXinSDKCallEventReject:
			code = 3;
            message = @"已拒接";
			break;
        case UXinSDKCallEventHangupBySelf:
			code = 4;
            message = @"自己挂断";
			break;
        case UXinSDKCallEventHangupByOther:
			code = 5;
            message = @"对方已挂断";
			break;
        case UXinSDKCallEventHangupBySystem:
			code = 6;
            message = @"系统挂断";
			break;
        case UXinSDKCallEventHangupByLoginFailed:
			code = -1;
            message = @"登录失败";
			break;
        case UXinSDKCallEventInvalidParams:
			code = -1;
            message = @"拨打参数错误";
			break;
        case UXinSDKCallEventCallbackFailed:
			code = -1;
            message = @"回拨失败";
			break;
        case UXinSDKCallEventCallbackSuccess:
			code = -2;
            message = @"回拨成功";
			break;
        case UXinSDKCallEventNoCustomUIPermission:
			code = -1;
            message = @"无自定义UI权限";
			break;
        default:
			code = -1;
            message = [NSString stringWithFormat:@"错误码 = %@", @(event)];
            break;
    }
	if(code==-2) return;
	if (message && message.length > 0) {
		NSLog(@"event = %d, reason = %@", (int)event, message); //当次通话当前的状态
		CDVPluginResult *pResult = nil;
		if(code==-1)
			pResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[NSString stringWithFormat:@"%@(%d))", message, (int) event, nil]];
		else
			pResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"{\"event\":%d, \"msg\":\"%@\"}", (int) event, @"Calling Succeed.", nil]];

		[pResult setKeepCallbackAsBool:YES];
		[self.commandDelegate sendPluginResult:pResult callbackId:_callbackId];
    }
	return;
}

- (void)uxinSDKCallEvent:(UXinSDKCallEvent)event {
    NSLog(@"uxinSDKCallEvent = %d", (int)event);
    [self callEvent2String:event];
}

@end
