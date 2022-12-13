#include "DHT.h" // Temp/Humidity by Adafruit
#include "RTClib.h" // Real Time Clock by Adafruit

#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

volatile unsigned int* portH = (unsigned int*)0x102;
volatile unsigned int* ddrH = (unsigned int*)0x101;
float temp;
float humid;

// Fan Motor
bool fanOn = false;

void setup() {
  // DHT
  dht.begin();
  *ddrH |= 0x60;
}

void loop() {
  // put your main code here, to run repeatedly:

  
   humid = getHumid(); // MONITOR temp and humidity, turn fan on if temp above threshold
   temp = getTemp();
  
   humid = getHumid(); // MONITOR temp and humidity
    temp = getTemp();
  
   humid = getHumid(); // MONITOR temp and humidity, turn fan on if temp above threshold
    temp = getTemp();
}





bool fanTemp(float tempC) { // take in temp reading and turn fan on or off
  if (tempC >= 21) {
    *portH |= 0x20;
    *portH |= 0x40;

    return true;
  } 
  else if (tempC < 21) {
    *portH &= 0xDF;

    return false;
  }
}

float getHumid(){
  float humi = dht.readHumidity();

  return humi;
}

float getTemp() {
  float tempC = dht.readTemperature();

  return tempC;
}
