#ifndef MONITOR_H
#define MONITOR_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <time.h>


//=====================================
// ESTRUTURAS
//=====================================

struct Resultado {

    String nome;
    
    String tipo;

    String host;

    int porta;

    bool online;

    int codigoHttp;

    unsigned long tempo;

    String horario;

    unsigned long timestamp;

};


//=====================================
// BUFFER
//=====================================

#define MAX_RESULTADOS 20

extern Resultado resultados[MAX_RESULTADOS];

extern int totalResultados;

void adicionarResultado(Resultado r);


//=====================================
// WIFI
//=====================================

void conectarWifi();


//=====================================
// NTP
//=====================================

void sincronizarHorario();

String horarioAtual();


//=====================================
// TESTES
//=====================================

void testarHTTP(

    const char* nome,

    const char* url

);

void testarTCP(

    const char* nome,

    const char* host,

    int porta

);


//=====================================
// SAÍDAS
//=====================================

void exibirResultadosSerial();

String uptimeMonitor(); // retorna o tempo desde o boot em formato legível

#endif