/////// include library section //////////////////////////////////

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <RTClib.h>


#define ONE_WIRE_BUS 14 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 RTC;

#define WIFI_SSID "Tamxinhdep2" 
#define WIFI_PASSWORD "25081989" 
     

#define FIREBASE_HOST "https://adrf-relay-control-default-rtdb.asia-southeast1.firebasedatabase.app" 
#define FIREBASE_AUTH "SDimGnccRFP2IrdTaTh6Q2nkcN8Fsam7KI3kRUg8"  
FirebaseData firebaseData;

int Relay1Pin = 14;
int Relay2Pin = 12;
int Relay3Pin = 15;

int FloatSwitchDrum = 5;
int FloatSwitchWater = 4;

/* function declaration */
void loading();
void na_display(int pos);
void temp_display(int pos);
void relay_check(int relayState1,int relayState2,int relayState3);



/* global variable */
int relayState1 ;
int relayState2 ;
int relayState3 ;

/*variable collect and send to firebase */
float temp = 0;
int fswdrum = 0;
int fswwater = 0;
String waterStatus;
String drumStatus;

void setup ()
{
  Serial.print("INITILAIZE");
  pinMode(Relay1Pin, OUTPUT);
  pinMode(Relay2Pin, OUTPUT);
  pinMode(Relay3Pin, OUTPUT);
  //pinMode(Relay4Pin, OUTPUT);
  pinMode(FloatSwitchDrum, INPUT_PULLUP);
  pinMode(FloatSwitchWater, INPUT_PULLUP);

  /* initialize the LCD */
  Wire.begin(D2, D1);
  Serial.begin(9600);
  sensors.begin();
  lcd.begin();
  RTC.begin();  // Init RTC
  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
  Serial.print('Time and date set');
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ") ;
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);  
  loading();  



   
}
void loop ()
{
   // ------ REAL TIME CLOCK --------- 
  DateTime now = RTC.now();
 
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  
  if(Firebase.getString(firebaseData, "/Relay1Status"))
  {
    String relay1status = firebaseData.stringData();
    if(relay1status.toInt() == 1){
      Serial.println("on1");
      digitalWrite(Relay1Pin, HIGH);
      relayState1 = 1;
    }
    else {
      Serial.println("off1");
      digitalWrite(Relay1Pin, LOW);
      relayState1 = 0;
    }
  }
  else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
  if(Firebase.getString(firebaseData, "/Relay2Status")){
    String relay2status = firebaseData.stringData();
    if(relay2status.toInt() == 1){
      Serial.println("on2");
      digitalWrite(Relay2Pin, HIGH);
      relayState2 = 1;
    }
    else {
      Serial.println("off2");
      digitalWrite(Relay2Pin, LOW);
      relayState2 = 0;
    }
  }
  else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 
  if(Firebase.getString(firebaseData, "/Relay3Status")){
    String relay3status = firebaseData.stringData();
    if(relay3status.toInt() == 1){
      Serial.println("on3");
      digitalWrite(Relay3Pin, HIGH);
      relayState3 = 1;
    }
    else {
      Serial.println("off3");
      digitalWrite(Relay3Pin, LOW);
      relayState3 = 0;
    }
  }
  else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  } 


  relay_check(relayState1,relayState2,relayState3);
  temp_display(12);

  // Get latest sensor readings
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  String Temp = String(temp,3);
  Firebase.setFloat(firebaseData, "/temperature", temp);
  Serial.println(Temp);

  if(digitalRead(FloatSwitchDrum) == LOW) 
  {
    fswdrum = 0;
    drumStatus = "Dirty";
    Serial.println(" Drum: dirty ");
  } 
  else 
  {
    fswdrum = 1;
    drumStatus = "OK";
    Serial.println(" Drum: OK ");
  }
  if(digitalRead(FloatSwitchWater) == LOW) 
  {
    fswwater = 0;
    waterStatus = "Stuck";
    Serial.println(" Water Intake: stuck ");
  } 
  else 
  {
    fswwater = 1;
    waterStatus = "OK";
    Serial.println(" Water Intake: OK ");
  }

  
  Firebase.setString(firebaseData, "/DrumStatus", waterLevel);
  Firebase.setString(firebaseData, "/WaterStatus", drumStatus);
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

void relay_check(int relayState1,int relayState2,int relayState3)
{
  lcd.setCursor(0, 0);
  lcd.print("Dru1");
  if( relayState1 == 1 )
  {
    lcd.setCursor(0, 1);
    lcd.print("-1ON");
  } 
  else if ( relayState1 == 0 )
  {
    lcd.setCursor(0, 1);
    lcd.print("1OFF");
  }
  lcd.setCursor(4, 0);
  lcd.print("Dru2");
  if( relayState2 == 1 )
  {
    lcd.setCursor(4, 1);
    lcd.print("-2ON");
  } 
  else if ( relayState2 == 0 )
  {
    lcd.setCursor(4, 1);
    lcd.print("2OFF");
  }
  lcd.setCursor(8, 0);
  lcd.print("Dru3");
  if( relayState3 == 1 )
  {
    lcd.setCursor(8, 1);
    lcd.print("-3ON");
  } 
  else if ( relayState3 == 0 )
  {
    lcd.setCursor(8, 1);
    lcd.print("3OFF");
  }
}
