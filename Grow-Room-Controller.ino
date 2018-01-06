#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <TimerOne.h>
#include <ClickEncoder.h>

#include "definitions.h"
#include "displaySetup.h"
//#include "menu.h"

//function prototypes
int getTemp();
void heat(bool state);
void cool(bool state);
void updateDisplay();
void menuDisplay(char* heading, int data, boolean edit);
void timerIsr();
void menu();

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

  //Run menu setup to start encoder
  pointer[0]=menuItem0;
  pointer[1]=menuItem1;
  pointer[2]=exitMenuItem;
  encoder = new ClickEncoder(encDT, encCLK, encSW);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);

  //
  pointer2[0] = &tempSet;
  pointer2[1] = &tempRng;
  pointer2[2] = 0;

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
//  Serial.println("Loop");
  if(encoder->getButton() == ClickEncoder::Clicked)
    menu();
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    
    //Refresh temperature
    getTemp();
//    Serial.print(inTemp);
    updateDisplay();
    
    if ( (inTemp <= tempSet + tempRng) && (inTemp >= tempSet - tempRng)){
//      Serial.println("Within Range");
      heat(LOW);
      cool(LOW);
    }
    if (inTemp > tempSet + tempRng){
//      Serial.println("Too Hot");
      cool(HIGH);
      heat(LOW);
    }
    else if (inTemp < tempSet - tempRng){
//      Serial.println("Too Cold");
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
//  Serial.println("Heat: " + String(state));
  heatStatus = state;
  digitalWrite(heaterPin,!state);
  return;
}

void cool(bool state){
//  Serial.println("Cool: " + String(state));
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

void menuDisplay(char* heading, int data = 0, boolean edit = 0){
//  Serial.print("Menu Display: ");
//  Serial.print(heading);
//  Serial.println(data);
  display.clearDisplay();
  display.setCursor(0,0);
  //heading
  display.println(heading);
  //data
  display.setTextSize(2);
  display.println(data);
  display.setTextSize(DEFAULT_TEXT_SIZE);
  //edit
  if(edit) display.println("Editing");
  display.display();
}

void timerIsr() {
  encoder->service();
}

void menu(){
  short last = -1;
  short value = 0;
  int old = 0;
  while(true){
    // ----------------- BEGIN MENU LOOP ----------------- \\
    value += (encoder->getValue());
    int newValue = floor(value/4);
    if ( newValue > ITEMS-1 || newValue < 0){
      value = old;
      newValue = last; 
    }
    if (newValue != last){
      last = newValue;
      old = value;
      menuDisplay(pointer[newValue],*pointer2[newValue]);
    }
    if(encoder->getButton() == ClickEncoder::Clicked){
      if(newValue == 2) break;
      last = -1;
      int readValue = 0;
      while(encoder->getButton() == ClickEncoder::Open){
        readValue += encoder->getValue();
        menuDisplay(pointer[newValue],*pointer2[newValue]+(readValue/4), true);
      }
      *pointer2[newValue] += (readValue/4);
    }
    
  }
  // ----------------- END MENU LOOP ----------------- \\
  return;
}

//eof

