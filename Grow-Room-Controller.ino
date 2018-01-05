#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include "definitions.h"
#include "displaySetup.h"
#include "menu.h"

//function prototypes
int getTemp();
void heat(bool state);
void cool(bool state);
void updateDisplay();

void setup() {
  //temp probes
  pinMode(outTempProbe, INPUT);
  //relay setups
  pinMode(heaterPin, OUTPUT);
  pinMode(acPin, OUTPUT);

  //start the display
  displaySetup();

  //start the temperature sensor
  dht.begin();

  //debug setup
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  //Display finished setup on screen before starting loop
  display.println("Finished Setup");
  display.display();
  delay(1500);
  display.clearDisplay();
  display.setCursor(0,0);
  display.display();
}
/* --------------------- END SETUP --------------------- */

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    
    //Refresh temperature
    getTemp();
//    Serial.print(inTemp);
    updateDisplay();
    
    if ( (inTemp <= tempSet + tempRng) && (inTemp >= tempSet - tempRng)){
      Serial.println("Within Range");
      heat(LOW);
      cool(LOW);
    }
    if (inTemp > tempSet + tempRng){
      Serial.println("Too Hot");
      cool(HIGH);
      heat(LOW);
    }
    else if (inTemp < tempSet - tempRng){
      Serial.println("Too Cold");
      heat(HIGH);
      cool(LOW);
    }
  }
}
/* --------------------- END LOOP --------------------- */

int getTemp() {
  float t = dht.readTemperature(true);
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h))
    Serial.println("Failed to read from DHT sensor!");
  else {
    inTemp = floor(t);
    inHumid = floor(h);
  }
  return floor(t);
}

void heat(bool state){
  Serial.println("Heat: " + String(state));
  heatStatus = state;
  digitalWrite(heaterPin,!state);
  return;
}

void cool(bool state){
  Serial.println("Cool: " + String(state));
  coolStatus = state;
  digitalWrite(acPin,!state);
  return;
}

void updateDisplay(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Set temp: " + String(tempSet) + "  Rng: " + String(tempRng));
  display.println("In Temp:  " + String(inTemp) + "; " + String(inHumid) + '%');
  display.println("Out Temp: " + String(outTemp) + "; " + String(outHumid) + '%');
  display.println("Heat: " + String(heatStatus) + "  Cool: " + String(coolStatus));
  display.display();
  return;
}
//eof

