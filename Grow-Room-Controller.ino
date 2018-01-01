#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#include "definitions.h"
#include "displaySetup.h"

//function prototypes
int getInTemp();
int getOutTemp();
void heat(bool state);
void cool(bool state);
void sendToDisplay(int temp);

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

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    
    //Refresh temperature
    inTemp = getInTemp();
    Serial.print(inTemp);
    sendToDisplay(inTemp);
    
    if ( (inTemp <= tempSet + tempRng) && (inTemp >= tempSet - tempRng)){
      heat(0);
      cool(0);
    }
    if (inTemp > tempSet + tempRng){
      cool(1);
      heat(0);
    }
    else if (inTemp < tempSet - tempRng){
      heat(1);
      cool(0);
    }
  }
}

int getInTemp() {
  float t = dht.readTemperature(true);
  if (isnan(t))
    Serial.println("Failed to read from DHT sensor!");
  return floor(t);
}

int getOutTemp(){
  return digitalRead(outTempProbe);
}

void heat(bool state){
  digitalWrite(heaterPin,state);
  return;
}

void cool(bool state){
  digitalWrite(acPin,state);
  return;
}

void sendToDisplay(int inTemp){
  display.print(inTemp);
  display.display();
  return;
}
//eof

