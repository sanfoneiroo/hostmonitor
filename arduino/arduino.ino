#include <SPI.h>
#include <Ethernet.h>

//=========================
// Tempo entre verificações de internet
//=========================
const unsigned long INTERVALO_INTERNET = 30000; // 30 segundos
unsigned long ultimaVerificacao = 0;

//=========================
// PINOS DOS LEDs
//=========================
const int LED1 = 7; 
const int LED2 = 8; 
const int LED3 = 9;

//=========================
// TESTE HTTP
//=========================
constexpr const char* httpServidor1 = "erwindemattos.com.br"; 
constexpr const char* httpServidor2 = "google.com"; 

//=========================
// TESTE TCP
//=========================
constexpr const char* tcpServidor1 = "192.168.10.100"; 
constexpr int tcpPorta1 = 3000; 

//---------------------------------------------------------
// Configuração do módulo W5500
//---------------------------------------------------------
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

const int CS_PIN = 5;
EthernetClient client;

//---------------------------------------------------------
// Função para checar servidor HTTP
//---------------------------------------------------------
bool verificarHostHTTP(const char* host, int porta = 80) {
  if (client.connect(host, porta)) {
    client.println(F("GET / HTTP/1.1"));
    client.print(F("Host: "));
    client.println(host);
    client.println(F("Connection: close"));
    client.println(); 

    unsigned long inicio = millis();
    bool statusOk = false;
    
    // Array para armazenar o início da resposta
    char respostaInicial[16]; 
    int indice = 0;

    // Aguarda a resposta (timeout de 5 segundos)
    while (!client.available() && millis() - inicio < 5000) {
      delay(10);
    }

    if (client.available()) {
      // Aguarda o recebimento do pacote TCP
      delay(50);
      
      // Lê os primeiros 15 caracteres para pegar o status
      while (client.available() && indice < 15) {
        respostaInicial[indice++] = client.read();
      }
      respostaInicial[indice] = '\0'; // Finaliza a string C

      // Se o servidor respondeu com "HTTP", ele está online
      if (strstr(respostaInicial, "HTTP") != NULL) {
        statusOk = true;
      }
      
      // Limpa os dados restantes do buffer para liberar o socket
      while (client.available()) {
        client.read(); 
      }
    }

    client.stop();
    return statusOk;
  }
  
  return false;
}

//---------------------------------------------------------
// Função para checar porta TCP
//---------------------------------------------------------
bool verificarHostTCP(const char* host, int porta) {
  if (client.connect(host, porta)) {
    client.stop();
    return true;
  }
  return false;
}

//---------------------------------------------------------
// SETUP
//---------------------------------------------------------
void setup() {
  delay(1000); 

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Mantem o SPI do Uno como master no pino 10
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  Ethernet.init(CS_PIN);

  if (Ethernet.begin(mac) == 0) {
    while (true);
  }

  // Primeira verificação para ligar o painel visual
  digitalWrite(LED1, verificarHostHTTP(httpServidor1) ? HIGH : LOW);
  digitalWrite(LED2, verificarHostHTTP(httpServidor2) ? HIGH : LOW);
  digitalWrite(LED3, verificarHostTCP(tcpServidor1, tcpPorta1) ? HIGH : LOW);

  ultimaVerificacao = millis();
}

//---------------------------------------------------------
// LOOP
//---------------------------------------------------------
void loop() {
  // Mantém o IP ativo
  Ethernet.maintain();

  if (millis() - ultimaVerificacao >= INTERVALO_INTERNET) {
    ultimaVerificacao = millis();
    
    // Atualiza os LEDs com base no status HTTP e TCP
    digitalWrite(LED1, verificarHostHTTP(httpServidor1) ? HIGH : LOW);
    digitalWrite(LED2, verificarHostHTTP(httpServidor2) ? HIGH : LOW);
    digitalWrite(LED3, verificarHostTCP(tcpServidor1, tcpPorta1) ? HIGH : LOW);
  }
}