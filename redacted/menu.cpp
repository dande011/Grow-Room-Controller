#include "menu.h"

char menuItem0[16] = "Set Temperature";
char menuItem1[15] = "Temperature Range";
char exitMenuItem[5] = "Exit";
char *pointer[ITEMS];

void menuSetup() {
  pointer[0]=menuItem0;
  pointer[1]=menuItem1;
  pointer[2]=exitMenuItem;
//  encoder = new ClickEncoder(encDT, encCLK, encSW);
}

void menu(){
//  String* 
  // if left, display array-1
  // if right, display array+1
  return;
}

void timerIsr() {
  encoder->service();
}
