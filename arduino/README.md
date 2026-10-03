# Monitor de Serviços e Infraestrutura (Arduino + W5500)

Um sistema de monitoramento de rede em hardware utilizando um Arduino Uno e um módulo Ethernet W5500. Este projeto realiza checagens periódicas da disponibilidade de servidores web externos e serviços TCP locais, fornecendo feedback visual imediato do status da infraestrutura através de LEDs.

## Visão Geral

Projetado para atuar como um painel físico de status (homelab ou ambiente de produção), o código executa testes a cada 30 segundos de forma não-bloqueante. Ele inclui um mecanismo específico nas requisições HTTP que simula o comportamento de um cliente `cURL`, evitando bloqueios comuns de ferramentas automatizadas por CDNs (como Cloudflare) ao verificar domínios externos.

## Funcionalidades

- Monitoramento HTTP Resiliente (Suporte a Redirecionamentos): Requisições GET que procuram por qualquer cabeçalho de resposta válido (buscando pela string "HTTP"). Isso garante compatibilidade com sites modernos que forçam redirecionamento 301/302 para HTTPS, contornando a limitação do W5500 que não possui suporte nativo a SSL/TLS.
- Monitoramento de Portas TCP: Validação direta de conexão de soquete para serviços hospedados localmente (ex: instâncias do Gitea, Nginx, Kathará, ou painéis de gerência).
- Blindagem de Memória (SRAM): Eliminação do uso da classe String e do monitor Serial. Uso intensivo da macro F() para manter os dados textuais na memória Flash (PROGMEM) e pequenos arrays circulares (buffers de 16 bytes) para leitura de cabeçalhos.
- Prevenção de Esgotamento de Sockets: Limpeza proativa de buffers de recepção (while(client.available()) client.read();) antes do fechamento de conexões para evitar que os 8 sockets limitados do chip W5500 fiquem "presos".
- Manutenção de Rede: O loop principal invoca silenciosamente Ethernet.maintain() para renovar a concessão DHCP automaticamente quando expirar, evitando a queda do painel após reboots do roteador.
- Execução Não-Bloqueante: Loop baseado em millis() no lugar de delay().

## Hardware Necessário

- 1x Arduino Uno
- 1x Módulo/Shield Ethernet W5500
- 3x LEDs (Cores sugeridas: Verde para serviços UP, ou cores distintas para cada serviço)
- 3x Resistores de 220Ω ou 330Ω
- Jumpers e Protoboard

## Wiring (Esquema de Pinos)

| Componente | Pino Arduino | Observação |
| :--- | :--- | :--- |
| **W5500 CS** | Digital 5 | Seleção do chip SPI. |
| **Pino SPI Master** | Digital 10 | Mantido em `HIGH` no setup para o Uno atuar como Master. |
| **LED 1 (Site)** | Digital 7 | Status do domínio principal. |
| **LED 2 (Google)**| Digital 8 | Status de conectividade com a internet. |
| **LED 3 (TCP)** | Digital 9 | Status do serviço interno na porta específica. |

*Nota: As conexões padrão SPI (MOSI, MISO, SCK) devem ser ligadas aos pinos correspondentes do Arduino Uno (11, 12 e 13 respectivamente).*

## Configuração e Uso

1. Abra o arquivo na Arduino IDE.
2. Certifique-se de ter as bibliotecas nativas `SPI.h` e `Ethernet.h` instaladas.
3. Modifique as variáveis na seção de configuração para os serviços da sua infraestrutura:

```cpp
//=========================
// TESTE HTTP
//=========================
// Substitua pelos domínios que deseja monitorar na porta 80
constexpr const char* httpServidor1 = "erwindemattos.com.br"; 
constexpr const char* httpServidor2 = "google.com"; 

//=========================
// TESTE TCP
//=========================
// Substitua pelo IP e porta do seu serviço local (ex: Gitea, VPS, Nginx)
constexpr const char* tcpServidor1 = "192.168.10.100"; 
constexpr int tcpPorta1 = 3000; 

//=========================
// TEMPORIZAÇÃO
//=========================
const unsigned long INTERVALO_INTERNET = 30000; // Tempo em milissegundos (30s)
```

1. Compile e carregue o código na placa.

2. Os LEDs acenderão instantaneamente caso os testes na inicialização passem. As próximas atualizações ocorrerão conforme o intervalo configurado.
