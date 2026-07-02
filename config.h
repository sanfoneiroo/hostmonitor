#ifndef CONFIG_H
#define CONFIG_H

//=========================
// WIFI
//=========================

constexpr const char* ssid     = "Sua Rede Wi-Fi";
constexpr const char* password = "sua_senha_wifi";


//=========================
// TESTE HTTP/HTTPS
//=========================

constexpr const char* httpNome1 =
    "Servidor HTTP 1"; // Nome do servidor HTTP 1

constexpr const char* httpServidor1 =
    "https://seudominio1.com.br"; // Endereço do servidor HTTP 1


constexpr const char* httpNome2 =
    "Servidor HTTP 2"; // Nome do servidor HTTP 2

constexpr const char* httpServidor2 =
    "https://seudominio2.com.br"; // Endereço do servidor HTTP 2

constexpr const char* httpNome3 =
    "Servidor HTTP 3"; // Nome do servidor HTTP 3

    constexpr const char* httpServidor3 =
    "http://seudominio3.com.br"; // Endereço do servidor HTTP 3

//=========================
// TESTE TCP
//=========================

constexpr const char* tcpNome1 =
    "Servidor TCP 1";

constexpr const char* tcpServidor1 =
    "123.456.789.254"; // IP do servidor TCP 1

constexpr int tcpPorta1 = 9090; // Porta do servidor TCP 1


constexpr const char* tcpNome2 =
    "Servidor TCP 2";

constexpr const char* tcpServidor2 =
    "123.456.789.253"; // IP do servidor TCP 2

constexpr int tcpPorta2 = 9090;

constexpr const char* tcpNome3 =
    "Servidor TCP 3"; // Porta do servidor TCP 3
    
constexpr const char* tcpServidor3 =
    "123.456.789.252"; // IP do servidor TCP 3

constexpr int tcpPorta3 = 81; // Porta do servidor TCP 3


//=========================
// CONFIGURAÇÕES GLOBAIS
//=========================

constexpr unsigned long intervaloTeste = 60000; // Tempo entre cada teste em milissegundos (60 segundos)

#endif