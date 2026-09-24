#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

RF24 radio (9, 10); // CNS pin, CE pin

const byte address [][6] = {"meow2"}; //byte address for radio

void setup() {
  Serial.begin(115200);
  delay(50);
  if(radio.begin())
    Serial.println("radio.begin succeeded!");
  else
    Serial.println("Not able to contact radio module");
  radio.openReadingPipe(0, address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  char text[32] = "";
  if (radio.available()){ //checks if there is a signal from the sensors
    radio.read(&text, sizeof(text)); //Transmits message
    Serial.println(text);
  }
  else{
    Serial.print(".");
    delay(100);
  }
}