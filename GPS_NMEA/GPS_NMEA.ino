#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(4, 3); // RX, TX (TX not used)
const int sentenceSize = 80;

char sentence[sentenceSize];

void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop()
{
  static int i = 0;
  if (gpsSerial.available())
  {
    char ch = gpsSerial.read();
    if (ch != '\n' && i < sentenceSize)
    {
      sentence[i] = ch;
      i++;
    }
    else
    {
     sentence[i] = '\0';
     i = 0;
     //displayGPS();
     Serial.println(sentence);
    }
  }
  
}

void displayGPS()
{
 
  char field[20];
  getField(field, 0);
  if (strcmp(field, "$GPGGA") == 0)
  {
    Serial.print("Lat: ");
    getField(field, 2);  // number
    Serial.print(field);
    getField(field, 3); // N/S
    Serial.print(field);
    
    Serial.print(" Long: ");
    getField(field, 4);  // number
    Serial.print(field);
    getField(field, 5);  // E/W
    Serial.print(field);
    
    Serial.print(" Altitud: ");
    getField(field, 9);  // number
    Serial.println(field);
    
  }
}

void getField(char* buffer, int index)
{
  int sentencePos = 0;
  int fieldPos = 0;
  int commaCount = 0;
  while (sentencePos < sentenceSize)
  {
    if (sentence[sentencePos] == ',')
    {
      commaCount ++;
      sentencePos ++;
    }
    if (commaCount == index)
    {
      buffer[fieldPos] = sentence[sentencePos];
      fieldPos ++;
    }
    sentencePos ++;
  }
  buffer[fieldPos] = '\0';
} 
