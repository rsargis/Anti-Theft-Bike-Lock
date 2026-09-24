#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio (9, 10); // CNS pin, CE pin

const byte address [][6] = {"meow2"}; //byte address for radio
const int buzzer = 2;
const int RED_LED = 4;
const int BLUE_LED = 6;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(buzzer, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

unsigned long int sum = 0;
bool status = false;

void loop() {
  static char text[] = "Bike Lock Alert!";

  sum += analogRead(A0) + analogRead(A1) + analogRead(A2) + analogRead(A3);
  Serial.println(sum);
  if(sum > 80000){
      status = true;
      sum = 0;
  }
  else{
    status = false;
  }
  if(millis() % 4000 > 3995){
    sum = 0;
    status = false;
  }

  if (status){
    for (int i = 0; i < 5; i++){
      radio.write(&text, sizeof(text)); //Transmits message
      tone(buzzer, 1000);
      digitalWrite(RED_LED, HIGH);
      delay(500);
      digitalWrite(RED_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      delay(500);
      digitalWrite(BLUE_LED, LOW);
      Serial.println("Alarm");
    }
  }
  else{
    noTone(buzzer);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
}

