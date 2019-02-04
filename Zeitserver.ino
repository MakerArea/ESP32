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


/*-----------Bitte ab hier nichts mehr ändern, da änderungen Probleme verursachen können-----------*/


void setup() 
{
  pinMode(relay, OUTPUT);
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

void loop() 
{
  for(int i=0; i<15;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  
  dateTime = NTPch.getNTPtime(1.0, 1);
  
  byte actualHour = dateTime.hour;
  byte actualMinute = dateTime.minute;

  if(actualMinute==lastMinute)
  {
    actualMinute++;
    if(actualMinute > 59)
    {
      actualMinute=0;
      actualHour++;
      if(actualHour > 23)
      {
        actualHour=0;
      }
    }
  }
  lastMinute=actualMinute;


  //Zählt 2 Minuten weiter, da der Zeitserver 2 Minuten nachgeht
  actualMinute+=2;
  if(actualMinute > 59)
  {
    actualMinute-=60;
    actualHour++;
    if(actualHour > 23)
    {
      actualHour=0;
    }
  }

  //Uhrzeitausgabe am Seriellen Monitor (wenns ned richtig funktioniert: Hilfe beim suchen eines Fehlers)
  Serial.print(actualHour);
  Serial.print(":");
  Serial.println(actualMinute);

  //Uhrzeitanzeige an den LEDs (also an der Uhr)
  haus();
  minaus();

  switch(actualHour)
  {
    case 0: for(int i=30; i<38; i++)  {pixels.setPixelColor(i, pixels.Color(0, 0, 0));} break;
    
    case 1: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  break;
    
    case 2: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut)); 
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  break;
            
    case 3: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));
            pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut));  break;
            
    case 4: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));
            pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut));
            pixels.setPixelColor(33, pixels.Color(rott, gruent, blaut));  break;
            
    case 5: //haus();
            pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  break;
            
    case 6: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  break;
    
    case 7: pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  break;
            
    case 8: pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut)); 
            pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut));  break;
            
    case 9: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut)); 
            pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut));
            pixels.setPixelColor(33, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  break;
    
    case 10: //haus();
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  break;
             
    case 11: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  break;
    
    case 12: pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  
              pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rot, gruent, blaut));  break;
    
    case 13: pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut)); 
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  
              pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  break;
             
    case 14: pixels.setPixelColor(33, pixels.Color(rott, gruent, blaut)); 
              pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut)); 
            pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  
              pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  break;
    
    case 15: //haus();
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut));  break;
             
    case 16: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut));  break;
             
    case 17: pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut));  break;
    
    case 18: pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut));  
              pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut));  break;
    
    case 19: pixels.setPixelColor(33, pixels.Color(rott, gruent, blaut)); 
            pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut));  
              pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut));  
            pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut));  
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut));  break;
    
    case 20: //haus();
             pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(37, pixels.Color(rott, gruent, blaut));  break;
             
    case 21: pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut)); 
              pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(37, pixels.Color(rott, gruent, blaut));  break;
    
    case 22: pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut)); 
              pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut)); 
              pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(37, pixels.Color(rott, gruent, blaut));  break;
    
    case 23: pixels.setPixelColor(32, pixels.Color(rott, gruent, blaut));  
              pixels.setPixelColor(31, pixels.Color(rott, gruent, blaut)); 
              pixels.setPixelColor(30, pixels.Color(rott, gruent, blaut)); 
              pixels.setPixelColor(34, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(35, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(36, pixels.Color(rott, gruent, blaut)); 
             pixels.setPixelColor(37, pixels.Color(rott, gruent, blaut));  break;
  }

  switch(actualMinute)
  {
    case 0:   for(int i=15; i<30; i++)  {pixels.setPixelColor(i, pixels.Color(0, 0, 0));} break;
    
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
    
    case 5: //minaus();
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
    
    case 10: //minaus();
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
    
    case 15: //minaus();
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
    
    case 20: //minaus();
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
    
    case 25: //minaus();
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
    
    case 30: //minaus();
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
    
    case 35: //minaus();
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
    
    case 40: //minaus();
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
    
    case 45: //minaus();
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
    
    case 50: //minaus();
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
    
    case 55: //minaus();
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
