
#define LASERPIN 8
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LASERPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  int bits[]={bitRead(sensorValue,0), bitRead(sensorValue,1), bitRead(sensorValue,2), bitRead(sensorValue,3), bitRead(sensorValue,4), bitRead(sensorValue,5), bitRead(sensorValue,6), bitRead(sensorValue,7), bitRead(sensorValue,8), bitRead(sensorValue,9)};
   //int bits[]={bitRead(sensorValue,9), bitRead(sensorValue,8), bitRead(sensorValue,7), bitRead(sensorValue,6), bitRead(sensorValue,5), bitRead(sensorValue,4), bitRead(sensorValue,3), bitRead(sensorValue,2), bitRead(sensorValue,1), bitRead(sensorValue,0)};

  Serial.println(sensorValue);
  
  // start bit
//  digitalWrite(LASERPIN, HIGH);
//  delay(10);
//  digitalWrite(LASERPIN, LOW);
  
  for (int i=0; i<10; i++){
    digitalWrite(LASERPIN, bits[i]*255);
    delayMicroseconds(850);
  }

  //digitalWrite(LASERPIN, LOW); 

  delay(10);
}
