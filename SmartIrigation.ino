#define BLYNK_PRINT Serial
 
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include <DHT.h> 


char auth[] = "rEYhj0lKwY8HcaH3A0_nqJUHm-X79xsT";
 
// Podaci o wifi mrezi.

char ssid[] = "NemaInterneta";
char pass[] = "nemozesifra123";
 
#define DHTPIN D6          
#define DHTTYPE DHT11
#define vlaznost A0

BlynkTimer timer;
int t;
float t1;
float h1;
int v;
int h;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
}
 
 

void sendSensor()
{
  h1 = dht.readHumidity();
  h=round(h1);
  t1 = dht.readTemperature();
  t=round(t1);

  v= analogRead(vlaznost);
  v = map(v, 1023, 0, 0, 100);  
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Neuspjesno citanje sa DHT senzora!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, v);
  
}
 
