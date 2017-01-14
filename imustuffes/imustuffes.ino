//#include <Wire.h>
#include <LSM6.h>
//#include <align_north.ino>

//short float velocity_x
//short float velocity_y
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

#include <Wire.h>


LSM6 imu;

char report[80];
int xAccel, yAccel, zAccel;
int xGyro, yGyro, zGyro;
void setup()
{
  Serial.begin(9600);
  Wire.begin();

  

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  imu.read();

  xAccel = imu.a.x * 0.00061;
  yAccel = imu.a.y * (0.061 * 9.81 / 1000.0);
  zAccel = imu.a.z * (0.061 * 9.81 / 1000.0);
  xGyro = imu.g.x * (4.375/ 1000);
  yGyro = imu.g.y * (4.375/ 1000);
  zGyro = imu.g.z * (4.375/ 1000);

  snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d",
    xAccel, yAccel, zAccel,
    xGyro, yGyro, zGyro);
  Serial.println(report);

  delay(100);
}
