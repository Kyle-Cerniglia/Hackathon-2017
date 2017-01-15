#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SD.h>
#include <SPI.h>
#include <Servo.h>
#include <EEPROM.h>

#define RAD 0.01745

Servo servo1;//Straight is 70', 0-140 0 = right 140 = left

int x = 0;
int y = 0;
int data[2][142];//degree, range or x,y
int data2[2][142];
int range = 0;
int i = 0;
int j = 0;
int k = 0;
int cnt = 0;
int x_c = 16;
int y_c = 0;
int sum = 0;

bool even(int in);
int mapread(int x, int y);
void mapwrite(int x, int y, int data);
void rangefind();

void setup() {
  pinMode(0, INPUT);    //encoder 1b
  pinMode(1, INPUT);    //encoder 1a
  pinMode(4, OUTPUT);   //motor2d
  pinMode(5, OUTPUT);   //motor2s
  pinMode(6, OUTPUT);   //motor1s
  pinMode(7, OUTPUT);   //motor1d
  pinMode(8, INPUT);    //encoder 2b
  pinMode(9, OUTPUT);   //servo
  pinMode(10, INPUT);    //encoder 2a
  pinMode(11, INPUT);    //us trigger
  pinMode(12, OUTPUT);   //sd cs
  pinMode(13, OUTPUT);   //us ping
  pinMode(20, INPUT);    //m4
  pinMode(21, INPUT);    //m3
  pinMode(23, INPUT);    //m2

  digitalWrite(13, LOW);
  
  SD.begin(12);
  Serial.begin(9600);
  servo1.attach(9);

  //Start program
  rangefind();
  process();
  digitalWrite(13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void process()
{
    //Reset
    k = 0;
    while(k < 142){
        data2[0][k] = -1;
        data2[1][k] = -1;
        k++;
    }
    k = 0;    

    //Point conversion=================================================
    i = 0;
    j = 0;
    while(i < 71){
        if(data[1][i] < 200){
            data[0][i] = 71 - data[0][i];
            y = data[1][i] * sin(RAD * data[0][i]);
            x = data[1][i] * cos(RAD * data[0][i]) + 200;

            data[0][j] = x;
            data[1][j] = y;
            j++;
        }
        i++;
    }
    i = 0;

    if(data[1][71] < 200){
        data[0][j] = 200;
    }
    j++;

    i = 72;
    while(i < 142){
        if(data[1][i] < 200){
            data[0][i] = data[0][i] - 71;
            y = data[1][i] * sin(RAD * data[0][i]);
            x = 200 - data[1][i] * cos(RAD * data[0][i]);

            data[0][j] = x;
            data[1][j] = y;
            j++;

        }
        i++;
    }

    while(j < i){
        data[0][j] = -1;
        data[1][j] = -1;
        j++;
    }

    i = 0;
    j = 0;
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //400x200->200x100========================================
    i = 0;
    j = 0;
    cnt = 0;
    sum = 0;
    x = 0;
    y = 0;

    while(i < 142){
        //Q1
        if((j == 0) && (data[0][i] != 0 && data[1][i] != 0) && (even(data[0][i]) == false && even(data[1][i]) == false)){
            x = 0;
            sum = data[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data[0][i] = x;
            data[1][i] = y;
            j++;
        }
        //Q2
        if((j == 0) && (data[1][i] != 0) && ((data[0][i] == 0 && even(data[1][i]) == false) || (even(data[0][i]) == true && even(data[1][i]) == false))){
            x = 0;
            sum = data[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data[0][i] = x;
            data[1][i] = y;
            j++;
        }
        //Q3
        if((j == 0) && ((data[0][i] == 0 && data[1][i] == 0) || (data[0][i] == 0 && even(data[1][i]) == true) || (even(data[0][i]) == true && even(data[1][i]) == true) || (even(data[0][i]) == true && data[1][i] == 0))){
            x = 0;
            sum = data[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data[0][i] = x;
            data[1][i] = y;
            j++;
        }
        //Q4
        if((j == 0) && (data[0][i] != 0) && ((even(data[0][i]) == false && data[1][i] == 0) || (even(data[0][i]) == false && even(data[1][i]) == true) || (even(data[0][i]) == false && data[1][i] == 0))){
            x = 0;
            sum = data[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data[0][i] = x;
            data[1][i] = y;
            j++;
        }
        j = 0;
        i++;
    }
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //Filter 1=================================================================
    j = 0;
    i = 0;
    x = 0;
    y = 0;
    while(i < 142){
        x = data[0][i];
        y = data[0][i];
        j = i + 1;
        if(data[0][i] != -1 && data[1][i] != -1){
            while(j < 142){
                if(data[0][j] == data[0][i] && data[1][j] == data[1][i]){
                    data[0][j] = -1;
                    data[1][j] = -1;
                }
                j++;
            }
            j = 0;
        }
        i++;
    }
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //Clean 1==================================================================

    x = 0;
    y = 0;
    i = 0;
    j = 0;
    k = 0;
    cnt = 0;
    sum = 0;
    while(cnt < 142){
        j = 0;
        if(data[0][i] == -1 || data[1][i] == -1){
            i++;
        }
        else{
            while(j < 142){
                //Invalid
                if(data[0][j] == -1 || data[0][j] == -1){
                    j++;
                }
                //Top left
                else if(data[0][i] == 1 && data[1][i] == 99){
                    if(data[0][j] == 2 && data[1][j] == 99){
                        sum++;
                    }
                    if(data[0][j] == 1 && data[1][j] == 98){
                        sum++;
                    }
                    if(data[0][j] == 2 && data[1][j] == 98){
                        sum++;
                    }
                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //Top right
                else if(data[0][i] == 199 && data[1][i] == 99){
                    if(data[0][j] == 198 && data[1][j] == 99){
                        sum++;
                    }
                    if(data[0][j] == 198 && data[1][j] == 98){
                        sum++;
                    }
                    if(data[0][j] == 199 && data[1][j] == 98){
                        sum++;
                    }
                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //Bottom left
                else if(data[0][i] == 1 && data[1][i] == 0){
                    if(data[0][j] == 1 && data[1][j] == 1){
                        sum++;
                    }
                    if(data[0][j] == 2 && data[1][j] == 1){
                        sum++;
                    }
                    if(data[0][j] == 2 && data[1][j] == 0){
                        sum++;
                    }
                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //Bottom right
                else if(data[0][i] == 199 && data[1][i] == 0){
                    if(data[0][j] == 199 && data[1][j] == 1){
                        sum++;
                    }
                    if(data[0][j] == 198 && data[1][j] == 1){
                        sum++;
                    }
                    if(data[0][j] == 198 && data[1][j] == 0){
                        sum++;
                    }
                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //Top
                else if(data[1][i] == 99){
                    if((data[0][i] - 1) == data[0][j] && 99 == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] + 1) == data[0][j] && 99 == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] - 1) == data[0][j] && 98 == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == data[0][j] && 98 == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] + 1) == data[0][j] && 98 == data[1][j]){
                        sum++;
                    }

                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //Bottom
                else if(data[1][i] == 0){
                    if((data[0][i] - 1) == data[0][j] && 0 == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] + 1) == data[0][j] && 0 == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] - 1) == data[0][j] && 1 == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == data[0][j] && 1 == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] + 1) == data[0][j] && 1 == data[1][j]){
                        sum++;
                    }

                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //Left
                else if(data[0][i] == 1){
                    if(data[0][i] == 1 && (data[1][i] + 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 1 && (data[1][i] - 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 2 && (data[1][i] + 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 2 && data[1][i] == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 2 && (data[1][i] - 1) == data[1][j]){
                        sum++;
                    }

                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //Right
                else if(data[0][i] == 199){
                    if(data[0][i] == 199 && (data[1][i] + 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 199 && (data[1][i] - 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 198 && (data[1][i] + 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 198 && data[1][i] == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == 198 && (data[1][i] - 1) == data[1][j]){
                        sum++;
                    }

                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        j++;
                    }
                    sum = 0;
                }
                //All others
                else{
                    if((data[0][i] - 1) == data[0][j] && (data[1][i] + 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == data[0][j] && (data[1][i] + 1) == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] + 1) == data[0][j] && (data[1][i] + 1) == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] - 1) == data[0][j] && data[1][i] == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] + 1) == data[0][j] && data[1][i] == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] - 1) == data[0][j] && (data[1][i] - 1) == data[1][j]){
                        sum++;
                    }
                    if(data[0][i] == data[0][j] && (data[1][i] - 1) == data[1][j]){
                        sum++;
                    }
                    if((data[0][i] + 1) == data[0][j] && (data[1][i] - 1) == data[1][j]){
                        sum++;
                    }
                    if(sum == 0){
                        data[0][i] = -1;
                        data[1][i] = -1;
                        i++;
                        j = 142;
                    }
                    else{
                        data2[0][k] = data[0][i];
                        data2[1][k] = data[1][i];
                        k++;
                        j++;
                    }
                    sum = 0;
                }
                j++;
            }
        }
        cnt++;
    }
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //Filter 2=================================================================
    j = 0;
    i = 0;
    k = 0;
    x = 0;
    y = 0;
    while(k < 142){
        x = data2[0][k];
        y = data2[1][k];
        j = k + 1;
        if(data2[0][k] != -1 && data2[1][k] != -1){
            while(j < 142){
                if(data2[0][j] == data2[0][k] && data2[1][j] == data2[1][k]){
                    data2[0][j] = -1;
                    data2[1][j] = -1;
                }
                j++;
            }
            j = 0;
        }
        k++;
    }

    //Reset
    i = 0;
    while(i < 142){
        data[0][i] = -1;
        data[1][i] = -1;
        i++;
    }
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //200x100->100x50==========================================
    i = 0;
    j = 0;
    cnt = 0;
    sum = 0;
    x = 0;
    y = 0;

    while(i < 142){
        //Q1
        if((j == 0) && (data2[0][i] != 0 && data2[1][i] != 0) && (even(data2[0][i]) == false && even(data2[1][i]) == false)){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data2[0][i] = x;
            data2[1][i] = y;
            j++;
        }
        //Q2
        if((j == 0) && (data2[1][i] != 0) && ((data2[0][i] == 0 && even(data2[1][i]) == false) || (even(data2[0][i]) == true && even(data2[1][i]) == false))){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data2[0][i] = x;
            data2[1][i] = y;
            j++;
        }
        //Q3
        if((j == 0) && ((data2[0][i] == 0 && data2[1][i] == 0) || (data2[0][i] == 0 && even(data2[1][i]) == true) || (even(data2[0][i]) == true && even(data2[1][i]) == true) || (even(data2[0][i]) == true && data2[1][i] == 0))){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data2[0][i] = x;
            data2[1][i] = y;
            j++;
        }
        //Q4
        if((j == 0) && (data2[0][i] != 0) && ((even(data2[0][i]) == false && data2[1][i] == 0) || (even(data2[0][i]) == false && even(data2[1][i]) == true) || (even(data2[0][i]) == false && data2[1][i] == 0))){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data2[0][i] = x;
            data2[1][i] = y;
            j++;
        }
        j = 0;
        i++;
    }
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //Filter 1=================================================================
    j = 0;
    i = 0;
    x = 0;
    y = 0;
    while(i < 142){
        x = data2[0][i];
        y = data2[0][i];
        j = i + 1;
        if(data2[0][i] == 0 && data2[1][i] == 0){
            data2[0][i] = -1;
            data2[1][i] = -1;
        }
        if(data2[0][i] != -1 && data2[1][i] != -1){
            while(j < 142){
                if(data2[0][j] == data2[0][i] && data2[1][j] == data2[1][i]){
                    data2[0][j] = -1;
                    data2[1][j] = -1;
                }
                j++;
            }
            j = 0;
        }
        i++;
    }

    //100x50->50x25
    i = 0;
    j = 0;
    cnt = 0;
    sum = 0;
    x = 0;
    y = 0;

    while(i < 142){
        //Q1
        if((j == 0) && (data2[0][i] != 0 && data2[1][i] != 0) && (even(data2[0][i]) == false && even(data2[1][i]) == false)){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data2[0][i] = x;
            data2[1][i] = y;
            j++;
        }
        //Q2
        if((j == 0) && (data2[1][i] != 0) && ((data2[0][i] == 0 && even(data2[1][i]) == false) || (even(data2[0][i]) == true && even(data2[1][i]) == false))){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data2[0][i] = x;
            data2[1][i] = y;
            j++;
        }
        //Q3
        if((j == 0) && ((data2[0][i] == 0 && data2[1][i] == 0) || (data2[0][i] == 0 && even(data2[1][i]) == true) || (even(data2[0][i]) == true && even(data2[1][i]) == true) || (even(data2[0][i]) == true && data2[1][i] == 0))){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data2[0][i] = x;
            data2[1][i] = y;
            j++;
        }
        //Q4
        if((j == 0) && (data2[0][i] != 0) && ((even(data2[0][i]) == false && data2[1][i] == 0) || (even(data2[0][i]) == false && even(data2[1][i]) == true) || (even(data2[0][i]) == false && data2[1][i] == 0))){
            x = 0;
            sum = data2[0][i];
            while(sum > 1){
                sum -= 2;
                x++;
            }
            y = 0;
            sum = data2[1][i];
            while(sum > 1){
                sum-= 2;
                y++;
            }
            data[0][i] = x;
            data[1][i] = y;
            j++;
        }
        j = 0;
        i++;
    }
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //Filter 1=================================================================
    j = 0;
    i = 0;
    x = 0;
    y = 0;
    while(i < 142){
        x = data[0][i];
        y = data[0][i];
        j = i + 1;
        if(data[0][i] == 0 && data[1][i] == 0){
            data[0][i] = -1;
            data[1][i] = -1;
        }
        if(data[0][i] != -1 && data[1][i] != -1){
            while(j < 142){
                if(data[0][j] == data[0][i] && data[1][j] == data[1][i]){
                    data[0][j] = -1;
                    data[1][j] = -1;
                }
                j++;
            }
            j = 0;
        }
        i++;
    }

    i = 0;
    x = 0;
    y = 0;
/*
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
*/
    //Store====================================
    while(i < 142){
        if(data[0][i] != -1 && data[1][i] != -1){
            x = data[0][i] * (32.0 / 50.0);
            y = data[1][i] * (32.0 / 50.0);
            x += x_c;
            y += y_c;
            if(x >= 0 && y >= 0 && x < 32 && y < 32){
                //Write data
                mapwrite(x, y, 1);
            }
        }
        i++;
    }

    return;
}

bool even(int in){
    if(in % 2 != 0){
        return false;
    }
    else{
        return true;
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

void rangefind(){
  //Rangefinding
  i = 0;
  
  while(i < 142){
    servo1.write(i);
    delay(10);
   
  
    while(cnt < 24){
      digitalWrite(13, LOW);
      delayMicroseconds(2);
      digitalWrite(13, HIGH);
      delayMicroseconds(10);
      digitalWrite(13, LOW);
      range = pulseIn(11, HIGH, 30000);
      
      range /= 59;
      sum += range;
      cnt++;
    }
    
    range = sum / 24;
    data[0][i] = i;
    data[1][i] = range;

    i++;
    
    sum = 0;
    cnt = 0;
    range = 0;
    
  }
  i = 0;
  return;
}

