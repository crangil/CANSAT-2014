/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial mySerial(9, 10); // RX, TX   puerto serie para la transmisión por radio

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Goodnight moon!");
  dht.begin();
  mySerial.begin(57600);
  mySerial.println("Hello, world?");
  pinMode(13, OUTPUT);
}

void loop() // run over and over
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  mySerial.print("Humedad: ");
  mySerial.print(h);
  mySerial.print("    Temperatura: ");
  mySerial.println(t);
  
  
  char c;
  if (mySerial.available()){
       c = mySerial.read();
  }
  if (c=='h')
  {
    digitalWrite(13,HIGH);
    mySerial.println("encendido");
  }
  else if(c=='l')
  {
    digitalWrite(13,LOW);
    mySerial.println("apagado");
  }
  
 delay(10);
}

