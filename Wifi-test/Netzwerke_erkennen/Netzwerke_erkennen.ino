#include <WiFi.h>

void setup() 
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  int N=WiFi.scanNetworks();
  if(N>0)
  {
    Serial.println("");
    Serial.print(N);
    Serial.println(" Networks found");
    for (int i=0; i<N; i++)
    {
      Serial.print(i+1);
      Serial.print(": ");
      Serial.print("Network Name: ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" ");
      Serial.print("Signal Strangth: ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" ");
      Serial.print("Mac Address: ");
      Serial.println(WiFi.BSSIDstr(i));
      delay(50);
    }
  }
}

void loop() 
{
  
}
