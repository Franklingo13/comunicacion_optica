#define __DEBUG__

#include <Wire.h>             //wire library
//#include <Adafruit_MCP4725.h> // MCP4725 library from adafrui
#include <SD.h> //libreria SD
#define RXPIN 7
//Adafruit_MCP4725 MCP4725; 
File myFile;
int UltimaPocicion=0;
float Nbits=0;
float Acu=0;
float BER=0;

unsigned long MuestreoActual=0;
unsigned long tiempo=0; 
int bits[10];
int charbits[10];

float graficaVoltaje = 0;


#include <Arduino.h>
#include <OLED_SSD1306_Chart.h>
#include <Adafruit_I2CDevice.h> //Include this to avoid compile errors in Platformio

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define BAUDRATE 9600

#define SDA_PIN D1
#define SCL_PIN D2

OLED_SSD1306_Chart display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char actualThickness;

void setup() {
  // put your setup code here, to run once:
 
  pinMode(RXPIN, INPUT);
  
  Serial.begin(9600);
  
//  MCP4725.begin(0x60); // Default I2C Address of MCP4725 breakout board (sparkfun)   If not try 0x61 or 0x62
  Serial.println("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");

  #if defined ESP8266
  Wire.begin(SDA_PIN, SCL_PIN);
#else
  Wire.begin();
#endif

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setChartCoordinates(0, 60);      //Chart lower left coordinates (X, Y)
  display.setChartWidthAndHeight(123, 55); //Chart width = 123 and height = 60
  display.setXIncrement(5);                //Distance between Y points will be 5px
  display.setYLimits(0, 100);             //Ymin = 0 and Ymax = 100
  display.setYLimitLabels("0", "5");    //Setting Y axis labels
  display.setYLabelsVisible(true);
  display.setAxisDivisionsInc(12, 6);    //Each 12 px a division will be painted in X axis and each 6px in Y axis
  display.setPlotMode(SINGLE_PLOT_MODE); //Set single plot mode
  // display.setPointGeometry(POINT_GEOMETRY_CIRCLE);
  actualThickness = LIGHT_LINE;
  display.setLineThickness(actualThickness);
  display.drawChart(); //Update the buffer to draw the cartesian chart
  display.display();
  
}

void loop() {

  int val=0;
 
   if(digitalRead(RXPIN) == 0 ){
    delayMicroseconds(801);
  
    for(int i =0; i<10; i++){
      if(digitalRead(RXPIN)== 0){
        bits[i]=1;
        charbits[i]=49;
      }
      else{
        bits[i]=0;
        charbits[i]=48;
      }
      delayMicroseconds(801);
    }

     myFile = SD.open("out5.txt");//abrimos  el archivo
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
      
      for(int i=0;i<10;i++)
      {     
        Nbits ++;
        val = val * 2 + ( bits[i]);
        if(cadena[i*2]!= charbits[i])
        {
           Acu ++;
        } 
      }
      BER=Acu/Nbits;
          //#bits recibidos total
        //Serial.println(Nbits);
          //#bits errones
        //Serial.println(Acu);
          //BER
        //Serial.println(BER, 6);   
        Serial.println(val);   



  //auto value = random(50) + 50;
  graficaVoltaje=map(val,0,1023,53,0);
  //Serial.println(val);
  if (!display.updateChart(4*val)) //Value between Ymin and Ymax will be added to chart
  {
    //Serial.println(graficaVoltaje);
    display.clearDisplay(); //If chart is full, it is drawn again
    if (actualThickness == NORMAL_LINE)
    {
      actualThickness = LIGHT_LINE;
    }
    else if (actualThickness == LIGHT_LINE)
    {
      actualThickness = NORMAL_LINE;
    }
    display.setLineThickness(actualThickness);
    display.drawChart();
  }
  delay(10);


      
  } else {  
    Serial.println("Error al abrir el archivo");
  }
 
 Serial.println("");  
} 

}
