#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SparkFunBME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

//터치 센서 핀
#define Left 27
#define Right 4

//온습도 센서
BME280 my;
LiquidCrystal_I2C lcd(0x20,16,2);

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();

//터치 감지용
int touch = 1;

void setup() {
  
  matrix.begin();
  Serial.begin(115200);
 //센서 세팅
  my.setI2CAddress(0x77);
  my.beginI2C();
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
  matrix.setTextSize(1);
  matrix.setTextColor(100);

  
  //온도 가져오기
  //lcd세팅
  lcd.setCursor(0,0);

  //디버깅용
  Serial.println(touchRead(Left));
  Serial.println(touchRead(Right));
  if(touchRead(Left)<15 || touchRead(Right) < 25) {
    //누르면 lcd 초기화
    lcd.clear();
    
    //왼쪽인지 오른쪽인지 저장
    if (touchRead(Left)<15) touch = 1;
    if (touchRead(Right)<25) touch = 0;
    while(touchRead(Left)<15 || touchRead(Right) < 25) {
      //누르는 동안 멈추기
      delay(100);
    }
    
  }

  if (touch == 1){
    matrix.clear();
    lcd.print("Temp: ");
    lcd.print(my.readTempC(), 1);
    lcd.print("C");
  } else {
    for(int8_t x = 0; x>=-64; x--) {
      //출력 도중나올때
      if(touchRead(Left)<15 || touchRead(Right) < 25) {
        //왼쪽인지 오른쪽인지 저장
        if (touchRead(Left)<15) touch = 1;
        if (touchRead(Right)<25) touch = 0;
      }
      matrix.clear();
      matrix.setCursor(x,1);
      matrix.print("Humi:");
      matrix.print(my.readFloatHumidity(),0);
      matrix.print("%");
      delay(50);
    }
  }

  delay(500);
}
