#include <NTPtimeESP.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define PIN         2
#define NUMPIXELS   38

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DEBUG_ON

NTPtime NTPch("0.pool.ntp.org");
char *ssid      = "MakerArea";
char *password  = "!MaAr_2018@";

strDateTime dateTime;

int sectime=3750;

int rot=0;
int gruen=0;
int blau=150;

byte actualHour;
byte actualMinute;

void setup() 
{
  pixels.begin();

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

  dateTime = NTPch.getNTPtime(1.0, 1);
  
  byte actualHour = dateTime.hour;
  byte actualMinute = dateTime.minute;
}

void haus()
{
  for (int i=30; i<33; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void minaus()
{
  for (int i=15; i<18; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void loop() 
{
  for(int i=0; i<15;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  
  dateTime = NTPch.getNTPtime(1.0, 1);
  
  byte actualHour = dateTime.hour;
  byte actualMinute = dateTime.minute;

  Serial.print(actualHour);
  Serial.print(":");
  Serial.println(actualMinute);

  switch(actualHour)
  {
    case 0: for(int i=30; i<37; i++)  {pixels.setPixelColor(i, pixels.Color(0, 0, 0));} break;
    
    case 1: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  break;
    
    case 2: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau)); 
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  break;
            
    case 3: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));
            pixels.setPixelColor(32, pixels.Color(rot, gruen, blau));  break;
            
    case 4: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));
            pixels.setPixelColor(32, pixels.Color(rot, gruen, blau));
            pixels.setPixelColor(33, pixels.Color(rot, gruen, blau));  break;
            
    case 5: haus();
            pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  break;
            
    case 6: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  break;
    
    case 7: pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  break;
            
    case 8: pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau)); 
            pixels.setPixelColor(32, pixels.Color(rot, gruen, blau));  break;
            
    case 9: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau)); 
            pixels.setPixelColor(32, pixels.Color(rot, gruen, blau));
            pixels.setPixelColor(33, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  break;
    
    case 10: haus();
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  break;
             
    case 11: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  break;
    
    case 12: pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  
              pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  break;
    
    case 13: pixels.setPixelColor(32, pixels.Color(rot, gruen, blau)); 
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  
              pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  break;
             
    case 14: pixels.setPixelColor(33, pixels.Color(rot, gruen, blau)); 
              pixels.setPixelColor(32, pixels.Color(rot, gruen, blau)); 
            pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  
              pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  break;
    
    case 15: haus();
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau));  break;
             
    case 16: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau));  break;
             
    case 17: pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau));  break;
    
    case 18: pixels.setPixelColor(32, pixels.Color(rot, gruen, blau));  
              pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau));  break;
    
    case 19: pixels.setPixelColor(33, pixels.Color(rot, gruen, blau)); 
            pixels.setPixelColor(32, pixels.Color(rot, gruen, blau));  
              pixels.setPixelColor(31, pixels.Color(rot, gruen, blau));  
            pixels.setPixelColor(30, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau));  break;
    
    case 20: haus();
             pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(37, pixels.Color(rot, gruen, blau));  break;
             
    case 21: pixels.setPixelColor(30, pixels.Color(rot, gruen, blau)); 
              pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(37, pixels.Color(rot, gruen, blau));  break;
    
    case 22: pixels.setPixelColor(31, pixels.Color(rot, gruen, blau)); 
              pixels.setPixelColor(30, pixels.Color(rot, gruen, blau)); 
              pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(37, pixels.Color(rot, gruen, blau));  break;
    
    case 23: pixels.setPixelColor(32, pixels.Color(rot, gruen, blau));  
              pixels.setPixelColor(31, pixels.Color(rot, gruen, blau)); 
              pixels.setPixelColor(30, pixels.Color(rot, gruen, blau)); 
              pixels.setPixelColor(34, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(36, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(37, pixels.Color(rot, gruen, blau));  break;
  }

  switch(actualMinute)
  {
    case 0:   for(int i=15; i<29; i++)  {pixels.setPixelColor(i, pixels.Color(0, 0, 0));} break;
    
    case 1: pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 2: pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;

    case 3: pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 4:pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 5: minaus();
            pixels.setPixelColor(19, pixels.Color(rot, gruen, blau));  break;
            
    case 6: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 7:pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 8:pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  
          pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 9: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
          pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  
          pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  
          pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 10: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau));  break;
             
    case 11: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 12:pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 13: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 14: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 15: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau));  break;
             
    case 16: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 17: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 18: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 19: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 20: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau));  break;
             
    case 21: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 22: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 23: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 24: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 25: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau));  break;
             
    case 26: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 27: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 28: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 29: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 30: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau));  break;
             
    case 31: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 32: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 33: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 34: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 35: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau));  break;
             
    case 36: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 37: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 38: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 39: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 40: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau));  break;
             
    case 41: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 42: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 43: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 44: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 45: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau));  break;
             
    case 46: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 47: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;

    case 48: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 49: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 50: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau));  break;
             
    case 51: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 52: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 53: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 54: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
    case 55: minaus();
             pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(29, pixels.Color(rot, gruen, blau));  break;
             
    case 56: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(29, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau));  break;
    
    case 57: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(29, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau));  break;
    
    case 58: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(29, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau));  break;
    
    case 59: pixels.setPixelColor(19, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(20, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(21, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(22, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(23, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(24, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(25, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(26, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(27, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(28, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(29, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(15, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(16, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(17, pixels.Color(rot, gruen, blau)); 
             pixels.setPixelColor(18, pixels.Color(rot, gruen, blau));  break;
    
  }

  portDISABLE_INTERRUPTS();
  pixels.show();
  portENABLE_INTERRUPTS();

  delay(sectime);

  for(int i=0; i<15;i++)
  {
    pixels.setPixelColor(i, pixels.Color(rot, gruen, blau));
    portDISABLE_INTERRUPTS();
    pixels.show();
    portENABLE_INTERRUPTS();
    delay(sectime);
  }
}
