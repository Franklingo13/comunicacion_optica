#include <SD.h>

File myFile;
int UltimaPocicion=0;
int pausa=1000;

#define LASERPIN 8

int sensorPin = A1;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

int periodo=100;      //en milisegundos
unsigned long MuestreoActual=0;
unsigned long tiempo=0;
int bits[11];

void setup() {
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
   //int bits[]={1,1,0,0,1,1,0,1,1,0,1};
  if(millis() < 28000 ){
  if(millis() > MuestreoActual+periodo){
    MuestreoActual = millis();
    //Serial.println(MuestreoActual);
    //tiempo = micros();
     //Serial.println(tiempo);

    // read the value from the sensor:
  //sensorValue = analogRead(sensorPin);
  //int bits[]={1, bitRead(sensorValue,9), bitRead(sensorValue,8), bitRead(sensorValue,7), bitRead(sensorValue,6), bitRead(sensorValue,5), bitRead(sensorValue,4), bitRead(sensorValue,3), bitRead(sensorValue,2), bitRead(sensorValue,1), bitRead(sensorValue,0)};
  //int bits[]={1,1,0,0,0,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,1,0,0,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,1,0,1,1,0,1,1,1,0,0,1,1,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,1,0,1,1,0,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1};
 
  //float voltage= sensorValue* (5/1023.0);
     
    //Serial.println(sensorValue); //muestra el valor de la senal muestreada
    //Serial.println(voltage); //muestra el valor de la senal real
    //start_bit();
     //tiempo = micros();
     //Serial.println(tiempo);

    myFile = SD.open("out7.txt");//abrimos  el archivo
  int totalBytes=myFile.size();
  String cadena="";
  
  if (myFile) {   
      if(UltimaPocicion>=totalBytes)   UltimaPocicion=0;
      myFile.seek(UltimaPocicion); 
      
      //--Leemos una línea de la hoja de texto--------------
      while (myFile.available()) {
          
        char caracter=myFile.read();
          cadena=cadena+caracter;
          UltimaPocicion=myFile.position();
          if(caracter==10)//ASCII de nueva de línea
          {            
            break;
          }
      }
      //---------------------------------------------------
      myFile.close(); //cerramos el archivo
      //Serial.print("Bits Leidos:");
      //Serial.print(cadena);
      
      //-----------procesamos la cadena------------
      int index=0;
      char c=cadena[index++];
      
      //Serial.print("   Bits |");
      for(int i=0;i<11;i++)
      {     
        if(cadena[i*2]=='1')
        {
          //digitalWrite(PinLeds[i], HIGH);
          //Serial.print(" 1 |");
           bits[i]=1;
        }
        else
        {
           bits[i]=0;
          //digitalWrite(PinLeds[i], LOW);
          //Serial.print(" 0 |");
        } 
      }
      Serial.println();
      //Serial.println();    
  
  } else {  
    Serial.println("Error al abrir el archivo");
  }
tiempo = micros();
  //Serial.println(tiempo);
    
    for (int i=0; i<11; i++){
      //Serial.print(bits[i]);
      digitalWrite(LASERPIN, bits[i]);
      
      //delay(90);
      delayMicroseconds(800);
    }
    Serial.println(" ");
    digitalWrite(LASERPIN, LOW); 
    tiempo = micros();
  //Serial.println(tiempo);
  //Serial.println("");
    //limpiar el  vector para un nuevo valor
    //for (int i=0; i<11; i++){
    //  bits[i] = 0;
    //}  

    
  }//fin if
  //delay(1);
  
//delayMicroseconds(1);
  }
}//fin loop
