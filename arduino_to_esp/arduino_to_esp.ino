#include<SoftwareSerial.h>
#include<LiquidCrystal_I2C.h>

SoftwareSerial mySerial(10, 11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available())
  {
    String data = mySerial.readStringUntil('\n');
    data.remove(data.length()-1);
    Serial.println(data);
    lcd.setCursor(0, 0);
    lcd.print(data);
    lcd.setCursor(data.length(), 0);
    lcd.print("                  ");
  }
}
