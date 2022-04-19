#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SparkFunBME280.h>

//LED pin
#define R 12
#define G 13
#define B 14

//부저 핀
#define freq 2000
#define channel 0
#define resolution 8

//온습도 센서
BME280 my;
LiquidCrystal_I2C lcd(0x20,16,2);

void setup() {
  //센서 세팅
  my.setI2CAddress(0x77);
  my.beginI2C();
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(115200);

  //부저
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(25, channel);
  pinMode(2, OUTPUT);
}

void loop() {
  //온도 가져오기
  Serial.println(my.readTempC());

  //lcd세팅
  lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(my.readTempC(), 2);

  if(29.7<=my.readTempC() && my.readTempC()<=30) {
    //28~29도 일때 초록색
    digitalWrite(G, HIGH);
    digitalWrite(R, LOW);
    digitalWrite(B, LOW);
    delay(1000);
  } else if (30<my.readTempC() && my.readTempC()<=31) {
    //30~31도 일때 빨간색 및 부저
    digitalWrite(G, LOW);
    digitalWrite(R, HIGH);
    digitalWrite(B, LOW);
    //부저 활성화
    digitalWrite(2,HIGH);
    ledcWriteTone(channel, 262);
    delay(500);
    ledcWriteTone(channel, 252);
    delay(500);
  } else if (29.7> my.readTempC()) {
    //27도이하 일때 파란색
    digitalWrite(G, LOW);
    digitalWrite(R, LOW);
    digitalWrite(B, HIGH);
    delay(1000);
  } else {
    //모두다 아닐때는 led 소등
    digitalWrite(G, LOW);
    digitalWrite(R, LOW);
    digitalWrite(B, LOW);
    delay(1000);
  }
  //부저 비활성화
  digitalWrite(2,LOW);
}
