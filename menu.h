#ifndef _menu_h
#define _menu_h

//Menu items
#define ITEMS 3
extern char menuItem0[16] = "Set Temperature";
extern char menuItem1[15] = "Temperature Range";
extern char exitMenuItem[5] = "Exit";
extern char *pointer[ITEMS];

void menuSetup();
void menu();
void timerISr();

#endif

