#include <iostream>
#include <math.h>
#include <EEPROM.h>

//These are our global variables. 
int xpos = 0;
int ypos = 0;
int xfinal;
int yfinal;
bool grid[32][32];

//1 is north, 2 is east, 3 is south, 4 is west. initially we point north. 
int curdir = 1;

//This is for the motors. 
int pin_motor_a_dir = 4;
int pin_motor_a_spd = 5;
int pin_motor_b_dir = 7;
int pin_motor_b_spd = 6;

void AngleToPoint(float& angle, int& xfinal, int& yfinal);
void findPath();
void moveForwardUno();
bool canRight();
bool canForward();
int mapread(int x, int y);
void mapwrite(int x, int y, int data);

void setup() {
  pinMode(pin_motor_a_dir, OUTPUT);
  pinMode(pin_motor_a_spd, OUTPUT);
  pinMode(pin_motor_b_dir, OUTPUT);
  pinMode(pin_motor_b_spd, OUTPUT);
}

//This is the function that begins the attempt to find a path. 
void BeginRun(){
  //This angle will be given to us by the audio thing. Not quite sure how. 
  float angle;
  //We turn the angle into x- and y-coordinates.
  AngleToPoint(float& angle);
  void ReadGrid();
  //Then, we find the path. 
  findPath();
  
  return;
}

void ReadGrid(){
  int i, j;
  for(i=0;i < 32; ++i){
    for(j=0;j<32;++j){
      if(readMap(i,j) == 1){
        grid[i][j] = true;
      }
      else{
        grid[i][j] = false;
      }
    }
  }
}

//This function goes to the destination.
void findPath(){
  
  //So while we have not reached our final destination,
  while(xpos != xfinal && ypos != yfinal){ 
    //If we find that we can turn right,
    if (canRight()){ 
      //We turn right and then go forward.
      turnRight();
      //moveForwardUno is the funciton that moves Pete forward by one, done by Matt. 
      moveForwardUno();
    }
    //Otherwise, if we find that we can go forward,
    else if(canForward()){
      //We do it. 
      moveForwardUno();
    }
    //If there is no other option,
    else{
      //we turn left. 
      turnLeft();
      //If we also find that after turning left we can go forward, we do it.
      if(canForward()){
        moveForwardUno();
      }
    }   
  }
}

//The two functions below rotate Pete 90 degrees counterclockwise and clockwise respectively. 
void turnRight(){
  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 100);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd, 100);
  delay(5770);
  delay(500);
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 95);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd, 100);
  delay(500);
  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 0);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 0);
}

void turnLeft(){
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 96);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 96);
  delay(5530);
  delay(500);
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 95);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd, 100);
  delay(500);
  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 0);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 0);  
}

//This sees whether or not Pete can turn right or not. 
bool canRight(){
  //If we are pointed north and we find that the square east is not occupied, 
  if(curdir%4 == 1 && xpos != 31){
    if(grid[xpos+1][ypos]){
      return true;
    }
    return false;
  }
  
  //If we are pointed east and we find that the square south is vacant, 
  if(curdir%4 == 2 && ypos != 0){
    if(grid[xpos][ypos-1]){
      return true;
    }
    return false;
  }
  
  //If we are pointed south and we find that the square west is vacant, 
  if(currdir%4 == 3 && xpos != 0){
    if(grid[xpos-1][ypos]){
      return true;
    }
    return false;
  }
  //If we are pointed west and find that the square north is vacant,
  if(currdirr%4==0 && ypos != 31) {
    if(grid[xpos][ypos+1]){
      return true;
    }
    return false;
  }
  
  //Otherwise, that means we cannot turn right. 
  else{
    return false;
  }
    
}

//This check determines whether or not the square facing the bot is vacant.
bool canForward(){
  //If we are north,
  if(curdir%4 == 1){
    if(grid[xpos][ypos+1]){
      return true;
    }
    return false;
  }
  //If we are east,
  if(curdir%4 == 2){
    if(grid[xpos+1][ypos]){
      return true;
    }
    return false;
  }
  //If we are south,
  if(curdir%4 == 3){
    if(grid[xpos][ypos-1]){
      return true;
    }
    return false;
  }
  //If we are west,
  if(curdir%4 == 0){
    if(grid[xpos-1][ypos]){
      return true;
    }
    return false;
  }
  return false;
}

//This function converts the given angle into a point.
void AngleToPoint(float& angle){
  if(angle > 45){
    angle = angle * 3.14159265358979 / 180;
    //If the angle is more than 45, that means that it is on the axis y = 16.
    yfinal = 31;
    //Now, we use a Taylor Series Approximation to calculate thing instead of using tangent inverse.
        xfinal = int(31/tan(angle));
  }

  else if (angle < 45){
    angle = angle * 14159265358979 / 180;
    //If the angle is less than 45, that means that it is on the axis x = 16.
    xfinal = 31;
    yfinal = int(31*tan(angle));
  }

  //If we reach here, that means that the angle must be 45 degrees, which means that the point is (16, 16).
  else{
    xfinal = 31;
    yfinal = 31;
  }
}

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

void moveForwardUno(){
  delay(500);
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 97);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd,102);
  delay(2600);
  //This stops the motor.
  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 0);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 0); 
  mer.close();
  digitalWrite(13, HIGH);
  return;
}