
//Define os pinos dos componentes usados
#define pinoSensorLuminosidade A0
#define pinoLedGroove D7

//Define os limites de luminosidade a serem usados 
int limiteEscuro = 100;
int limiteClaro = 500;

void setup() {
  // Configura o led para saída
  pinMode(pinoLedGroove, OUTPUT);

  // Configura o sensor de luminosidade como entrada
  pinMode(pinoSensorLuminosidade, INPUT);
 
  Serial.begin(9600);
  while (! Serial);
}

void loop() {
  int valorObservado = analogRead(pinoSensorLuminosidade);
    
  Serial1.println("Hi My Name is Emad ");
  delay(1000);

    
  if(valorObservado < limiteClaro){
    if(valorObservado < limiteEscuro){
      //Não acende o LED
      digitalWrite(pinoLedGroove, LOW);
      }else{
        //Acende  o LED 
        digitalWrite(pinoLedGroove, HIGH);
        }
  }else{
    //Pisca o LED
    digitalWrite(pinoLedGroove, HIGH);
    delay(500);
    digitalWrite(pinoLedGroove, LOW);
    delay(500);  
    digitalWrite(pinoLedGroove, HIGH);
    delay(500);
    digitalWrite(pinoLedGroove, LOW);
    delay(500); 
    digitalWrite(pinoLedGroove, HIGH);
    delay(500);
    digitalWrite(pinoLedGroove, LOW);
    delay(500);         
  }
}
