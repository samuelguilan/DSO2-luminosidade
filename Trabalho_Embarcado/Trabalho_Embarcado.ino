//Inclusâo da biblioteca de conexao por wifi
#include <ESP8266WiFi.h>

//Define os pinos dos componentes usados
#define pinoSensorLuminosidade A0
#define pinoLedGroove D7

//Define os limites de luminosidade a serem usados 
int limiteEscuro = 300;
int limiteClaro = 800;

int valorObservado;
char* nivelLuminosidade;

const char* ssid = "Mi Phone";
const char* password = "matheus123";

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
  
  //Recebe o valor do sensor de luminosidade
  valorObservado = analogRead(pinoSensorLuminosidade);

  //Verifica o nível 
  if(valorObservado < limiteClaro){
    if(valorObservado < limiteEscuro){
      nivelLuminosidade = "ESCURO";
      //Não acende o LED
      digitalWrite(pinoLedGroove, LOW);
      }else{
        nivelLuminosidade = "AMENO";
        //Acende  o LED sólido
        digitalWrite(pinoLedGroove, HIGH);
        }
  }else{
    nivelLuminosidade = "CLARO";
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
  //Manda aviso de nova consulta pela porta serial
  Serial.println("Nova consulta");
  while(!client.available()){
    delay(1);
  }
   //Recebe pedido do cliente
   String request = client.readStringUntil('\r');
   Serial.println(request);
   
   //Monta página HTML de resposta
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println(""); 
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   client.println("<HEAD><meta http-equiv=\"refresh\" content=\"1\"></HEAD>");
   client.print("Nivel de luminosidade: ");
   client.print(nivelLuminosidade);
   client.println("<br><br>");
   client.print("Valor observado pelo sensor: ");
   client.print(valorObservado);
   client.println("<br><br>");
   client.println("</html>");

   
}
