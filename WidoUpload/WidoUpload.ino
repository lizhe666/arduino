#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#define Wido_IRQ   7
#define Wido_VBAT  5
#define Wido_CS    10

Adafruit_CC3000 Wido = Adafruit_CC3000(Wido_CS, Wido_IRQ, Wido_VBAT,SPI_CLOCK_DIVIDER); // you can change this clock speed
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2
#define WLAN_SSID       "lizhe666"           // cannot be longer than 32 characters!
#define WLAN_PASS       "11111111"          // For connecting router or AP, don't forget to set the SSID and password here!!
#define TCP_TIMEOUT      3000
#define WEBSITE  "www.ixinfeng.com"
#define API_key  "80f8bfe40553d4a8761ae6f3ca31089c"

/////////////////////////////
//CO2 start
#include "SoftwareSerial.h"
#include <T6603.h>  //download from   http://forum.arduino.cc/index.php?topic=289428.0
T6603 sensor;
//CO2 end
/////////////////////////////


void setup(){
  Serial.begin(115200);
  
  /* Initialise the module */
  Serial.println(F("\nInitialising ..."));
  if (!Wido.begin()) {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while(1);
  }

  /* Attempt to connect to an access point */
  char *ssid = WLAN_SSID;             /* Max 32 chars */
  Serial.print(F("\nAttempting to connect to ")); 
  Serial.println(ssid);

  /* NOTE: Secure connections are not available in 'Tiny' mode!
   By default connectToAP will retry indefinitely, however you can pass an
   optional maximum number of retries (greater than zero) as the fourth parameter.
   */
  if (!Wido.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }

  Serial.println(F("Connected wifi!"));

  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!Wido.checkDHCP()) {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  
 
  /////////////////////////////
  //CO2 start
  //volt   5V   
  //port 3    5V+
  //port 4    GND
  //Serial.begin(19200);
  Serial.println("Initing...Co2");
  sensor.begin(9/*port 2*/, 11/*port 1*/);  
  //CO2 end
  ///////////////////////////// 
}

uint32_t ip = 0;
float temp = 0;

void loop(){
  
  static Adafruit_CC3000_Client widoClient;
  static unsigned long RetryMillis = 0;
  static unsigned long uploadtStamp = 0;
  static unsigned long sensortStamp = 0;

  if(!widoClient.connected() && millis() - RetryMillis > TCP_TIMEOUT){
    // Update the time stamp
    RetryMillis = millis();

    Serial.println(F("Try to connect the cloud server"));
    widoClient.close();

    // Get WEBSITE IP address
    while  (ip  ==  0)  {
      if  (!Wido.getHostByName(WEBSITE, &ip))  {    //  Get the server IP address based on the domain name
        Serial.println(F("Couldn't resolve!"));
      }
      delay(500);
    }  
    Wido.printIPdotsRev(ip);
    Serial.println(F(""));
    ip = Wido.IP2U32(192,168,138,1);  //TODO make it assign
    Wido.printIPdotsRev(ip);
    Serial.println(F(""));
    
    // Connect to the WEBSITE Server
    widoClient = Wido.connectTCP(ip, 80);          // Try to connect cloud server
  } else {
    Serial.print(F("1"));
  }
  
  //when connect, do something!
  if(widoClient.connected() && millis() - uploadtStamp > 5000){
    uploadtStamp = millis();
        
    Serial.println(F("Sending headers"));   // Send headers
    widoClient.fastrprintln(F("GET /st/DoReceiveInfo?uid=666&sensorId=666666&value=888 HTTP/1.1"));
    Serial.print("1...");
    
    /*
    char str[100] = "";
    sprintf(str,"%s%d","GET /st/DoReceiveInfo?uid=666&sensorId=666666&value=",sensor.get_co2());
    Serial.print(str);
    widoClient.fastrprintln(str);    
    */
    Serial.print(sensor.get_co2());
            
    widoClient.fastrprintln("Host: www.ixinfeng.com");
    Serial.print("2...");
    widoClient.fastrprintln(F("\r\n"));
    Serial.print("3...");
    widoClient.fastrprintln(F("\r\n"));
    Serial.println("4...");
    Serial.println(F(" done."));
   
    /********** Get the http page feedback ***********/
    unsigned long rTimer = millis();
    Serial.println(F("Reading Cloud Response!!!\r\n"));
    while (millis() - rTimer < 2000) {
      while (widoClient.connected() && widoClient.available()) {
        char c = widoClient.read();
        Serial.print(c);
      }
    }
    delay(1000);             // Wait for 1s to finish posting the data stream
    widoClient.close();      // Close the service connection
    RetryMillis = millis();  // Reset the timer stamp for applying the connection with the service
  } else {
    Serial.print(F("2"));
  }

}


