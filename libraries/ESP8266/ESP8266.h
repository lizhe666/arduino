#ifndef __ESP8266_H_DEFINE__
#define __ESP8266_H_DEFINE__

#include "Arduino.h"

#define ESP8266_DEBUG true

class ESP8266 {

private:
	int restPin;
	HardwareSerial* hardSerial;
	bool wifiConnect;
	void clearResults(void);
	bool doATCmdWithCheck(String, const char*, unsigned long);
	bool doATDataWithCheck(byte [], int, const char*, unsigned long);
public:
	bool isWifiConnect() const {
		return wifiConnect;
	}
	
	void init(HardwareSerial*, int);
	bool configWithPwd(String,String);
	void smartConfig(String);
	String httpGet(String, int, String);
	String httpPost();

	/**
	*  建立tcp连接
	*/
	bool tcpStart(String,int) ;
	/**
	*  建立tcp连接后，发送数据包长度
	*/
	bool tcpSendLength(int);
	/**
	*  建立tcp连接后，不断的发送数据包
	*/
	bool tcpSend(byte [],int) ;
	/**
	*  关闭tcp连接
	*/
	bool tcpClose();
};

#endif
