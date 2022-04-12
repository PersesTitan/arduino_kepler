#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <SparkFunBME280.h>
#define BME280_ADDR 0x77
#define TOUCH_L 27
#define TOUCH_R 4
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731{};
BME280 myBME280;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myBME280.setI2CAddress(BME280_ADDR);
  myBME280.beginI2C();
  matrix.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(int8_t i = 0; i>=-64; i--) {
    matrix.clear();
    matrix.setCursor(i,1);
    matrix.print(myBME280.readTempC(),1);
    matrix.print("C");
    matrix.print(" ");
    matrix.print(myBME280.readFloatHumidity(),0);
    matrix.print("%");
    delay(50);
  }
  matrix.clear();
  delay(2000);
}
