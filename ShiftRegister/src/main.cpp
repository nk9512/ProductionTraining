#include <Arduino.h>

#define PIN_DATA 5
#define PIN_LATCH 4
#define PIN_CLK 3

const uint8_t rclkPin  = 11;   // (11) ST_CP [RCLK] on 74HC595
const uint8_t srclkPin =  9;  // (9)  SH_CP [SRCLK] on 74HC595
const uint8_t dsPin = 12;     // (12) DS [SER] on 74HC595
const uint8_t tDelay = 10;   //200ms遅延設定

//Lesson 20-1 8bitシフトレジスタを使ってLEDを順番に点灯２
//https://omoroya.com/

int Position[2] = {0};  //Position...センサーの位置の要素数2の配列
uint8_t leds[8] = {B00000000}; //ledsをuint8_t型配列としてb00000000で定義

void shiftSetup(){
  DDRB = (1 << PIN_DATA) | (1 << PIN_LATCH) | (1 << PIN_CLK);
}

void shiftWrite(uint8_t sendData){
  PORTB &= ~((1 << PIN_DATA) | (1 << PIN_LATCH) | (1 << PIN_CLK));
  
  for(int i = 0; i < 8; i++){
    PORTB &= ~(1 << PIN_DATA);
    PORTB |= ((!!(sendData & (1 << i))) << PIN_DATA);

    PORTB |= (1 << PIN_CLK);
    PORTB &= ~(1 << PIN_CLK);
  }

  PORTB |= (1 << PIN_LATCH);
  PORTB &= ~(1 << PIN_DATA);
}

void BitTranslate(int Position[],uint8_t bitData[])   //2要素配列の位置データをビット単位に変換
{
  bitData[Position[0]] |= (1 << Position[1]);
}

void ToShiftRegister(uint8_t bitData[]) //シフトレジスターにLED点灯位置のデータを送信
{
  for (int i = 0; i < 8; i++)
  {
    shiftWrite(bitData[i]);
  }
}

void setup() 
{
  DDRB = 0b00011010;  //rclkPin,srclkPin,dsPinをOUTPUTに設定
}

void loop() 
{
  BitTranslate(Position,leds);
  PORTB &= 0b11110111;               //送信中のRCLKをLowにする
  ToShiftRegister(leds);
  PORTB |= 0b00001000;              //送信終了後RCLKをHighにする
  
  delay(tDelay);
}