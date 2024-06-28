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

  gps.begin(9600);

  if (!ism330dhcx.begin_I2C())
  {
    Serial.println("Failed to find ISM330DHCX chip");
    for (;;)
      ;
  }

  Serial.println("ISM330DHCX Found!");

  ism330dhcx.configInt1(false, false, true); // accelerometer DRDY on INT1
  ism330dhcx.configInt2(false, true, false); // gyro DRDY on INT2

  if (!lis3mdl.begin_I2C())
  {
    Serial.println("Failed to find LIS3MDL chip");
    for (;;)
      ;
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

  while (gps.read())
    if (gps.newNMEAreceived())
      gps.parse(gps.lastNMEA());

  printf("compass (uH): [%5.2f %5.2f %5.2f]\n\n",
         compass.magnetic.x, compass.magnetic.y, compass.magnetic.z);

  printf("temperature (C): %5.2f\n", temp.temperature);
  printf("acceleration (m/s^2): [%5.2f  %5.2f  %5.2f]\n",
         accel.acceleration.x, accel.acceleration.y, accel.acceleration.z);
  printf("rotation (rad/s): [%5.2f  %5.2f  %5.2f]\n\n",
         gyro.gyro.x, gyro.gyro.y, gyro.gyro.z);

  if (gps.fix)
  {
    printf("altitude (m): %8.2f\n", gps.altitude);
    printf("latitude (deg): %8.2f  longitude: %8.2f\n", gps.latitude, gps.longitude); // not really degrees, but related.
    printf("%2d-%02d-20%02d\n", gps.month, gps.day, gps.year);
    printf("%2d:%02d:%02d.%03u UTC\n\n", gps.hour, gps.minute, gps.seconds, gps.milliseconds);
  }
  else
    printf("no GPS fix\n");

  delay(100);
}