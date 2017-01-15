//#include <Wire.h>
#include <LSM6.h>
//#include <align_north.ino>


/*
The sensor outputs provided by the library are the raw
16-bit values obtained by concatenating the 8-bit high and
low accelerometer and gyro data registers. They can be
converted to units of g and dps (degrees per second) using
the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).
Example: An LSM6DS33 gives an accelerometer Z axis reading
of 16276 with its default full scale setting of +/- 2 g. The
LA_So specification in the LSM6DS33 datasheet (page 15)
states a conversion factor of 0.061 mg/LSB (least
significant bit) at this FS setting, so the raw reading of
16276 corresponds to 16276 * 0.061 = 992.8 mg = 0.9928 g.
*/
#include <SPI.h>
#include <Wire.h>
#include <SD.h>


LSM6 imu;
File mer;
int pin_motor_a_dir = 4;
int pin_motor_a_spd = 5;
int pin_motor_b_dir = 7;
int pin_motor_b_spd = 6;
int i=0;
float dist=0;
char report[80];
int xAccel, yAccel, zAccel;
float velocity_x=0.0;
float velocity_y=0.0;
float degreeTurn;
int xGyro, yGyro, zGyro;
  int sumsax[3]={0,0,0};
  int sumsay[3]={0,0,0};
  int sumsaz[3]={0,0,0};
  int sumsgx[3]={0,0,0};
void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  SD.begin(12);
  Serial.begin(9600);
  Wire.begin();

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}
void moveForwardUno(){
  delay(500);
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 97);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd,102);
  dist =0.0;
  delay(2600);
//  do{
//  xAccel = imu.a.x * 0.00061;
//  yAccel = imu.a.y * (0.061 * 9.81 / 1000.0);
//  zAccel = imu.a.z * (0.061 * 9.81 / 1000.0);
//  xGyro = imu.g.x * (4.375/ 1000);
//  //yGyro = imu.g.y * (4.375/ 1000);
//  //zGyro = imu.g.z * (4.375/ 1000);
//
//
//  //Serial.println(report);
//  
//  sumsay[2]=sumsay[1];
//  sumsaz[2]=sumsay[1];
//  sumsax[1]=sumsax[0];
//  sumsay[1]=sumsay[0];
//  sumsaz[1]=sumsaz[0];
//  sumsax[0]=xAccel;
//  sumsay[0]=yAccel;
//  sumsaz[0]=zAccel;
//  mer.println("1");
//  velocity_x=(sumsaz[0]+sumsaz[1]+sumsaz[2])*.1;
//  velocity_y=(sumsay[0]+sumsay[1]+sumsay[2])*.1;
//  mer.println("2");
//  sumsgx[2]=sumsgx[1];
//  sumsgx[1]=sumsgx[0];
//  sumsgx[0]=xGyro;
//  mer.println("3");
//  degreeTurn=(sumsgx[0]+sumsgx[1]+sumsgx[2])*.1;
// // mer.println(velocity_x);
////  mer.println(velocity_x*1000);
// // mer.println(velocity_y*1000);
//  //mer.println(degreeTurn);
//  delay(100);
//  mer.println(velocity_x);
//  dist+=velocity_x*.1;
//  mer.println(dist);
//  i++;
// 
//  }while(dist<.5);
// 
 // }
  
  while(1){
  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 0);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 0); 
  mer.close();
  digitalWrite(13, HIGH);
}
  }
void turnRight(){
void loop()
{
if(i==0){
  mer = SD.open("ted.txt", FILE_WRITE);
 mer.println("Test\n");
}

  if(!mer){
    digitalWrite(13, HIGH);
    return;
  }

  
  imu.read();

  moveForwardUno();
  
    





  
}
