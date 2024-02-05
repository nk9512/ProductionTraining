#include <Arduino.h>
#define rclkPin 11   // (11) ST_CP [RCLK] on 74HC595
#define srclkPin 9  // (9)  SH_CP [SRCLK] on 74HC595
#define dsPin 12     // (12) DS [SER] on 74HC595
#define tDelay 200   //200ms遅延設定

//Lesson 20-1 8bitシフトレジスタを使ってLEDを順番に点灯２
//https://omoroya.com/


byte leds = B00000000; //ledsをbyte型としてb00000000で定義

void setup() 
{
  pinMode(rclkPin, OUTPUT);   //11番ピンをOUTPUTとして定義
  pinMode(dsPin, OUTPUT);     //12番ピンをOUTPUTとして定義
  pinMode(srclkPin, OUTPUT);  //9番ピンをOUTPUTとして定義
}

void loop() 
{
  //　LED1からLED8までのレジスタを初期化。
  leds = B11111111;                          //初期化設定、b11111111（全て消灯）
  digitalWrite(rclkPin, LOW);                //送信中のRCLKをLowにする
  shiftOut(dsPin, srclkPin, LSBFIRST, leds); //全てのLEDを消灯
  digitalWrite(rclkPin, HIGH);               //送信終了後RCLKをHighにする
  
  delay(tDelay);
  
  //　LED1からLED8までを順に光らせる。
  for (int i = 0; i < 8; i++)
  {
    bitClear(leds, i);                           //bitbyte操作関数で指定したビットを0にする
    
    digitalWrite(rclkPin, LOW);                //送信中のRCLKをLowにする
    shiftOut(dsPin, srclkPin, LSBFIRST, leds); //シフト演算を使って点灯するLEDを選択
    digitalWrite(rclkPin, HIGH);               //送信終了後RCLKをHighにする
    
    delay(tDelay);
  }
}
//うんち