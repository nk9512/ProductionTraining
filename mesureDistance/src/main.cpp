#include <Arduino.h>
#include <Wire.h>

#define BNO055_ADDR      (0x28)
#define BNO055_CHIP_ID          0x00
#define BNO055_CHIP_ID_VALUE    0xa0
#define BNO055_AXIS_MAP_CONFIG  0x41
#define BNO055_OPR_MODE         0x3d
#define CONFIGMODE              0x00
#define MODE_NDOF               0x0c
#define ACCEL_OFFSET_X_LSB      0x55
#define ACCEL_OFFSET_X_MSB      0x56
#define ACCEL_OFFSET_Y_LSB      0x57
#define ACCEL_OFFSET_Y_MSB      0x58
#define ACCEL_OFFSET_Z_LSB      0x59
#define ACCEL_OFFSET_Z_MSB      0x5a
#define MAG_OFFSET_X_LSB        0x5b
#define MAG_OFFSET_X_MSB        0x5c
#define MAG_OFFSET_Y_LSB        0x5d
#define MAG_OFFSET_Y_MSB        0x5e
#define MAG_OFFSET_Z_LSB        0x5f
#define MAG_OFFSET_Z_MSB        0x60
#define GYRO_OFFSET_X_LSB       0x61
#define GYRO_OFFSET_X_MSB       0x62
#define GYRO_OFFSET_Y_LSB       0x63
#define GYRO_OFFSET_Y_MSB       0x64
#define GYRO_OFFSET_Z_LSB       0x65
#define GYRO_OFFSET_Z_MSB       0x66
#define ACCEL_RADIUS_LSB        0x67
#define ACCEL_RADIUS_MSB        0x68
#define MAG_RADIUS_LSB          0x69
#define MAG_RADIUS_MSB          0x6a
#define BNO055_EULER_H_LSB      0x1a
#define BNO055_EULER_H_MSB      0x1b
#define BNO055_EULER_R_LSB      0x1c
#define BNO055_EULER_R_MSB      0x1d
#define BNO055_EULER_P_LSB      0x1e
#define BNO055_EULER_P_MSB      0x1f

static uint8_t sensorReadArray[18] = {0};
static uint8_t sensorWriteArray[18] = {0};

void setup(){
  Wire.begin();
  Serial.begin(9600);

  while(Serial.read() != 13)
    ;
  
  Serial.println("Program has Started!!");

  Wire.beginTransmission(BNO055_ADDR);
  if(Wire.endTransmission() == 0)
    Serial.println("Pass : 1");
  else
    Serial.println("Error : 1");

  delay(750);

  sensorWriteArray[0] = BNO055_CHIP_ID;

  Wire.beginTransmission(BNO055_ADDR);
  Wire.write(sensorReadValue[0], 1);
  Wire.endTransmission();
  Wire.requestFrom(BNO055_ADDR, 1);
  
  if(Wire.available()){
    sensorReadValue[0] = Wire.read();
    Serial.print("Read 0x00 : ");
    Serial.println(sensorReadValue[0], HEX);
  }else{
    Serial.println("Error : 2");
  }

  Wire.beginTransmission(BNO055_OPR_MODE);
  Wire.write(0x07);
  Wire.endTransmission();
}

void loop(){
  sensorReadValue[0] = 0x08;
  Wire.beginTransmission(BNO055_ADDR);
  Wire.write(sensorReadValue[0]);
  Wire.endTransmission();
  Wire.requestFrom(BNO055_ADDR, 1);

  if(Wire.available()){
    Serial.print("Read Accl X : ");

    sensorReadValue[0] = Wire.read();

    Serial.println((sensorReadValue[0]), DEC);
  }
  
  delay(1000);
}