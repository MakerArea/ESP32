/*  
 *  © Felix Geiger, 2018
 *  
 *    Die Stellen, an denen etwas geändert werden darf, sind nur in den ersten 50 Zeilen UND mit einem 
 *    
 *        //
 *        
 *    und einer kurzen Info gekennzeichnet.
 */
#include <NTPtimeESP.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define PIN         2
#define NUMPIXELS   38

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DEBUG_ON

NTPtime NTPch("1.pool.ntp.org");        //Adresse des benutzten Zeitservers
char *ssid      = "MakerArea";          //SSID hier eintragen
char *password  = "!MaAr_2018@";        //Password hier eintragen

strDateTime dateTime;

int sectime=3750;

int rotgd=255;      //  
int gruengd=255;    //   }- einzelne Farbwerte; diese geben zusammen die Farbe an, in der die LEDs leuchten (Sekunden)
int blaugd=255;     //  

int rot=0;      //
int gruen=0;    //   }- einzelne Farbwerte; diese geben zusammen die Farbe an, in der die LEDs leuchten (Minuten)
int blau=255;   // 

int rott=0;      //
int gruent=255;  //   }- einzelne Farbwerte; diese geben zusammen die Farbe an, in der die LEDs leuchten (Stunden)
int blaut=180;   //

byte actualHour;
byte actualMinute;
byte lastMinute=25;

int relay=15;
int einzeit=6;  //Uhrzeit, bei der das Bosch-Schild einschaltet (Stunde)
int auszeit=20; //Uhrzeit, bei der das Bosch-Schild ausschaltet (Stunde)


/*-----------Bitte ab hier nichts mehr ändern, da Änderungen Probleme verursachen können-----------*/

byte altmin;

int resetvar=0;
int wlan=0;

void setup() 
{
  pinMode(relay, OUTPUT);
  pixels.begin();

  Serial.begin(9600);
  Serial.println("");
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    if(wlan<15)
    {
      Serial.println("Attempting to connect...");
      delay(1000);
      wlan++;
    }
    else
    {
      Serial.println("Restart, da kein W-LAN Verbindung möglich");
      ESP.restart();
    }
  }
  Serial.println("Connected to Wi-Fi network");

  Serial.print("IP-address: ");
  Serial.println(WiFi.localIP());

  for(int i=0; i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
  }
  portDISABLE_INTERRUPTS();
  pixels.show();
  portENABLE_INTERRUPTS();
  delay(3000);
  for(int i=0; i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  portDISABLE_INTERRUPTS();
  pixels.show();
  portENABLE_INTERRUPTS();

  dateTime = NTPch.getNTPtime(1.0, 1);
  
  byte actualHour = dateTime.hour;
  byte actualMinute = dateTime.minute;
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

  if(actualMinute==altmin)
  {
    actualMinute++;
    if(actualMinute>=60)
    {
      actualMinute-=60;
      actualHour++;
      if(actualHour>=24)
      {
        actualHour-=24;
      }
    }
  }
  else
  {
    altmin=actualMinute;
  }

  //Uhrzeitausgabe am Seriellen Monitor (wenns ned richtig funktioniert: Hilfe beim suchen eines Fehlers)
  Serial.print(actualHour);
  Serial.print(":");
  Serial.println(actualMinute);

  //Uhrzeitanzeige an den LEDs (also an der Uhr)
  setzen(15, 37, 0, 0, 0);  //alle Minuten- und Stunden-LEDs aus

  switch(actualHour)
  {
    case 0: 
      setzen(30, 37, 0, 0, 0);
      break;
    case 1: 
      if(resetvar==1)
      {
        resetvar=0;
        ESP.restart();
      }
      setzen(30, 30, rott, gruent, blaut);
      break;
    case 2: 
      setzen(30, 31, rott, gruent, blaut);
      break;
    case 3: 
      setzen(30, 32, rott, gruent, blaut);
      break;
    case 4: 
      setzen(30, 33, rott, gruent, blaut);
      break;
    case 5: 
      setzen(34, 34, rott, gruent, blaut);
      break;
    case 6: 
      setzen(30, 30, rott, gruent, blaut);
      setzen(34, 34, rott, gruent, blaut);
      break;
    case 7: 
      setzen(30, 31, rott, gruent, blaut);
      setzen(34, 34, rott, gruent, blaut);
      break;
    case 8: 
      setzen(30, 32, rott, gruent, blaut);
      setzen(34, 34, rott, gruent, blaut);
      break;
    case 9: 
      setzen(30, 34, rott, gruent, blaut);
      break;
    case 10: 
      setzen(34, 35, rott, gruent, blaut);
      break;
    case 11: 
      setzen(30, 30, rott, gruent, blaut);
      setzen(34, 35, rott, gruent, blaut);
      break;
    case 12:  
      resetvar=1;
      setzen(30, 31, rott, gruent, blaut);
      setzen(34, 35, rott, gruent, blaut);
      break;
    case 13:  
      setzen(30, 32, rott, gruent, blaut);
      setzen(34, 35, rott, gruent, blaut);
      break;
    case 14:  
      setzen(30, 35, rott, gruent, blaut);
      break;
    case 15:  
      setzen(34, 36, rott, gruent, blaut);
      break;
    case 16:  
      setzen(30, 30, rott, gruent, blaut);
      setzen(34, 36, rott, gruent, blaut);
      break;
    case 17:   
      setzen(30, 31, rott, gruent, blaut);
      setzen(34, 36, rott, gruent, blaut);
      break;
    case 18:   
      setzen(30, 32, rott, gruent, blaut);
      setzen(34, 36, rott, gruent, blaut);
      break;
    case 19:   
      setzen(30, 36, rott, gruent, blaut);
      break;
    case 20:  
      setzen(34, 37, rott, gruent, blaut);
      break;
    case 21:   
      setzen(30, 30, rott, gruent, blaut);
      setzen(34, 37, rott, gruent, blaut);
      break;
    case 22:   
      setzen(30, 31, rott, gruent, blaut);
      setzen(34, 37, rott, gruent, blaut);
      break;
    case 23:   
      setzen(30, 32, rott, gruent, blaut);
      setzen(34, 37, rott, gruent, blaut);
      break;
  }

  switch(actualMinute)
  {
    case 0:
      setzen(15, 29, 0, 0, 0);
      break;
    case 1: 
      setzen(15, 15, rot, gruen, blau);
      break;
    case 2: 
      setzen(15, 16, rot, gruen, blau);
      break;
    case 3: 
      setzen(15, 17, rot, gruen, blau);
      break;
    case 4:
      setzen(15, 18, rot, gruen, blau);
      break;
    case 5: 
      setzen(19, 19, rot, gruen, blau);
      break;
    case 6: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 19, rot, gruen, blau);
      break;
    case 7:
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 19, rot, gruen, blau);
      break;
    case 8:
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 19, rot, gruen, blau);
      break;
    case 9: 
      setzen(15, 19, rot, gruen, blau);
      break;
    case 10: 
      setzen(19, 20, rot, gruen, blau);
      break;
    case 11: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 20, rot, gruen, blau);
      break;
    case 12:
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 20, rot, gruen, blau);
      break;
    case 13: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 20, rot, gruen, blau);
      break;
    case 14: 
      setzen(15, 20, rot, gruen, blau);
      break;
    case 15: 
      setzen(19, 21, rot, gruen, blau);
      break;
    case 16: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 21, rot, gruen, blau);
      break;
    case 17: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 21, rot, gruen, blau);
      break;
    case 18: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 21, rot, gruen, blau);
      break;
    case 19: 
      setzen(15, 21, rot, gruen, blau);
      break;
    case 20: 
      setzen(19, 22, rot, gruen, blau);
      break;
    case 21: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 22, rot, gruen, blau);
      break;
    case 22: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 22, rot, gruen, blau);
      break;
    case 23: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 22, rot, gruen, blau);
      break;
    case 24: 
      setzen(15, 22, rot, gruen, blau);
      break;
    case 25: 
      setzen(19, 23, rot, gruen, blau);
      break;
    case 26: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 23, rot, gruen, blau);
      break;
    case 27: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 23, rot, gruen, blau);
      break;
    case 28: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 23, rot, gruen, blau);
      break;
    case 29: 
      setzen(15, 23, rot, gruen, blau);
      break;
    case 30: 
      setzen(19, 24, rot, gruen, blau);
      break;
    case 31: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 24, rot, gruen, blau);
      break;
    case 32: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 24, rot, gruen, blau);
      break;
    case 33: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 24, rot, gruen, blau);
      break;
    case 34: 
      setzen(15, 24, rot, gruen, blau);
      break;
    case 35: 
      setzen(19, 25, rot, gruen, blau);
      break;
    case 36: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 25, rot, gruen, blau);
      break;
    case 37: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 25, rot, gruen, blau);
      break;
    case 38: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 25, rot, gruen, blau);
      break;
    case 39: 
      setzen(15, 25, rot, gruen, blau);
      break;
    case 40: 
      setzen(19, 26, rot, gruen, blau);
      break;
    case 41: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 26, rot, gruen, blau);
      break;
    case 42: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 26, rot, gruen, blau);
      break;
    case 43: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 26, rot, gruen, blau);
      break;
    case 44: 
      setzen(15, 26, rot, gruen, blau);
      break;
    case 45: 
      setzen(19, 27, rot, gruen, blau);
      break;
    case 46: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 27, rot, gruen, blau);
      break;
    case 47: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 27, rot, gruen, blau);
      break;
    case 48: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 27, rot, gruen, blau);
      break;
    case 49: 
      setzen(15, 27, rot, gruen, blau);
      break;
    case 50: 
      setzen(19, 28, rot, gruen, blau);
      break;
    case 51: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 28, rot, gruen, blau);
      break;
    case 52: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 28, rot, gruen, blau);
      break;
    case 53: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 28, rot, gruen, blau);
      break;
    case 54: 
      setzen(15, 28, rot, gruen, blau);
      break;
    case 55: 
      setzen(19, 29, rot, gruen, blau);
      break;
    case 56: 
      setzen(15, 15, rot, gruen, blau);
      setzen(19, 29, rot, gruen, blau);
      break;
    case 57: 
      setzen(15, 16, rot, gruen, blau);
      setzen(19, 29, rot, gruen, blau);
      break;
    case 58: 
      setzen(15, 17, rot, gruen, blau);
      setzen(19, 29, rot, gruen, blau);
      break;
    case 59: 
      setzen(15, 29, rot, gruen, blau);
      break;
  }

  portDISABLE_INTERRUPTS();
  pixels.show();
  portENABLE_INTERRUPTS();

  boschschild();

  delay(sectime);

  //Sekundenanzeige
  for(int i=0; i<15;i++)
  {
    pixels.setPixelColor(i, pixels.Color(rotgd, gruengd, blaugd));
    portDISABLE_INTERRUPTS();
    pixels.show();
    portENABLE_INTERRUPTS();
    delay(sectime);
  }
}

void boschschild()
{
  if(actualHour >= einzeit and actualHour <= auszeit)
  {
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
  }
}

void haus()
{
  for (int i=30; i<34; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void minaus()
{
  for (int i=15; i<19; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void setzen(int startpix, int stoppix, int rwert, int gwert, int bwert)
{
  for(int ilauf=startpix; ilauf<=stoppix; ilauf++)
  {
    pixels.setPixelColor(ilauf, pixels.Color(rwert, gwert, bwert));
  }
}
