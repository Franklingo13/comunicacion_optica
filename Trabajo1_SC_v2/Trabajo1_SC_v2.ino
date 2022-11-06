#define LASERPIN 8
int sensorPin = A1;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

int periodo=45;      //en milisegundos
unsigned long MuestreoActual=0;
unsigned long tiempo=0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LASERPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  if(millis() > MuestreoActual+periodo){
    MuestreoActual = millis();
    //Serial.println(MuestreoActual);
    //tiempo = micros();
     //Serial.println(tiempo);

    // read the value from the sensor:

    //condicional para transmitir por 20 periodos

    if(millis()<18000){
      sensorValue = analogRead(sensorPin);
    int bits[]={1, bitRead(sensorValue,9), bitRead(sensorValue,8), bitRead(sensorValue,7), bitRead(sensorValue,6), bitRead(sensorValue,5), bitRead(sensorValue,4), bitRead(sensorValue,3), bitRead(sensorValue,2), bitRead(sensorValue,1), bitRead(sensorValue,0)};
    //int bits[]={1,1,0,1,0,1,0,1,0,1,0};
    
    //float voltage= sensorValue* (5/1023.0);
       
      Serial.println(sensorValue); //muestra el valor de la senal muestreada
      //Serial.println(voltage); //muestra el valor de la senal real
      //start_bit();
       //tiempo = micros();
       //Serial.println(tiempo);
      
      for (int i=0; i<11; i++){
        digitalWrite(LASERPIN, bits[i]);
        //delay(90);
        delayMicroseconds(800); //se cambió a 700 para darle más tiempo a la escritura 
      }
      digitalWrite(LASERPIN, LOW); 
      tiempo = micros();
    //Serial.println(tiempo);
    //Serial.println("");
      //limpiar el  vector para un nuevo valor
      for (int i=0; i<11; i++){
        bits[i] = 0;
      }
    }
    

    
  }//fin if
  //delay(1);
  
delayMicroseconds(1);

}//fin loop
