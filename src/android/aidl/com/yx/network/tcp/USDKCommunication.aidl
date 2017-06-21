package com.yx.network.tcp;

import com.yx.network.tcp.USDKYxMessage;

interface USDKCommunication {

 boolean isTCPConnection();
 
 //tcp重新连接
 void reTcpConnection(); 
 
 //断开tcp连接
 void disTCPconnect();
 
 //发送消息
 int sendPack(in byte[] head, in byte[] body, in int headLength, in int bodyLength);
 
 
 //设置ams登录返回的ac
 void setAc(in String ac, in String uid);
 
 //获取当前需要处理的所有数据包  ResponseDataPack为统一封装好的接收消息的数据包，同我们现有的保持一致。
 //List<USDKYxMessage> getYxMessage(in boolean isLoadLib); isLoad是否加载完库文件
 USDKYxMessage getYxMessage(in boolean isLoadLib);
 
 //获取tcp是否登录
 boolean getTcpLogin();
 
 //退出进程
 void exit();
 
  //获取cs地址
 String getCs();
 
 //对外提供发送心跳包方法
 void sendPingPack();
 
 long getPingTime();
 
}

