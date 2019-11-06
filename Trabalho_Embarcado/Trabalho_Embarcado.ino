#include <ESP8266WiFi.h>
//Define os pinos dos componentes usados
#define pinoSensorLuminosidade A0
#define pinoLedGroove D7

//Define os limites de luminosidade a serem usados 
int limiteEscuro = 100;
int limiteClaro = 500;

int valorObservado;

const char* ssid = "Marcia";
const char* password = "99094129";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(100);
  
  // Configura o led para saída
  pinMode(pinoLedGroove, OUTPUT);

  // Configura o sensor de luminosidade como entrada
  pinMode(pinoSensorLuminosidade, INPUT);

  //Inicia conexão com a rede wifi
  Serial.println();
  Serial.println();
  Serial.print("Conectando a rede ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);

  //Espera o servidor conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
 
  // Inicia o Servidor 
  server.begin();
  Serial.println("Servidor Iniciado");
 
  // Retorna o Valor do IP que estará nosso servidor na Rede.
  Serial.print("Usar essa URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

void loop() {
  delay(1000);
  
  valorObservado = analogRead(pinoSensorLuminosidade);
   
  if(valorObservado < limiteClaro){
    if(valorObservado < limiteEscuro){
      //Não acende o LED
      digitalWrite(pinoLedGroove, LOW);
      }else{
        //Acende  o LED sólido
        digitalWrite(pinoLedGroove, HIGH);
        }
  }else{
    //Pisca o LED três vezes
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

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("Novo cliente");
  while(!client.available()){
    delay(1);
  }

   String request = client.readStringUntil('\r');
   Serial.println(request);
   

   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println(""); 
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   client.println("<HEAD><meta http-equiv=\"refresh\" content=\"1\"></HEAD>");
   client.print("Valor observado pelo sensor: ");
   client.print(valorObservado);
   client.println("<br><br>");
   client.println("</html>");

   
}
