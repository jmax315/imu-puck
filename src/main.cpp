#include <Arduino.h>
#include <LibPrintf.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_ISM330DHCX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GPS.h>


Adafruit_LIS3MDL lis3mdl;
Adafruit_ISM330DHCX ism330dhcx;
Adafruit_GPS gps(&Serial1);


void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  gps.begin(9600);

  if (!ism330dhcx.begin_I2C())
  {
    Serial.println("Failed to find ISM330DHCX chip");
    while (1) ;
  }

  Serial.println("ISM330DHCX Found!");

  ism330dhcx.configInt1(false, false, true); // accelerometer DRDY on INT1
  ism330dhcx.configInt2(false, true, false); // gyro DRDY on INT2

  if (!lis3mdl.begin_I2C())
  {
    Serial.println("Failed to find LIS3MDL chip");
    while (1) ;
  }
  Serial.println("LIS3MDL Found!");

  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
  lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true, // enable z axis
                          true,               // polarity
                          false,              // don't latch
                          true);              // enabled!
}

void loop()
{
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  ism330dhcx.getEvent(&accel, &gyro, &temp);

  sensors_event_t compass;
  lis3mdl.getEvent(&compass);

  while(gps.read())
    if (gps.newNMEAreceived())
      gps.parse(gps.lastNMEA()); 
  
  printf("Bx: %5.2f  By: %5.2f  Bz: %5.2f\n\n", compass.magnetic.x, compass.magnetic.y, compass.magnetic.z);

  printf("T: %5.2f\n", temp.temperature);
  printf("Ax: %5.2f  Ay: %5.2f  Az: %5.2f  m/s^2\n", accel.acceleration.x, accel.acceleration.y, accel.acceleration.z);
  printf("Rx: %5.2f  Ry: %5.2f  Rz: %5.2f rad/s\n\n", gyro.gyro.x, gyro.gyro.y, gyro.gyro.z);

  printf("Fix: %s\n", gps.fix? "true": "false");
  printf("alt: %8.2f  lat: %8.2f  long: %8.2f\n", (float) gps.altitude, (float) gps.latitude, (float) gps.longitude);
  printf("%2d-%02d-20%02d  %2d:%02d:%02d.%03d\n\n", gps.month, gps.day,gps.year, gps.hour,gps.minute,gps.seconds,gps.milliseconds);

  delay(100);
}