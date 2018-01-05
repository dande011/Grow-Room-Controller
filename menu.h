#ifndef _menu_h
#define _menu_h

void menuSetup();
void menu();

#define ITEMS 3
char item0[16] = "Set Temperature";
char item1[15] = "Temperature Range";
char exitItem[5] = "Exit";
char *pointer[ITEMS];

#endif

