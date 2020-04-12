#include <EEPROM.h>

const int DATA_BUFFER_SIZE = 10;//a word
const int DATA_INIT_ADDRESS = 1;//from adress 1

void setup() {
  Serial.begin(9600);
  Serial.println("call setup().");
  
  initData();
  debug();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void debug(){
  const int word_index = 39; // index is started from 0

  //get header
  int data_count = EEPROM.read(0);
  Serial.print("data_count is: ");Serial.println(data_count);
  
  //test get data
  char data[10] = "";
  EEPROM.get(DATA_INIT_ADDRESS + (data_count-1)*DATA_BUFFER_SIZE, data);
  Serial.print("test data is: ");Serial.print(data);Serial.print(". index is: ");Serial.println(word_index);
}

void initData(){
  int addr = DATA_INIT_ADDRESS;

  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  char data[][DATA_BUFFER_SIZE] = {"some", "will", "were", "green", "an", "has", "their", "come", "these", "up"
      , "get", "may", "four", "which", "had", "all", "six", "them", "five", "cut"
      , "not", "did", "off", "when", "now", "two", "its", "if", "write", "with"
      , "like", "run", "been", "tell", "made", "would", "saw", "how", "red", "got"
      , "into", "long", "find", "down", "him", "we", "of", "eat", "you", "draw"
      , "from", "then", "first", "your", "me", "us", "could", "any", "does", "today"
      , "call", "hot", "no", "be", "or", "why", "what", "her", "see", "one"
      , "have", "so", "make", "a", "I", "by", "look", "many", "can", "said"
      , "read", "brown", "as", "too", "on", "my", "sit", "yellow", "black", "am"};
      //, "say", "at", "to", "who", "want", "for", "is", "his", "three", "old"
      //, "she", "it", "yes", "do", "are", "big", "they", "where", "and", "about"
      //, "out", "this", "in", "blue", "that", "he", "go", "but", "ten", "use"
      //, "our", "was", "there", "the"};
  int data_count = sizeof(data)/DATA_BUFFER_SIZE;
  
  //write header
  EEPROM.write(0, data_count);

  //write data
  for (int i=0; i<data_count; i++){
    write2ROM(addr, *(data+i), DATA_BUFFER_SIZE);
  }
}

void write2ROM(int &addr, char data[10], const int buffer_size){
  for (int i=0; i<buffer_size; i++) {
    EEPROM.write(addr, *(data+i));
    addr++;
  }

  // 2020.4.12 I tried to yse EEPROM.put(data), but can't work correctly
  //EEPROM.put(addr, data);
  //addr+=buffer_size;
}
