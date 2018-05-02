#include <WiFi.h>

const char* ssid = "MakerArea";
const char* password = "!MaAr_2018@";

void setup() 
{
  Serial.begin(9600);
  Serial.println("");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Attempting to connect...");
    delay(1000);
  }
  Serial.println("Connected to Wi-Fi network");

  Serial.print("IP-address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  
}
