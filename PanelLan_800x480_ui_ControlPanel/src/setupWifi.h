#include <WiFi.h>
//#include "getWifiAccess.h"
const char* ssid = "ESP32-NODE-1";
const char* password = "123456789";
// We set a Static IP address
IPAddress local_IP(192, 168, 4, 3);
// We set a Gateway IP address
IPAddress gateway(192, 168, 4, 2);
IPAddress subnet(255, 255, 255, 0);

void setupWifi(const char* _ssid, IPAddress _gateway) 
{
    //ESP32 connects to your wifi -----------------------------------
  //WiFi.mode(WIFI_STA); 
  Serial.println(WiFi.config(local_IP, _gateway, subnet) ? "Ready" : "Failed!");
  WiFi.begin(_ssid, password);

  Serial.println("Connecting to ");
  Serial.print(_ssid);

  //Wait for WiFi to connect
  const long interval = 5000; 
  unsigned long currentMillis = millis();
  unsigned long previousMillis = currentMillis;
  while(WiFi.waitForConnectResult() != WL_CONNECTED)
  {   
      currentMillis = millis();   
      Serial.print(".");
      if(currentMillis - previousMillis >= interval) 
      {
        break;
      }
  }
  
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

String getWifi()
{  
  IPAddress ip = WiFi.localIP();
  String _ip = ip.toString();
  return (String)(_ip);
}
