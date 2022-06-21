#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <DallasTemperature.h>


//---- define section---
#define ledAr LED_BUILTIN 
#define ONE_WIRE_BUS 4
LiquidCrystal_I2C lcd(0x27,16,2);       // set the LCD address to 0x27 for a 16 chars and 2 line display
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void setup()
{
  lcd.begin();
  //lcd.begin(D2, D1);
  //Wire.begin(0, 1);
  // Print a message to the LCD.
  lcd.backlight();
  Wire.begin(D2, D1);
  Serial.begin(115200);
  lcd.setCursor(1,0);
  lcd.print("SENIOR PROJECT");
  lcd.setCursor(3,1);
  lcd.print("konichiwaa");
  
  lcd.clear();
  
  
  sensors.begin();
}

void loop() 
{

  
  // ---- Code display temp on Serial ----
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(temperatureC);

  
  // ---- Code display temp on LCD ----
  /*
  sensors.requestTemperatures();
  float x = sensors.getTempCByIndex(0);
  lcd.setCursor(0,0);
  lcd.print("Temperature: "); 
  lcd.setCursor(0,1);
  lcd.print("          ");
  lcd.setCursor(0,1); 
  lcd.print(x);   
  */
  
  
  /*
  // put your main code here, to run repeatedly:
  digitalWrite(ledAr, HIGH);
  delay(10000);
  digitalWrite(ledAr, LOW);
  delay(10000);
  */
}
