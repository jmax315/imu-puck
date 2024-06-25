#include <Arduino.h>
#include <Wire.h>

int LIS3MDL_i = 0;

unsigned char LIS3MDL_address = 0x1c;
unsigned char LIS3MDL_registers[] = {
    0x05,
    0x06,
    0x07,
    0x08,
    0x09,
    0x0a,

    0x0f,

    0x20,
    0x21,
    0x22,
    0x23,
    0x24,

    0x27,
    0x28,
    0x29,
    0x2a,
    0x2b,
    0x2c,
    0x2d,
    0x2e,
    0x2f,
    0x30,
    0x31,
    0x32,
    0x33,
};

// void setup()
// {
//   LIS3MDL_i = 0;

//   Serial.begin(115200);
//   Serial1.begin(9600);

//   Wire.begin();
//   Wire.beginTransmission(LIS3MDL_address);
//   Wire.write(0x20);
//   Wire.write(0xfe);
//   Wire.endTransmission();
// }

// // const unsigned addr_1 = 0x1c;
// const unsigned addr_2 = 0x6a;

// void loop()
// {
  // while (Serial.available() > 0 && Serial1.availableForWrite() > 0)
  //   Serial1.write((unsigned char)Serial.read());

  // while (Serial1.available() > 0 && Serial.availableForWrite() > 0)
  //   Serial.write((unsigned char)Serial1.read());

  // Wire.beginTransmission(LIS3MDL_address);
  // Wire.write(LIS3MDL_registers[LIS3MDL_i]);
  // Wire.endTransmission();

  // Wire.requestFrom(LIS3MDL_address, 1);
  // int value = Wire.read();

  // Serial.printf("%8u: i2c %02x:%02x -> 0x%02x\n", millis(), LIS3MDL_address, LIS3MDL_registers[LIS3MDL_i], value);

  // if (++LIS3MDL_i >= sizeof(LIS3MDL_registers)/sizeof(LIS3MDL_registers[0])) {
  //   LIS3MDL_i = 0;
  //   Serial.printf("\n");
  //   delay(200);
  // }


/////////////////////////////////////////////////////////////
// Basic demo for magnetometer readings from Adafruit LIS3MDL

// #include <Wire.h>
// #include <Adafruit_LIS3MDL.h>
// #include <Adafruit_Sensor.h>

// Adafruit_LIS3MDL lis3mdl;

// #define LIS3MDL_CLK 13
// #define LIS3MDL_MISO 12
// #define LIS3MDL_MOSI 11
// #define LIS3MDL_CS 10

//   void setup(void)
//   {
//     Serial.begin(115200);
//     while (!Serial)
//       delay(10); // will pause Zero, Leonardo, etc until serial console opens

//     Serial.println("Adafruit LIS3MDL test!");

//     // Try to initialize!
//     if (!lis3mdl.begin_I2C())
//     { // hardware I2C mode, can pass in address & alt Wire
//       // if (! lis3mdl.begin_SPI(LIS3MDL_CS)) {  // hardware SPI mode
//       // if (! lis3mdl.begin_SPI(LIS3MDL_CS, LIS3MDL_CLK, LIS3MDL_MISO, LIS3MDL_MOSI)) { // soft SPI
//       Serial.println("Failed to find LIS3MDL chip");
//       while (1)
//       {
//         delay(10);
//       }
//     }
//     Serial.println("LIS3MDL Found!");

//     lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
//     Serial.print("Performance mode set to: ");
//     switch (lis3mdl.getPerformanceMode())
//     {
//     case LIS3MDL_LOWPOWERMODE:
//       Serial.println("Low");
//       break;
//     case LIS3MDL_MEDIUMMODE:
//       Serial.println("Medium");
//       break;
//     case LIS3MDL_HIGHMODE:
//       Serial.println("High");
//       break;
//     case LIS3MDL_ULTRAHIGHMODE:
//       Serial.println("Ultra-High");
//       break;
//     }

//     lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
//     Serial.print("Operation mode set to: ");
//     // Single shot mode will complete conversion and go into power down
//     switch (lis3mdl.getOperationMode())
//     {
//     case LIS3MDL_CONTINUOUSMODE:
//       Serial.println("Continuous");
//       break;
//     case LIS3MDL_SINGLEMODE:
//       Serial.println("Single mode");
//       break;
//     case LIS3MDL_POWERDOWNMODE:
//       Serial.println("Power-down");
//       break;
//     }

//     lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);
//     // You can check the datarate by looking at the frequency of the DRDY pin
//     Serial.print("Data rate set to: ");
//     switch (lis3mdl.getDataRate())
//     {
//     case LIS3MDL_DATARATE_0_625_HZ:
//       Serial.println("0.625 Hz");
//       break;
//     case LIS3MDL_DATARATE_1_25_HZ:
//       Serial.println("1.25 Hz");
//       break;
//     case LIS3MDL_DATARATE_2_5_HZ:
//       Serial.println("2.5 Hz");
//       break;
//     case LIS3MDL_DATARATE_5_HZ:
//       Serial.println("5 Hz");
//       break;
//     case LIS3MDL_DATARATE_10_HZ:
//       Serial.println("10 Hz");
//       break;
//     case LIS3MDL_DATARATE_20_HZ:
//       Serial.println("20 Hz");
//       break;
//     case LIS3MDL_DATARATE_40_HZ:
//       Serial.println("40 Hz");
//       break;
//     case LIS3MDL_DATARATE_80_HZ:
//       Serial.println("80 Hz");
//       break;
//     case LIS3MDL_DATARATE_155_HZ:
//       Serial.println("155 Hz");
//       break;
//     case LIS3MDL_DATARATE_300_HZ:
//       Serial.println("300 Hz");
//       break;
//     case LIS3MDL_DATARATE_560_HZ:
//       Serial.println("560 Hz");
//       break;
//     case LIS3MDL_DATARATE_1000_HZ:
//       Serial.println("1000 Hz");
//       break;
//     }

//     lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
//     Serial.print("Range set to: ");
//     switch (lis3mdl.getRange())
//     {
//     case LIS3MDL_RANGE_4_GAUSS:
//       Serial.println("+-4 gauss");
//       break;
//     case LIS3MDL_RANGE_8_GAUSS:
//       Serial.println("+-8 gauss");
//       break;
//     case LIS3MDL_RANGE_12_GAUSS:
//       Serial.println("+-12 gauss");
//       break;
//     case LIS3MDL_RANGE_16_GAUSS:
//       Serial.println("+-16 gauss");
//       break;
//     }

//     lis3mdl.setIntThreshold(500);
//     lis3mdl.configInterrupt(false, false, true, // enable z axis
//                             true,               // polarity
//                             false,              // don't latch
//                             true);              // enabled!
//   }

//   void loop()
//   {
//     lis3mdl.read(); // get X Y and Z data at once
//     // Then print out the raw data
//     Serial.print("\nX:  ");
//     Serial.print(lis3mdl.x);
//     Serial.print("  \tY:  ");
//     Serial.print(lis3mdl.y);
//     Serial.print("  \tZ:  ");
//     Serial.println(lis3mdl.z);

//     /* Or....get a new sensor event, normalized to uTesla */
//     sensors_event_t event;

//     lis3mdl.getEvent(&event);
//     /* Display the results (magnetic field is measured in uTesla) */
//     Serial.print("X: ");
//     Serial.print(event.magnetic.x);
//     Serial.print(" \tY: ");
//     Serial.print(event.magnetic.y);
//     Serial.print(" \tZ: ");
//     Serial.print(event.magnetic.z);
//     Serial.println(" uTesla ");

//     delay(100);
//     Serial.println();
//   }

///////////////////////////////////////////////////////////////////////////////////

// Basic demo for accelerometer/gyro readings from Adafruit ISM330DHCX

#include <Adafruit_ISM330DHCX.h>

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11

Adafruit_ISM330DHCX ism330dhcx;
void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit ISM330DHCX test!");

  if (!ism330dhcx.begin_I2C()) {
    // if (!ism330dhcx.begin_SPI(LSM_CS)) {
    // if (!ism330dhcx.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    Serial.println("Failed to find ISM330DHCX chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("ISM330DHCX Found!");

  // ism330dhcx.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (ism330dhcx.getAccelRange()) {
  case LSM6DS_ACCEL_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case LSM6DS_ACCEL_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case LSM6DS_ACCEL_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case LSM6DS_ACCEL_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // ism330dhcx.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
  Serial.print("Gyro range set to: ");
  switch (ism330dhcx.getGyroRange()) {
  case LSM6DS_GYRO_RANGE_125_DPS:
    Serial.println("125 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_250_DPS:
    Serial.println("250 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_500_DPS:
    Serial.println("500 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_1000_DPS:
    Serial.println("1000 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_2000_DPS:
    Serial.println("2000 degrees/s");
    break;
  case ISM330DHCX_GYRO_RANGE_4000_DPS:
    Serial.println("4000 degrees/s");
    break;
  }

  // ism330dhcx.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Accelerometer data rate set to: ");
  switch (ism330dhcx.getAccelDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  // ism330dhcx.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Gyro data rate set to: ");
  switch (ism330dhcx.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  ism330dhcx.configInt1(false, false, true); // accelerometer DRDY on INT1
  ism330dhcx.configInt2(false, true, false); // gyro DRDY on INT2
}

void loop() {
  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  ism330dhcx.getEvent(&accel, &gyro, &temp);

  Serial.print("\t\tTemperature ");
  Serial.print(temp.temperature);
  Serial.println(" deg C");

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tAccel X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" \tY: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" \tZ: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2 ");

  /* Display the results (rotation is measured in rad/s) */
  Serial.print("\t\tGyro X: ");
  Serial.print(gyro.gyro.x);
  Serial.print(" \tY: ");
  Serial.print(gyro.gyro.y);
  Serial.print(" \tZ: ");
  Serial.print(gyro.gyro.z);
  Serial.println(" radians/s ");
  Serial.println();

  delay(100);

  //  // serial plotter friendly format

  //  Serial.print(temp.temperature);
  //  Serial.print(",");

  //  Serial.print(accel.acceleration.x);
  //  Serial.print(","); Serial.print(accel.acceleration.y);
  //  Serial.print(","); Serial.print(accel.acceleration.z);
  //  Serial.print(",");

  // Serial.print(gyro.gyro.x);
  // Serial.print(","); Serial.print(gyro.gyro.y);
  // Serial.print(","); Serial.print(gyro.gyro.z);
  // Serial.println();
  //  delayMicroseconds(10000);
}
