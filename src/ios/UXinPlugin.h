#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>
#import "UXinSDK.h"

@interface UXinPlugin : CDVPlugin <UXinSDKDelegate>

/**
 *  登陆UXinSDK平台
 */
- (void)signin:(CDVInvokedUrlCommand *)command;

/**
 * （登陆UXIN平台及拨号
 */
- (void)calling:(CDVInvokedUrlCommand *)command;
/**
 *  登陆UXinSDK平台
 */
- (void)signout:(CDVInvokedUrlCommand *)command;

/**
 * 在原生的View界面显示信息
 * */
- (void)showmsg:(CDVInvokedUrlCommand *)command;

/**
 * 登陆失效时，自动登陆系统
 */
- (void)loginUXin;


/**
 * 当前上下文的参数对象
 * */
@property(nonatomic, assign) BOOL isInitedApp;

/**
 * 当前上下文的参数对象
 * */
@property(nonatomic, copy) NSString *callbackId;
/**
 * 登用的Token信息
 * */
@property(nonatomic, copy) NSString *accountId;
/**
 * 主叫电话号码
 * */
@property(nonatomic, copy) NSString *callerPhone;

@end
