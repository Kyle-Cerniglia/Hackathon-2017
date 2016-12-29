#include <SD.h>
#include <SPI.h>
#include <Servo.h>

Servo servo1;//Straight is 70', 0-140 0 = right 140 = left
File rangedata;

int delayus = 0;
int range = 0;
int range_s = 0;
int count = 0;
int range_a[142];
int degree = 0;
int x = 0;
int y = 0;

void setup() {
  
  pinMode(0, INPUT);    //EncoderA
  pinMode(1, INPUT);    //EncoderB
  pinMode(4, OUTPUT);   //D1
  pinMode(5, OUTPUT);   //S1
  pinMode(6, OUTPUT);   //S2
  pinMode(7, OUTPUT);   //D2
  pinMode(8, OUTPUT);   //SDCS
  pinMode(9, OUTPUT);   //MAGCS
  pinMode(A0, OUTPUT);  //SOUT
  pinMode(A1, INPUT);   //SIN
  //pinMode(10, OUTPUT);  //Servo
  pinMode(13, OUTPUT);  //LED

  digitalWrite(13, LOW);
  
  servo1.attach(10);
  SD.begin(8);
  Serial.begin(9600);


  
}

void loop() {

  //Rangefinding
  degree = 0;
  
  while(degree < 142){
    servo1.write(degree);
    delay(10);
   
  
    while(count < 50){
      digitalWrite(A0, LOW);
      delayMicroseconds(2);
      digitalWrite(A0, HIGH);
      delayMicroseconds(10);
      digitalWrite(A0, LOW);
      delayus = pulseIn(A1, HIGH, 30000);
      
      range = delayus;
      range /= 59;
      range_s += range;
      count++;
    }
    
    range = range_s / 50;
    range_a[degree] = range;

    degree++;
    
    range_s = 0;
    count = 0;
    range = 0;
    
  }
  degree = 0;
  
/*
  degree = 141;
  while(degree >= 0){
    Serial.print(range_a[degree]);
    Serial.print(" ");
    degree--;
  }
  degree = 0;
  Serial.println();
*/

//SD Card
  rangedata = SD.open("rangdata.txt", FILE_WRITE);
  if(rangedata){
    degree = 0;
    while(degree < 142){
      rangedata.print(x);
      rangedata.print(":");
      rangedata.print(y);
      rangedata.print(":");
      rangedata.print(degree);
      rangedata.print(":");
      rangedata.print(range_a[degree]);
      rangedata.println(";");
      degree++;
    }
    degree = 0;
    rangedata.close();
  }
  else{
    digitalWrite(13, HIGH);
    while(1){}
  }

}
