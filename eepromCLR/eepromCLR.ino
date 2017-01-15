#include <EEPROM.h>
void setup() {
  int i = 0;
  while(i < 1024){
    EEPROM.write(i, 0);
    i++;
  }
}

void loop() {}
