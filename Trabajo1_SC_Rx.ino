#define RXPIN A0
#define UMBRAL 10

int ambientelectura = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(RXPIN, INPUT);
  Serial.begin(9600);

  ambientelectura = analogRead(RXPIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lectura = analogRead(RXPIN);
  int bits[10];

  // Escuchando el bit de inicio
  if(lectura > ambientelectura + UMBRAL ){
    for(int i =0; i<10; i++){
      if(analogRead(RXPIN) > ambientelectura + UMBRAL){
        bits[i]=1;
      }
      else{
        bits[i]=0;
      }
      delay(10);
    }

    for(int i =0; i<10; i++){
      Serial.print( bits[i]);
      }
    Serial.println("");
  }
}
