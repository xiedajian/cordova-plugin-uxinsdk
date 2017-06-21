//
//  UXinSDK.h
//  UXinSDK
//
//  Created by Shaun on 16/2/25.
//  Copyright (c) 2016年 UXIN.COM All rights reserved.

#import <Foundation/Foundation.h>

/**
 *  UXinSDK连接状态
 */
typedef NS_ENUM(NSInteger, UXinSDKStatus) {
    /**
     *  离线
     */
    UXinSDKStatusOffline = 0,
    /**
     *  在线
     */
    UXinSDKStatusOnline = 1,
};

/**
 *  UXinSDK登录模式
 */
typedef NS_ENUM(NSInteger, UXinSDKLoginMode) {
    /**
     *  客户端短信验证方式（手机号、验证码登录）
     */
    UXinSDKLoginModeLocalSMSCodeLogin   = 0,
    /**
     *  服务器验证方式（第三方app<－>第三方服务端<－>有信服务端登录）
     */
    UXinSDKLoginModeRemoteLogin         = 1,
    /**
     *  快速接入验证方式(推荐)(第三方app调用接口直接登录)
     */
    UXinSDKLoginModeFastAccess          = 2
};

/**
 *  UXinSDK登录错误码
 */
typedef NS_ENUM(NSInteger, UXinSDKLoginResult) {
    /**
     *  登录成功
     */
    UXinSDKLoginResult_Success              = 0,
    /**
     *  登录失败，原因：非法的账号ID
     */
    UXinSDKLoginResult_InvalidAccountID     = 1,
    /**
     *  登录失败，原因：非法的手机号码
     */
    UXinSDKLoginResult_InvalidPhoneNumber   = 2,
    /**
     *  登录失败，原因：无法获取token
     */
    UXinSDKLoginResult_CanNotGetToken       = 3
};

/**
 *  有信通话时间（单位分钟）
 */
typedef NS_ENUM(int16_t, UXinSDKCallTime) {
    /**
     *  限制拨打，如果开发者想限制用户通话，传0即可
     */
    UXinSDKCallTimeLimit = 0,
    /**
     *  单通电话最大通话时长
     */
    UXinSDKCallTimeMax = INT16_MAX,
};

/**
 *  主叫拨号通话事件
 */
typedef NS_ENUM(NSInteger, UXinSDKCallEvent) {
    /**
     *  正在接通
     */
    UXinSDKCallEventConnecting          = 0,
    /**
     *  正在响铃
     */
    UXinSDKCallEventRinging             = 1,
    /**
     *  已接听(主叫)
     */
    UXinSDKCallEventAnswerByCaller      = 2,
    /**
     *  已接听(被叫)
     */
    UXinSDKCallEventAnswerByCalled      = 3,
    /**
     *  对方拒接
     */
    UXinSDKCallEventReject              = 4,
    /**
     *  接通后自己挂断
     */
    UXinSDKCallEventHangupBySelf        = 5,
    /**
     *  通话结束(异常挂断)
     */
    UXinSDKCallEventCallFinished        = 6,
    /**
     *  接通后对方挂断
     */
    UXinSDKCallEventHangupByOther       = 7,
    /**
     *  系统挂断
     */
    UXinSDKCallEventHangupBySystem      = 8,
    /**
     *  登录失败后挂断
     */
    UXinSDKCallEventHangupByLoginFailed = 9,
    /**
     *  拨打失败，参数错误
     */
    UXinSDKCallEventInvalidParams       = 10,
    /**
     *  拨打失败，函数调用错误,即打开自定义开关后调用默认UI的拨打电话方法或使用默认UI的情况下调用自定义UI的拨打方法
     */
    UXinSDKCallEventInvalidFunctionCall = 11,
    /**
     *  拨打失败，没有可用网络(默认UI下会直接调用拨打系统电话)
     */
    UXinSDKCallEventNotAvailableNetwork = 12,
    /**
     *  2G网络下拨打失败
     */
    UXinSDKCallEventFailedBy2GNet       = 13,
    /**
     *  拨打失败，未登录
     */
    UXinSDKCallEventFailedNotLoggedIn   = 14,
    /**
     *  拨打失败，未知错误
     */
    UXinSDKCallEventUnknownFailed       = 15,
    /**
     *  拨打失败，无自定义UI的权限下调用自定义UI的拨打接口
     */
    UXinSDKCallEventNoCustomUIPermission= 16,
    /**
     *  本地网络波动
     */
    UXinSDKCallEventLocalNetPoor        = 17,
    /**
     *  对方网络波动
     */
    UXinSDKCallEventOthersideNetPoor    = 18,
    /**
     *  回拨成功
     */
    UXinSDKCallEventCallbackSuccess     = 19,
    /**
     *  回拨失败
     */
    UXinSDKCallEventCallbackFailed      = 20
};

/**
 *  更新用户信息返回值
 */
typedef NS_ENUM(NSInteger, UXinUpdateUserInfoResult) {
    /**
     *  更新用户信息成功
     */
    UXinUpdateUserInfoSuccess                   = 0,
    /**
     *  更新用户信息失败---没有传入账号ID
     */
    UXinUpdateUserInfoFailed_NoAccountID        = 1,
    /**
     *  更新用户信息失败---没有传入有效信息：昵称或头像地址
     */
    UXinUpdateUserInfoFailed_NoInfoToUpdate     = 2,
    /**
     *  更新用户信息失败---昵称非法(超过长度，含有表情或特殊字符等)
     */
    UXinUpdateUserInfoFailed_InvalidNickname    = 3,
    /**
     *  更新用户信息失败
     */
    UXinUpdateUserInfoFailed
};

/// 有信通话事件回调代理
@protocol UXinCallEventDelegate <NSObject>

@required

/**
 通话中电话事件回调
 
 @param event 事件类型
 */
- (void)onUXinCallEventNotify:(UXinSDKCallEvent)event;

/**
 *  来电回调
 @param phone 来电号码
 */
- (void)onUXinIncomingCallWithPhoneNumber:(NSString*)phone;

@optional

/**
 *  更新通话时长
 */
- (void)onUXinCallUpdateCallDuration:(NSString*)callDuration;

/**
 *  更新用户昵称
 */
- (void)onUXinCallUpdateNickname:(NSString*)nickname;

/** 
 *  更新用户头像
 */
- (void)onUXinCallUpdateHeaderUrl:(NSString*)urlString;


@end

/**
 *  UXinSDK设置
 */
@interface UXinSDKSetting : NSObject

/**
 *  是否震动
 */
@property (nonatomic, assign) BOOL isVibration;

/**
 *  是否播放铃声
 */
@property (nonatomic, assign) BOOL isPlayRing;

@end

/**
 *  UXinSDKDelegate
 */
@protocol UXinSDKDelegate <NSObject>

@optional

/**
 *  SDK连接状态
 *
 *  @param status 见UXinSDKStatus
 */
- (void)uxinSDKstatus:(UXinSDKStatus)status;

/**
 *  token失效或者token不正确，或者没有token。
 *  服务器验证方式（2）下用户可以根据此回调方法来重新获取token，然后登录有信服务器
 *  客户端短信验证和快速接入方式下会自动再次更新token，如更新失败，则需要用户输入手机号验证在次验证登录
 */
- (void)uxinSDKTokenInvalid;

/**
 *  SDK登录结果回调
 *
 *  @param resultCode 见UXinSDKLoginResult
 */
- (void)uxinSDKLoginResult:(UXinSDKLoginResult)resultCode;

/**
 *  被踢断开连接
 */
- (void)uxinSDKBeKicked;

/**
 *  通话被限制挂断(当开发者对电话时长有限制时，传入了maxtime，当时间到了，电话会被系统自动挂断，此时会回调此方法，开发者可以根据自己的需求去实现定制化的逻辑和页面)
 */
- (void)uxinSDKLimitHangup;

/**
 *  轻量CRM
 *
 *  开发者拿到此CRMId去开发者服务端查询对应的crm信息，然后通过block(CRMString)传入给sdk，sdk进行展示.
 *  CRM信息由开发者自行维护上下文，sdk只做展示
 *
 *  @param CRMId crmid 目前的crmid是主叫手机号
 *  @param block 开发者调用block(CRMString)把crm值传入SDK
 *  @notice CRMString支持部分html标签
    支持的html标签有：
     b标签
     font标签
     i标签
     u标签
 */
- (void)uxinSDKCRM:(NSString*)CRMId CRMString:(void (^)(NSString *CRMString))block;

@end

/**
 *
 *  UXinSDK提供打OTT电话和直拨电话功能，可以作为主叫，也可以作为被叫
 *  名次解释:
 *  OTT电话:UXinSDK拨打UXinSDK、UXin客户端
 *  直拨电话:UXinSDK拨打运营商电话
 */
@interface UXinSDK : NSObject

/**
 *  添加设置
 */
+ (void)setSetting:(UXinSDKSetting*)setting;

/**
 *  是否打印日志到控制台,默认=NO
 */
+ (void)setLogToConsoleEnable:(BOOL)enable;

/**
 *  获取是否打印日志到控制台,默认=NO
 */
+ (BOOL)getLogToConsoleEnable;

/**
 *  是否打印日志到文件,默认=NO,默认路径在/Library/Caches/UX_SDK_Logs
 */
+ (void)setLogToFileEnable:(BOOL)enable;

/**
 *  获取是否打印日志到文件,默认=NO
 */
+ (BOOL)getLogToFileEnable;

/**
 *  是否使用有信的默认通话UI,默认=YES
 */
+ (void)setDefaultCallingUIEnable:(BOOL)enable;

/**
 *  获取是否启用有信的默认通话UI,默认=YES
 */
+ (BOOL)getDefaultCallingUIEnable;

/**
 *  添加一个通话代理接收通话事件
 */
+ (void)addCallEventDelegate:(id<UXinCallEventDelegate>)aDelegate;

/**
 *  移除一个通话代理
 */
+ (void)removeCallEventDelegate:(id<UXinCallEventDelegate>)aDelegate;


/**
 *  拨打电话（通话状态通过UXinCallEventDelegate回调通知）
 *  默认是智能呼叫，不录音，不限时。
 
 *  @param strPhoneNumber 被叫号码
 *
 *  @return 调用是否成功
 *  正常返回YES,失败的话返回NO。
    ＃在没有数据网络的情况下，会调用用户系统电话拨打电话，结果返回YES。
    失败则需
    1.检查被叫号码是否正确；
    2.是否调用过registerApp:方法来初始化sdk；
    3.是否设置了使用自定义UI但未实现自定义的UI；
 
    如果调用失败，被叫手机号是正常的，再次登录上有信服务器后，会自动拨打上次未拨打出去的电话
 */
+ (BOOL)callPhoneNumber:(NSString*)strPhoneNumber;

/**
 *  拨打电话（通话时长）(通话状态通过UXinCallEventDelegate回调通知）
 *  不录音，增加通话时长选项。
 *  @param strPhoneNumber 被叫号码
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumber:(NSString*)strPhoneNumber
                maxTime:(UXinSDKCallTime)maxTime;

/**
 *  拨打电话（录音开关、通话时长，带通话状态回调）
 *
 *  @param strPhoneNumber 被叫号码
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *  @param isRecord       是否需要录音
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumber:(NSString *)strPhoneNumber
                maxTime:(UXinSDKCallTime)maxTime
               isRecord:(BOOL)isRecord
         callEventBlock:(void (^)(UXinSDKCallEvent event))callEventBlock;

/**
 *  拨打电话（传入默认昵称,带通话状态回调）
 *
 *  @param strPhoneNumber 被叫号码
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *  @param isRecord       是否录音
 *  @param callEventBlock 通话状态回调
 *  @param nickName       默认昵称
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumber:(NSString *)strPhoneNumber
                maxTime:(UXinSDKCallTime)maxTime
               isRecord:(BOOL)isRecord
               nickName:(NSString *)nickName
         callEventBlock:(void (^)(UXinSDKCallEvent event))callEventBlock;

/**
 *  自定义UI的拨打电话方法（传入默认昵称,通话状态回调通过代理回调出去）
 *
 *  @param strPhoneNumber 被叫号码
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *  @param isRecord       是否录音
 *  @param nickName       默认昵称
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumberByCustomUI:(NSString*)strPhoneNumber
                          maxTime:(UXinSDKCallTime)maxTime
                         isRecord:(BOOL)isRecord
                         nickName:(NSString*)nickName;

/**
 *  回拨电话接口（建议在弱网环境下使用回拨，强网环境使用ott＋直播）
 *
 *  @param phone  被叫号码
 *  @param mt     最大分钟数
 *  @param record 是否录音
 */
+ (void)callbackPhoneNumber:(NSString*)phone
                    maxtime:(UXinSDKCallTime)maxtime
                   isRecord:(BOOL)record;

/**
 *  SDK版本
 *
 *  @return versionString
 */
+ (NSString *)sdkVersion;

/**
 *  在AppStore中下载有信
 */
+ (void)toAppStoreForUxin;

/**
 *  当前登录状态，online可以直接拨打电话，offline说明没有登录
 */
+ (UXinSDKStatus)currentLoginStatus;

/**
 *  当前登录模式
 */
+ (UXinSDKLoginMode)currentLoginMode;

/**
 *  注销当前用户(清除缓存并且断开连接)
    第三方开发者注销账户使用
 */
+ (void)logout;

/**
 *  更新商家专号
 *  此操作需要先调用registerApp初始化sdk
 *  @return 接口调用是否成功
 */
+ (BOOL)updateVipContacts;


@end

@interface UXinSDK (UXinCallInterface)

/**
 *  挂断当前通话
 */
+ (void)hungUpCall;

/**
 *  拒绝当前来电
 */
+ (void)rejectCall;

/**
 *  接听当前电话
 */
+ (void)answerCall;

/**
 *  发送DTMF
 *
 *  @param cDigit '0'~'9','*','#'
 */
+ (void)sendDTMF:(char)cDigit;

/**
 *  设置是否静音麦克风
 *
 *  @param on NO:关闭静音 YES:打开静音
 */
+ (void)setMute:(BOOL)on;

/**
 *  设置是否启用扬声器输出声音
 *
 *  @param enable NO:关闭扬声器 YES:打开扬声器
 */
+ (void)setLoudspeakerEnable:(BOOL)enable;

/**
 *  播放正在呼出的声音(通过听筒播放)
 */
+ (void)playCallDialingSound;

/**
 *  停止播放正在呼出的声音
 */
+ (void)stopPlayCallDialingSound;

/**
 *  播放来电铃声(通过喇叭播放)
 */
+ (void)playIncomingCallRingtone;

/**
 *  停止播放来电铃声
 */
+ (void)stopPlayIncomingCallRingtone;


@end


@interface UXinSDK (SMSCodeMode)

/**
 *  传入APP KEY,APP ID等信息初始化SDK
 */
+ (BOOL)registerApp4SMSCodeMode:(NSString*)appID appKey:(NSString*)appKey delegate:(id<UXinSDKDelegate>)delegate;

/**
 *  短信验证码登录方式：显示登录页面
 */
+ (void)showLoginUI;

@end

/**
 *  服务器验证方式
 *  正常调用步骤：
 1.调用registerApp4RemoteMode，
 2.实现协议方法uxinSDKTokenInvalid
 3.在uxinSDKTokenInvalid方法里面调用开发者服务器接口获取token，
 4.获取成功后调用loginWith:(NSString*)phoneNumber token:(NSString*)token
 5.在需要拨打电话的地方根据需要调用callPhoneNumber
 */
@interface UXinSDK (RemoteMode)

/**
 *  服务器验证方式 初始化uxinsdk
 *  此方法用来服务器验证方式初始化
 */
+ (BOOL)registerApp4RemoteMode:(NSString*)appID appKey:(NSString*)appKey delegate:(id<UXinSDKDelegate>)delegate;

/**
 *  登录有信服务器（服务器验证方式使用）
 *  用户先调用用户服务器，用户服务器调用有信服务器来获取token，把获取到的token和手机号带入sdk登录有信服务器
 此方法异步登录SDK服务器
 *  @param phoneNumber 主叫号码(如果走显号路线，必须传真实手机号码，否则拨打不了电话)
 *  @param token       主叫token（必填）
 */
+ (BOOL)loginWith:(NSString*)phoneNumber token:(NSString*)token;

@end

/**
 *  快速接入验证方式（推荐）
 *  正常调用步骤：
    1.调用registerApp进行注册；
    2.实现协议方法uxinSDKLoginResult, 登录结果会回调此函数传出；
    3.调用loginWithAccountID: phoneNumber: nickName: headerUrl:传入账号、手机号、昵称、头像URL进行账号登录验证；
    4.调用setDefaultCallingUIEnable设置是否使用默认UI(若不调用则是使用默认UI)；
    5.实现UXinCallEventDelegate来接收电话事件回调；
    6.调用callPhoneNumber:系列函数来拨打电话；
 */
@interface UXinSDK (FastAccessLoginMode)

/**
 *  快速接入验证方式（推荐） 初始化uxinsdk
 *  此方法用来快速接入验证方式（推荐）初始化
 */
+ (BOOL)registerApp4FastAccessMode:(NSString*)appID appKey:(NSString*)appKey delegate:(id<UXinSDKDelegate>)delegate;

/**
 *  用账号和手机号来登录有信服务器（推荐）

 *  @param account     第三方账号
 *  @param phoneNumber 手机号码
 *  @param nickName    用户昵称(非必要,不能带emoji表情，最长10个字符)
 *  @param urlString   用户头像地址URL(非必要)
 */
+ (void)loginWithAccountID:(NSString*)account
               phoneNumber:(NSString*)phoneNumber
                  nickName:(NSString*)nickName
                 headerUrl:(NSString*)urlString;


/**
 *  更新有信服务器的用户信息
 *  若只想更新昵称或头像其中一个的用户信息，可调用时把另一个值置为nil即可。

 *  @param nickName  用户昵称(不能带emoji表情，最长10个字符)
 *  @param urlString 用户头像地址
 *  @param accountId 第三方账户ID，唯一标识(必传)
 *  @param callback  更新结果回调
 */
+ (void)updateUserNickName:(NSString*)nickName
                 headerUrl:(NSString*)urlString
             withAccountId:(NSString*)accountId
                  callback:(void(^)(UXinUpdateUserInfoResult result))callback;

@end

/**
 *  将在以后的某个版本删除的方法
 */
@interface UXinSDK (Deprecated)

/**
 *  断开连接
 *  为了用户能更方便的拨打有信电话，此方法已经被弃用，将来某个版本会移除。
 *  请用｀+(void)logout｀
 */
+ (void)disconnect;

/**
 *  清除缓存,把本地保存的token清除，下次登录sdk需要重新获取token
 *  请用｀+(void)logout｀
 */
+ (void)clearCache;

@end
