#include <Arduino.h>

const uint8_t rclkPin  = 11;   // (11) ST_CP [RCLK] on 74HC595
const uint8_t srclkPin =  9;  // (9)  SH_CP [SRCLK] on 74HC595
const uint8_t dsPin = 12;     // (12) DS [SER] on 74HC595
const uint8_t tDelay = 10;   //200ms遅延設定

//Lesson 20-1 8bitシフトレジスタを使ってLEDを順番に点灯２
//https://omoroya.com/

int Position[2] = {0};  //Position...センサーの位置の要素数2の配列
uint8_t leds[8] = {B00000000}; //ledsをuint8_t型配列としてb00000000で定義

void BitTranslate(int Position[],uint8_t bitData[])   //2要素配列の位置データをビット単位に変換
{
  uint8_t ForShift = B00000001;
  bitData[Position[0]] |= (ForShift << Position[1]);
}

void ToShiftRegister(uint8_t bitData[]) //シフトレジスターにLED点灯位置のデータを送信
{
  for (int i = 0; i < 8; i++)
  {
      shiftOut(dsPin, srclkPin, LSBFIRST, bitData[i]);  //ShiftOut...Byte単位でデータをシリアル的に送信する。
  }
}

void setup() 
{
  pinMode(rclkPin, OUTPUT);   //11番ピンをOUTPUTとして定義
  pinMode(dsPin, OUTPUT);     //12番ピンをOUTPUTとして定義
  pinMode(srclkPin, OUTPUT);  //9番ピンをOUTPUTとして定義
}

void loop() 
{
  BitTranslate(Position,leds);
  digitalWrite(rclkPin, LOW);                //送信中のRCLKをLowにする
  ToShiftRegister(leds);
  digitalWrite(rclkPin, HIGH);               //送信終了後RCLKをHighにする
  
  delay(tDelay);
}