#include <EEPROM.h>

int mapread(int x, int y);
void mapwrite(int x, int y, int data);

int mapread(int x, int y){
  y = 31 - y;
  int addr = 0;

  if(y != 0){
    addr = 32 * y;
    addr += x;
  }
  else{
    addr = x;
  }
  if(addr > 1023){
    return 0;
  }
  return EEPROM.read(addr);
}

void mapwrite(int x, int y, int data){
  y = 31 - y;
  int addr = 0;

  if(y != 0){
    addr = 32 * y;
    addr += x;
  }
  else{
    addr = x;
  }
  if(addr > 1023){
    return;
  }
  EEPROM.write(addr, data);
  return;
}

void setup() {
  
}

void loop() {
  //ignore
}


