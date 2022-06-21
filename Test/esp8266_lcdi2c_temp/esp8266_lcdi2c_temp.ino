/* library declaration */
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* function declaration */
void loading();
void na_display(int pos);
void temp_display(int pos);
int relay_on();
int relay_off();
void relay_check(int relayState);

/* global variable */
int relayInput = 2;
int relayState ;

void setup()
{
  /* initialize the LCD */
  Wire.begin(D2, D1);
  Serial.begin(9600);
  sensors.begin();
  lcd.begin();

  /* Turn on the blacklight and print a message. */ 
  loading();
  pinMode(relayInput, OUTPUT); 

}

void loop()
{
  //na_display(0);
  na_display(4);
  na_display(8);
  temp_display(12);
  
  relay_on();
  delay(1000);
  relay_check(relayState);
  relay_off();
  delay(1000);
  relay_check(relayState);
}

/* function print loading screen for fun :v */
void loading()
{
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting Prj ");
  for (int i = 0; i < 15; i++)
  {
    lcd.setCursor(i, 1);
    lcd.print("-");
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
}

void na_display(int pos)
{
  lcd.setCursor(pos, 0);
  lcd.print("N/A ");
  lcd.setCursor(pos, 1);
  lcd.print("--- ");
}
void temp_display(int pos)
{
  lcd.setCursor(pos, 0);
  lcd.print("Temp");
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  lcd.setCursor(pos, 1);
  lcd.print(temp);
}
int relay_on()
{
  digitalWrite(relayInput, HIGH);
  return relayState = 1;
}

int relay_off()
{
  digitalWrite(relayInput, LOW);
  return relayState = 0;
}
void relay_check(int relayState)
{
  lcd.setCursor(0, 0);
  lcd.print("Drum");
  if( relayState == 1 )
  {
    lcd.setCursor(0, 1);
    lcd.print("ON  ");
  } 
  else if ( relayState == 0 )
  {
    lcd.setCursor(0, 1);
    lcd.print("OFF ");
  }
}
