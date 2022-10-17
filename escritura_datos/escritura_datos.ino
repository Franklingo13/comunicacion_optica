#include <SD.h>
#define LASERPIN 8
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

File myFile;
void setup()
{
  pinMode(LASERPIN, OUTPUT);
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
}

void loop()
{
  myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo
  
  if (myFile) { 
        Serial.print("Escribiendo SD: ");
        
          // lee los valores
        sensorValue = analogRead(sensorPin);
         //int bits[]={bitRead(sensorValue,0), bitRead(sensorValue,1), bitRead(sensorValue,2), bitRead(sensorValue,3), bitRead(sensorValue,4), bitRead(sensorValue,5), bitRead(sensorValue,6), bitRead(sensorValue,7), bitRead(sensorValue,8), bitRead(sensorValue,9)};
        int bits[]={bitRead(sensorValue,9), bitRead(sensorValue,8), bitRead(sensorValue,7), bitRead(sensorValue,6), bitRead(sensorValue,5), bitRead(sensorValue,4), bitRead(sensorValue,3), bitRead(sensorValue,2), bitRead(sensorValue,1), bitRead(sensorValue,0)};
        
        Serial.println(sensorValue);

        myFile.print(sensorValue)
        myFile.close(); //cerramos el archivo
        
                    
  
  } else {
    Serial.println("Error al abrir el archivo");
  }
    for (int i=0; i<10; i++){
    digitalWrite(LASERPIN, bits[i]);
    delay(10);
  }

  digitalWrite(LASERPIN, LOW); 
  delay(10);
}
