// using HC SR-04 to get the measurement
// should be able to create distance as of now

const int ECHOpin = 19;
const int TRIGpin = 5;

long int duration;  // stores the time, ECHOpin was HIGH
float distance;   // stores the distance 

void setup() {
  pinMode(ECHOpin, INPUT);
  pinMode(TRIGpin, OUTPUT);

  Serial.begin(115200);
  Serial.println("Starting the Serial Monitor");
}

void loop() {
  digitalWrite(TRIGpin, LOW);
  delayMicroseconds(4);
  digitalWrite(TRIGpin, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIGpin, LOW);

  // pulseIn will be calulating the time for which ECHOpin will be HIGH
  duration = pulseIn(ECHOpin, HIGH); 
  Serial.println(duration);
  // distance = speed * time and divided by 2 to get one way distance
  distance = duration * 0.034 / 2;

  Serial.print("The measured distance is -- " );
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000);
}
