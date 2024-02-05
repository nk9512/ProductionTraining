#include "BNO055_Controller.hpp"

#define MODULE_ADDRESS 0x28

BNO055 sensor(MODULE_ADDRESS);  //クラスを宣言
BNO055::measurementData data;   //測定データを格納するための

void setup(){
  Serial.begin(9600);

  sensor.begin(); //センサとの通信を開始
  sensor.measuringStart();  //測定開始
}

void loop(){
  sensor.read(&data, true, true, true); //測定データを更新

  //各軸の加速度を測定 単位:m/(s^2)
  Serial.print("Accl X : ");
  Serial.print(data.accl.x);
  Serial.print("Accl Y : ");
  Serial.print(data.accl.y);
  Serial.print("Accl Z : ");
  Serial.print(data.accl.z);

  //各軸の角速度を測定 単位:deg/s
  Serial.print("Gyro X : ");
  Serial.print(data.gyro.x);
  Serial.print("Gyro Y : ");
  Serial.print(data.gyro.y);
  Serial.print("Gyro Z : ");
  Serial.print(data.gyro.z);

  //各軸の地磁気を測定 単位:μT
  Serial.print("Mag X : ");
  Serial.print(data.mag.x);
  Serial.print("Mag Y : ");
  Serial.print(data.mag.y);
  Serial.print("Mag Z : ");
  Serial.println(data.mag.z);

  delay(50);
}