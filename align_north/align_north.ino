#include <Wire.h>
#include <LIS3MDL.h>

LIS3MDL mag;
int maxval = 0;

int pin_motor_a_dir = 4;
int pin_motor_a_spd = 5;
int pin_motor_b_dir = 7;
int pin_motor_b_spd = 6;

void setup() {
  pinMode(pin_motor_a_dir, OUTPUT);
  pinMode(pin_motor_a_spd, OUTPUT);
  pinMode(pin_motor_b_dir, OUTPUT);
  pinMode(pin_motor_b_spd, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  magread:
  while (!mag.init()){}
  mag.enableDefault();
  mag.read();
}

void loop() {
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 255);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 255);

  while(mag.m.x < 2000){
    mag.read();
  }

  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 100);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 100);
  
  //Find north
  maxval = mag.m.x;
  while(mag.m.x > 2000){
    mag.read();
    Serial.print(mag.m.x);
    Serial.print(":");
    Serial.println(maxval);
    if(mag.m.x > maxval){
      maxval = mag.m.x;
    }
  }

  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 100);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd, 100);

  while(mag.m.x < (maxval - 300)){
    mag.read();
  }

  analogWrite(pin_motor_a_spd, 0);
  analogWrite(pin_motor_b_spd, 0);

  while(1){}
}
