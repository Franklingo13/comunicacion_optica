
#include <SD.h>
#define LASERPIN 8
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

int periodo=1;      //en milisegundos
unsigned long MuestreoActual=0;

File myFile;
void setup() 
{
  // declare the ledPin as an OUTPUT:
  pinMode(LASERPIN, OUTPUT);
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  int bits[]={bitRead(sensorValue,0), bitRead(sensorValue,1), bitRead(sensorValue,2), bitRead(sensorValue,3), bitRead(sensorValue,4), bitRead(sensorValue,5), bitRead(sensorValue,6), bitRead(sensorValue,7), bitRead(sensorValue,8), bitRead(sensorValue,9)};
  //float voltage= sensorValue* (5/1023);
  myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo
  
if(millis() > MuestreoActual+periodo){
  
    MuestreoActual = millis();

    if (myFile) { 
        Serial.print("Escribiendo SD: ");
        
          // lee los valores
        myFile.print(sensorValue)
        myFile.close(); //cerramos el archivo
  } else {
    Serial.println("Error al abrir el archivo");
  }
     
    //Serial.println(sensorValue); //muestra el valor de la senal muestreada
    //Serial.println(voltage); //muestra el valor de la senal real
    start_bit();
   
    for (int i=0; i<10; i++){
      digitalWrite(LASERPIN, bits[i]);
      //delay(10);
      delayMicroseconds(85);
    }
    digitalWrite(LASERPIN, LOW); 
  
    //limpiar el  vector para un nuevo valor
    for (int i=0; i<10; i++){
      bits[i] = 0;
    }  
  }//fin if
  

//delay(10);
}//fin loop


void start_bit() { //THE START BIT
  digitalWrite(LASERPIN, HIGH);
  delay(10);
  digitalWrite(LASERPIN, LOW);
}
