#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

#include "definitions.h"
#include "displaySetup.h"

int getInTemp();
int getOutTemp();
void heat(bool state);
void cool(bool state);

void setup() {
  // put your setup code here, to run once:
  //temp probes
  pinMode(inTempProbe, INPUT);
  pinMode(outTempProbe, INPUT);
  //relay setups
  pinMode(heaterPin, OUTPUT);
  pinMode(acPin, OUTPUT);

  //start the display
  displaySetup();

  //debug setup
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  display.println("Finished Setup");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Refresh temperature
  //inTemp = getInTemp();
  //Serial.print("I'm doing it!!\n");

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

int getInTemp() {
  return digitalRead(inTempProbe);
}

void heat(bool state){
  digitalWrite(heaterPin,state);
}

void cool(bool state){
  digitalWrite(acPin,state);
}
//eof

