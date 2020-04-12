#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd( 7, 6, 5, 4, 3, 2);

const int DATA_BUFFER_SIZE = 10;//a word
const int DATA_INIT_ADDRESS = 1;//from adress 1
//
int readIndex = 0;
int totalCount=0;

void setup() {
  Serial.begin(9600);
  Serial.println("call setup().");
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // set up the LCD's nusmber of columns and rows:
  lcd.begin(16, 2);

  // initiate words array index to start 
  totalCount = EEPROM.read(0);
  if (totalCount < 0) { totalCount=0; }
  
  readIndex = millis()%totalCount;
  if (readIndex>=totalCount) { readIndex=0; }
}

void loop() {
  lcd.clear();
  
  //test get data
  char data[10] = "";
  EEPROM.get(DATA_INIT_ADDRESS + readIndex*DATA_BUFFER_SIZE, data);
  readIndex++;
  if (readIndex>=totalCount) { readIndex=0; }

  lcd.print(data); 
  delay(3000);
}
