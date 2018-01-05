#define OLED_RESET 4

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Default settings
int tempSet = 70;
int tempRng = 5;

//Variables
bool heatStatus = LOW;
bool coolStatus = LOW;

//Calibration Settings
int interval = 1000;
int inTemp = 0;
int inHumid = 0;
int outTemp = 0;
int outHumid = 0;
unsigned long previousMillis = 0;


//Pin # Settings
int outTempProbe = 0;
int heaterPin = 3;
int acPin = 4;

int ledPin = 13;

