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
  unsigned long loop_start_time = millis();

  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  ism330dhcx.getEvent(&accel, &gyro, &temp);

  sensors_event_t compass;
  lis3mdl.getEvent(&compass);

  while (gps.read())
    if (gps.newNMEAreceived())
      gps.parse(gps.lastNMEA());

  unsigned long data_end_time = millis();

  printf("compass: [%5.2f %5.2f %5.2f] (uH)\n\n",
           compass.magnetic.x, compass.magnetic.y, compass.magnetic.z);

  printf("temperature: %5.2f °C\n\n", temp.temperature);

  printf("acceleration: [%5.2f  %5.2f  %5.2f] (m/s^2)\n\n",
         accel.acceleration.x, accel.acceleration.y, accel.acceleration.z);
  
  printf("rotation: [%5.2f  %5.2f  %5.2f] °/s\n\n",
         gyro.gyro.x*180.0/PI, gyro.gyro.y*180.0/PI, gyro.gyro.z*180.0/PI);

  if (gps.fix)
  {
    printf("hdop: %7.3f\n", gps.HDOP);
    printf("vdop: %7.3f\n", gps.VDOP);
    printf("pdop: %9.5f\n\n", gps.PDOP);
    printf("# satellites: %d\n\n", gps.satellites);
    printf(" altitude: %8.2f m\n\n", gps.altitude);
    printf(" latitude: %3d° %2d' %6.3f\"\n", (int) (gps.latitude/100), ((int) gps.latitude)%100, 60*(gps.latitude - (int)gps.latitude));
    printf("longitude: %3d° %2d' %6.3f\"\n\n", (int) (gps.longitude/100), ((int) gps.longitude)%100, 60*(gps.longitude - (int)gps.longitude));
    printf("date: %2d-%02d-20%02d UTC\n\n", gps.month, gps.day, gps.year);
    printf("time: %2d:%02d:%02d.%03u UTC\n\n", gps.hour, gps.minute, gps.seconds, gps.milliseconds);
  }
  else
    printf("no GPS fix\n\n");

  unsigned long loop_end_time = millis();
 
  printf("       loop start time: %lu\n\n", loop_start_time);
  printf("  data acquisition time: %3lu ms\n", data_end_time - loop_start_time);
  printf("analysis and print time: %3lu ms\n", loop_end_time - data_end_time);
  printf("        total loop time: %3lu ms\n\n\n", loop_end_time - loop_start_time);

  delay(100 - (millis() - loop_start_time));
}