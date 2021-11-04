// using HC SR-04 to get the measurement
// should be able to create distance as of now

#include <WiFi.h>
#include "secret.h"
#include "ThingSpeak.h"

const int ECHOpin = 19;
const int TRIGpin = 5;

long int duration;  // stores the time, ECHOpin was HIGH
float distance;   // stores the distance 

WiFiClient client;
void setup() {
  pinMode(ECHOpin, INPUT);
  pinMode(TRIGpin, OUTPUT);

  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  
  Serial.println("Connecting to ");
  Serial.println(USERNAME);

  WiFi.begin(USERNAME, PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  digitalWrite(TRIGpin, LOW);
  delayMicroseconds(4);
  digitalWrite(TRIGpin, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIGpin, LOW);

  // pulseIn will be calulating the time for which ECHOpin will be HIGH
  duration = pulseIn(ECHOpin, HIGH); 
  // Serial.println(float(duration)/60000000); // converting to minutes
  // distance = speed * time and divided by 2 to get one way distance
  distance = duration * 0.034 / 2;

  Serial.print("The measured distance is -- " );
  Serial.print(distance);
  Serial.println(" cm");

  // setting fields in ThingSpeak
  ThingSpeak.setField(1, distance);
  ThingSpeak.setField(2, float(duration)/60000000); // converting to minutes

  // Writting the values to ThinSpeak using the channel ID and API key
  ThingSpeak.writeFields(CH_ID, API_KEY);
  
  delay(1000);
}
