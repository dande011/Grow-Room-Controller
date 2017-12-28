  Adafruit_SSD1306 display(OLED_RESET);
  
void displaySetup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //I2C address 0x3C
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  /*//draw Adafruit splash
  display.display();
  delay(2000);
  display.clearDisplay();
  */

  //draw logo
  display.clearDisplay();
  display.println("Starting up...");
  display.display();
  
  /*
  //draw Rapidstrike logo
  display.drawBitmap(0, 0, rapidstrike, rapidstrikeWPixels, rapidstrikeHPixels, 1);
  display.display();
  delay(1000);
  display.invertDisplay(true); //invert image (for teh cool factor)
  delay(1500);
  for(int i=0; i<64; i+=5){ // drop the image out of the frame
    display.clearDisplay();
    display.drawBitmap(0, i, rapidstrike, rapidstrikeWPixels, rapidstrikeHPixels, 1);
    display.display();
  }
  display.invertDisplay(false); //fix inversion
  display.clearDisplay();
  display.display();
  */
}
