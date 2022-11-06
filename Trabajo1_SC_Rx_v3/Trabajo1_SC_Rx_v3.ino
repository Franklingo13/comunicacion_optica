#define RXPIN 3
#define UMBRAL 10

//int ambientelectura = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RXPIN, INPUT);
  Serial.begin(9600);
  //ambientelectura = analogRead(RXPIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lectura = digitalRead(RXPIN);
  int bits[10];
  
  int val=0;
  
  // Escuchando el bit de inicio
  //LOW xq cuando llega luz laser muestra cero 
   if(lectura == LOW ){
    for(int i =0; i<10; i++){
      
      if(digitalRead(RXPIN)== LOW){
        bits[i]=1;
      }
      else{
        bits[i]=0;
      }
      //delay(10);
      delayMicroseconds(85);
    }
    
    for(int i=0; i<10; i++){
      Serial.print( bits[i]);
      val = val * 2 + ( bits[i]);
      //Serial.println("");
    } 
    Serial.println("");
    Serial.println(val);
    
    for(int i=0; i<10; i++){
      bits[i]=0;
    } 
  }
  
 //delay(1);
} 
