# ESP32 Network Monitor

Sistema embarcado para monitoramento de disponibilidade de hosts utilizando **ESP32**, desenvolvido em **C++** com o framework **Arduino**.

O projeto realiza testes periódicos de conectividade (ICMP Ping e HTTP/HTTPS), registra estatísticas de disponibilidade e disponibiliza uma interface web responsiva para consulta em tempo real.

Este projeto foi desenvolvido como estudo de sistemas embarcados aplicados ao monitoramento de infraestrutura de redes, servindo também como base para um artigo técnico.

---

## Características

* Monitoramento simultâneo de múltiplos hosts
* Testes via ICMP (Ping)
* Testes via HTTP e HTTPS
* Interface Web embarcada
* Atualização automática das informações
* Histórico de disponibilidade
* Tempo de resposta (latência)
* Estatísticas de uptime
* Configuração por arquivo JSON
* Registro de eventos em memória
* Baixo consumo de recursos
* Operação totalmente independente de servidores externos

---

## Arquitetura

```
                  ┌────────────────────────────┐
                  │        Configuração        │
                  │        config.json         │
                  └─────────────┬──────────────┘
                                │
                                ▼
                    ┌────────────────────┐
                    │  Gerenciador de    │
                    │   Monitoramento    │
                    └─────────┬──────────┘
                              │
          ┌───────────────────┼────────────────────┐
          │                   │                    │
          ▼                   ▼                    ▼
   ICMP Ping Task      HTTP Check Task     HTTPS Check Task
          │                   │                    │
          └───────────────┬───┴────────────────────┘
                          ▼
                Atualização das Métricas
                          │
                          ▼
                Histórico / Estatísticas
                          │
                          ▼
                 Servidor Web (ESP32)
                          │
                          ▼
                    Navegador do usuário
```

---

## Tecnologias utilizadas

* ESP32
* Arduino Framework
* PlatformIO
* ESPAsyncWebServer
* AsyncTCP
* ArduinoJson
* LittleFS
* FreeRTOS (Tasks)

---

## Estrutura do projeto

```
src/
 ├── main.cpp
 ├── network/
 ├── monitor/
 ├── web/
 ├── storage/
 └── utils/

data/
 ├── index.html
 ├── style.css
 ├── script.js
 └── config.json

include/
lib/
platformio.ini
```

*(A estrutura pode variar conforme a organização do projeto.)*

---

## Funcionamento

1. O ESP32 conecta-se à rede.
2. Carrega a configuração dos hosts.
3. Cria as tarefas de monitoramento.
4. Executa verificações periódicas.
5. Atualiza as estatísticas.
6. Disponibiliza as informações através da interface web.

Todo o processamento ocorre localmente no ESP32, sem dependência de serviços em nuvem.

---

## Interface Web

A interface apresenta:

* Status de cada host
* Tempo de resposta
* Disponibilidade (%)
* Histórico de verificações
* Última atualização
* Informações em tempo real

Todo o conteúdo é servido diretamente pelo ESP32 utilizando LittleFS.

---

## Compilação

### Requisitos

* PlatformIO
* ESP32 Arduino Framework

Clone o projeto:

```bash
git clone https://github.com/seuusuario/esp32-network-monitor.git
```

Compile:

```bash
pio run
```

Grave o firmware:

```bash
pio run --target upload
```

Envie os arquivos da interface:

```bash
pio run --target uploadfs
```

---

## Aplicações

O projeto pode ser utilizado para:

* Monitoramento de servidores
* Monitoramento de roteadores
* Equipamentos IoT
* Serviços HTTP
* Laboratórios de redes
* Ambientes educacionais
* Estudos de sistemas embarcados

---

## Objetivos do projeto

Este projeto foi desenvolvido com foco em:

* estudo de programação embarcada em C++;
* utilização do ESP32 como plataforma para aplicações de rede;
* implementação de multitarefa utilizando FreeRTOS;
* desenvolvimento de uma interface web embarcada;
* experimentação de técnicas de monitoramento de infraestrutura em dispositivos de baixo custo.

O objetivo principal é demonstrar que sistemas embarcados podem executar tarefas tradicionalmente associadas a computadores convencionais, mantendo simplicidade, baixo consumo de recursos e facilidade de implantação.

---

## Licença

Este projeto é disponibilizado para fins de estudo e pesquisa.

Sinta-se à vontade para utilizá-lo como referência, respeitando os termos da licença adotada pelo repositório.

