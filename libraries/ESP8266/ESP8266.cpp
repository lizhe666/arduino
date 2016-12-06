#include "ESP8266.h"

void ESP8266::init(HardwareSerial* s, int pin) {
	Serial.println(("ESP8266::ESP8266 init"));
			
	this->wifiConnect = false;
	this->hardSerial = s;
	hardSerial->begin(115200);
	// must do rest 8266 in this way then  8266 will be in work state
	this->restPin = pin;
	pinMode(restPin, OUTPUT);
	digitalWrite(restPin, LOW); //reset
	delay(2000); //等待一段时间，让arduino板子完全启动后，才启动 will模块
	digitalWrite(restPin, HIGH); //reset
}

/**
 * 发送AT指令，并且
 */
bool ESP8266::doATCmdWithCheck(String cmd, const char* check, unsigned long timeout) {
	if(ESP8266_DEBUG){
		Serial.print(("ESP8266::doATCmdWithCheck\tCHECK="));
		Serial.println(check);
		Serial.print(("\tCMD="));
		Serial.println(cmd);
	}

	this->clearResults();
	hardSerial->setTimeout(timeout);
	hardSerial->print(cmd);
	delay(200);//这里需要执行delay否则会导致异常
	bool result = hardSerial->find((char*) check);
	if(ESP8266_DEBUG){
		Serial.print(("\tRESULT="));
		Serial.println(result);
	}

	return result;
}

/**
 * 发送AT 数据，并且检查返回
 */
bool ESP8266::doATDataWithCheck(byte buf[],int length, const char* check,unsigned long timeout) {
	if(ESP8266_DEBUG){
		Serial.print(("ESP8266::doATDataWithCheck\tCHECK="));
		Serial.println(check);
		Serial.print(("\tDATA="));
		//Serial.write(buf,length);
	}
	this->clearResults();
	hardSerial->setTimeout(timeout);
	hardSerial->write(buf,length);
	delay(500);//这里需要执行delay否则会导致异常
	bool result = hardSerial->find((char*) check);
	if(ESP8266_DEBUG){
		Serial.print(("\tRESULT="));
		Serial.println(result);
	}
	return result;
	
}

/**
* 直接用 uuid pwd 连接网络
*/
bool ESP8266::configWithPwd(String uuid,String pwd) {
	if (doATCmdWithCheck("AT+RST\r\n", "WIFI GOT IP", 15000)) {
		wifiConnect = true;
		return true;
	} else{
		doATCmdWithCheck("AT+CWAUTOCONN=1\r\n", "OK", 1000);
		//如果知道用户名和密码，就直接连接
		//if (doATCmdWithCheck("AT+CWJAP=\"chuanke-qa\",\"chuanketest\"\r\n", "WIFI CONNECTED", 15000)) {
		if (doATCmdWithCheck("AT+CWJAP=\""+uuid+"\",\""+pwd+"\"\r\n", "WIFI CONNECTED", 15000)) {
			wifiConnect = true;
			return true;
		}else{
			return false;
		}
	}
	
}

/**
*  type 0 AI_LINK
*  type 1 ESP_TOUCH
*  type 2 微信公众号
*/
void ESP8266::smartConfig(String type/*TODO*/) { //这里需要传入一个回调函数，用来在调用 smart config 的时候，用这个函数显示相关信息来提示用户，这个时候该配置网络了
	Serial.println(("ESP8266::smartConfig"));
	do {
		delay(200);
	} while (doATCmdWithCheck("AT\r\n", "OK", 1000) == false);
		
	if (doATCmdWithCheck("AT+RST\r\n", "WIFI GOT IP", 15000)) {
		wifiConnect = true;
	} else {
		doATCmdWithCheck("AT+CWMODE=1\r\n", "OK", 5000);
		
		//需要配置smart config
		Serial.println(("Now trying to connecting wifi  you have 120 seconds"));
		if (doATCmdWithCheck("AT+CWSMARTSTART="+type+"\r\n", "WIFI CONNECTED",
				120000)) { //等待 smart config 配置成功 (等待时间2分钟，两分钟未完成配置，则选择失效)
			wifiConnect = true;
		} else { //配置失败，进入无网络模式
			wifiConnect = false;
		}
	}
}

/**
*  建立tcp连接
*/
bool ESP8266::tcpStart(String host, int port) {
	if (wifiConnect) {
		if (doATCmdWithCheck("AT+CIPSTART=\"TCP\",\"" + host + "\"," + port + "\r\n","CONNECT", 2000)) {
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

/**
*  建立tcp连接后，发送数据包长度
*/
bool ESP8266::tcpSendLength(int length) {
	if (doATCmdWithCheck("AT+CIPSEND=" + (String) length + (String) "\r\n", ">", 1)) {
		return true;
	}else{
		return false;
	}
}

/**
*  建立tcp连接后，不断的发送数据包
*/
bool ESP8266::tcpSend(byte buf[],int length) {
	if (doATDataWithCheck(buf, length, "SEND OK", 1)) {
		return true;
	}else{
		return false;
	}
}

/**
*  关闭tcp连接
*/
bool ESP8266::tcpClose() {
	if (doATCmdWithCheck("AT+CIPCLOSE\r\n", "SEND OK", 100)) {
		return true;
	}else{
		return false;
	}
}

String ESP8266::httpGet(String host, int port, String path) {
	if (wifiConnect) {
		if (doATCmdWithCheck(
				"AT+CIPSTART=\"TCP\",\"" + host + "\"," + port + "\r\n",
				"CONNECT", 10000)) {
			String package = "GET " + path + " HTTP/1.1\r\nHost: " + host
					+ "\r\nConnection: Keep-Alive\r\n\r\n\r\n";
			String cmd = "AT+CIPSEND=" + (String) package.length()
					+ (String) "\r\n";
			if(ESP8266_DEBUG){
				Serial.println(cmd);
			}
			if (doATCmdWithCheck(cmd, ">", 10000)) {
				if (doATCmdWithCheck(package, "SEND OK", 10000)) {
					String _data;
					int available = hardSerial->available();
					/*
					 * 为了这个函数，我重新定义了
					 * #define SERIAL_TX_BUFFER_SIZE 512
					 * #define SERIAL_RX_BUFFER_SIZE 512
					 * 此文件位于   \Arduino\hardware\arduino\avr\cores\arduino
					 * 切记，必须从这里修改原始文件！！！因为后面还有相关的逻辑，在这里重新定义是没有意义的
					 */
					while (available > 0) {
						_data += (char) hardSerial->read();
						//Serial.println(available);
						available = hardSerial->available();
						delay(20); //必须增加这行代码，否则数据接受不全
					}
					if(ESP8266_DEBUG){
						Serial.println("------ http response start ------");
						Serial.println(_data);
						Serial.println("------ http response end ------");
					}
					if (_data.length() > 20) {  //第二个  双换行后，就是需要的内容
						_data = _data.substring(4);
						_data = _data.substring(_data.indexOf("\r\n\r\n") + 4);

						int beginIndex = _data.indexOf("_INFO_B_");
						int endIndex = _data.indexOf("_INFO_E_");
						if (beginIndex >= 0 && endIndex > 0) {
							_data = _data.substring(beginIndex + 8, endIndex);
						}
					}
					//doATCmdWithCheck("AT+CIPCLOSE\r\n", "SEND OK", 10000);
					return _data;
				}
			}
		} else {
			return F("connect failed");
		}
	} else {
		return F("no wifi connect");
	}
	return F("connect middle failed");
}

String ESP8266::httpPost() {
	return F("post");
}

/**
 *	清除 串口缓冲区中未输出的字符串，以便下次解析
 */
void ESP8266::clearResults() {
	while (hardSerial->available() > 0) {
		hardSerial->read();
		delay(2);
	}
}
