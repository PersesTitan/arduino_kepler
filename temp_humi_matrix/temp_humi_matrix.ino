#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
LiquidCrystal_I2C lcd(0x20,16,2);

static const uint8_t smile[] =
{ B00000000, B01000010, B10100101, B00000000, B01000010, B00111100, B00000000, B00000000 };
static const uint8_t sade[] =
{ B00000000, B10000001, B01000010, B00100100, B00000000, B00000000, B00111100, B01000010 };
static const uint8_t angle[] =
{ B00000000, B00000000, B11100111, B00000000, B00000000, B00000000, B01111110, B00000000 };

//버튼 카운트
int count = 0;

void setup() {
  matrix.begin();
  Serial.begin(115200);
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
  int light = analogRead(36);

  //디버깅용
  Serial.print("밝기: ");
  Serial.println(light);
  lcd.setCursor(0,0);
  if (light>1200) {
    lcd.clear();
    lcd.print("good morning");
  } else {
    lcd.clear();
    lcd.print("Not yet");
  }
 
  count = count%3;
  if(digitalRead(15)==1){
    count++;
    delay(100);
  }

  matrix.setRotation(0);
  matrix.clear();
  if (count == 0) matrix.drawBitmap(0,0,smile, 8,8,128);
  if (count == 1) matrix.drawBitmap(0,0,sade, 8,8,128);
  if (count == 2) matrix.drawBitmap(0,0,angle, 8,8,128);
  //마지막은 꺼두기

  delay(1000);
}
