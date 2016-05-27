//Arduino Sample Code //www.DFRobot.com 
//Last modified on 14th March 2012 by HJS 
//This code has been updated to work with the sample code provided in the Wiki   
int Relay = 11;    

void setup() {   
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);     //Set Pin3 as output 
} 
void loop() {           
  digitalWrite(Relay, HIGH);   //Turn off relay 
  Serial.println("high signal has sent!");  
  delay(2000);           
  digitalWrite(Relay, LOW);    //Turn on relay  
    Serial.println("low signal has sent!");  
  
  delay(2000); 
} 
