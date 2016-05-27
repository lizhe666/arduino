#ifndef __ESP8266_H_DEFINE__
#define __ESP8266_H_DEFINE__

#include "Arduino.h"

#define ESP8266_DEBUG false

class ESP8266 {

private:
	int restPin;
	HardwareSerial* hardSerial;
	bool wifiConnect;
	void clearResults(void);
	bool doATCmdWithCheck(String,const char*, unsigned long);

public:
	void init(HardwareSerial* s, int pin);
	void smartConfig();
	String httpGet(String, int, String);
	String httpPost();

	bool isWifiConnect() const {
		return wifiConnect;
	}
};

#endif
