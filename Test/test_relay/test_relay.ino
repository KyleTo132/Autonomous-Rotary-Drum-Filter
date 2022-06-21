 #include <Wire.h>

int relay = 5;                   // the input to the relay pin
int floatSensor = 2;             // the input to the float switch
int valSw = 0;  

void setup() 
{
  Serial.begin(115200);
  pinMode(relay, OUTPUT);        // initialize pin GPIO5 (D1) as OUTPUT
  pinMode(floatSensor, INPUT);   // initialize pin GPIO4 (D2) as INPUT
  digitalWrite(relay, LOW);
}
void loop() 
{
  valSw = digitalRead(floatSensor);
  Serial.println(valSw);

  if(valSw == 1)
  {
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
  }
  //digitalWrite(relayInput, HIGH); // turn relay on
  //delay(1000);
  //digitalWrite(relayInput, LOW); // turn relay off
  //delay(1000);

}
