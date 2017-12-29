#define OLED_RESET 4

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//Default settings
int tempSet = 65;
int tempRng = 5;

//Calibration Settings
int inTemp = 0;
int outTemp = 0;


//Pin # Settings
int inTempProbe = 0;
int outTempProbe = 0;
int heaterPin = 0;
int acPin = 0;

int ledPin = 13;
