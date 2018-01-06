#define OLED_RESET 4

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define DEFAULT_TEXT_SIZE 1

ClickEncoder *encoder;

//Default settings
short tempSet = 70;
short tempRng = 5;

//Variables
bool heatStatus = LOW;
bool coolStatus = LOW;

//Calibration Settings
short interval = 1000;
short inTemp = 0;
short inHumid = 0;
short outTemp = 0;
short outHumid = 0;
unsigned long previousMillis = 0;


//Pin # Settings
short outTempProbe = 0;
short heaterPin = 5;
short acPin = 4;

short ledPin = 13;

short encDT = 8;
short encCLK = 9;
short encSW = 7;


//Menu Variables
#define ITEMS 3
char menuItem0[16] = "Set Temperature";
char menuItem1[114] = "Temperature Range";
char exitMenuItem[5] = "Exit";
char *pointer[ITEMS];
short *pointer2[ITEMS];

