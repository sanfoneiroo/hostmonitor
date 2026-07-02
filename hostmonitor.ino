/*

  Monitor de Uptime - ESP32

  Este código monitora a disponibilidade de serviços HTTP e TCP, exibindo os resultados no console serial e em uma interface web.

  Configurações:
  - Defina os intervalos de teste e os detalhes dos servidores HTTP e TCP no arquivo "config.h".

  Funcionalidades:
  - Conecta-se à rede Wi-Fi.
  - Sincroniza o horário usando NTP.
  - Inicia um servidor web para exibir os resultados dos testes.
  - CSS leve e otimizado inspirado nos terminais de NOCs.
  - Realiza testes periódicos de HTTP e TCP, registrando os resultados.

Erwin de Mattos, 19 de junho de 2026
*/

#include "config.h"
#include "monitor.h"
#include "web.h"

unsigned long ultimoTeste = 0;

void setup() {

    unsigned long tempoBoot = millis();

    Serial.begin(115200);

    conectarWifi();

    sincronizarHorario();

    iniciarWeb();

}

void loop() {

    // atende requisições web o tempo todo

    atenderWeb();

    // verifica se chegou a hora de testar

    unsigned long agora = millis();

    if (

        agora - ultimoTeste

        >=

        intervaloTeste

    ) {

        ultimoTeste = agora;

        testarHTTP(

            httpNome1,

            httpServidor1

        );

        testarHTTP(

            httpNome2,

            httpServidor2

        );

        testarHTTP(

            httpNome3,

            httpServidor3

        );

        testarTCP(

            tcpNome1,

            tcpServidor1,

            tcpPorta1

        );

        testarTCP(

            tcpNome2,

            tcpServidor2,

            tcpPorta2

        );

        testarTCP(

            tcpNome3,

            tcpServidor3,

            tcpPorta3

        );

        exibirResultadosSerial();

    }

}