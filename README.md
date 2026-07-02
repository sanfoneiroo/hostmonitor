# ESP32 Network Monitor

Sistema embarcado para monitoramento de disponibilidade de dispositivos e serviços de rede utilizando o microcontrolador ESP32.

O projeto realiza verificações periódicas de conectividade em hosts configurados, registrando informações como disponibilidade, tempo de resposta e estatísticas de uptime, disponibilizando todos os dados através de uma interface web hospedada diretamente no próprio ESP32.

O desenvolvimento teve como objetivo investigar a utilização de plataformas embarcadas de baixo custo em aplicações de monitoramento de infraestrutura de redes, demonstrando que tarefas tradicionalmente executadas por computadores ou servidores podem ser implementadas de forma eficiente em um microcontrolador.

---

# Principais funcionalidades

* Monitoramento simultâneo de múltiplos hosts.
* Verificação de disponibilidade por ICMP (Ping).
* Verificação de serviços HTTP e HTTPS.
* Medição do tempo de resposta.
* Cálculo de disponibilidade (uptime).
* Registro do horário da última verificação.
* Histórico recente das consultas realizadas.
* Interface web responsiva acessível por qualquer navegador.
* Funcionamento totalmente local, sem dependência de serviços externos.
* Baixo consumo de recursos computacionais.

---

# Arquitetura do software

O firmware foi desenvolvido integralmente em C++ utilizando a Arduino IDE.

A aplicação segue uma arquitetura modular, onde cada componente é responsável por uma etapa específica do monitoramento.

```text
                 Inicialização
                       │
                       ▼
             Configuração da rede
                       │
                       ▼
          Inicialização do servidor Web
                       │
                       ▼
          Carregamento da lista de hosts
                       │
                       ▼
        ┌─────────────────────────────────┐
        │        Loop principal           │
        │                                 │
        │ • Controle dos temporizadores   │
        │ • Execução dos testes           │
        │ • Atualização das métricas      │
        │ • Atendimento HTTP              │
        └─────────────────────────────────┘
                       │
                       ▼
             Interface Web embarcada
```

Todo o processamento ocorre localmente no ESP32. O servidor web, o mecanismo de monitoramento e o armazenamento das estatísticas executam no mesmo firmware, dispensando qualquer infraestrutura adicional.

---

# Funcionamento

Após a energização do equipamento, o firmware executa as seguintes etapas:

1. Inicializa a interface de rede.
2. Conecta-se à rede Wi-Fi configurada.
3. Inicializa o servidor HTTP.
4. Carrega a lista de dispositivos monitorados.
5. Inicia o ciclo contínuo de verificações.
6. Atualiza as estatísticas de disponibilidade.
7. Disponibiliza os resultados na interface web.

As verificações são executadas continuamente em intervalos definidos pelo firmware, permitindo acompanhamento praticamente em tempo real da disponibilidade dos equipamentos monitorados.

---

# Interface Web

A interface foi desenvolvida utilizando HTML, CSS e JavaScript incorporados diretamente ao código-fonte do firmware.

Dessa forma, não há necessidade de utilizar sistemas de arquivos embarcados como SPIFFS ou LittleFS. Todo o conteúdo da página é enviado diretamente pelo servidor HTTP implementado no ESP32.

A interface apresenta:

* Status atual de cada host;
* Tempo de resposta;
* Disponibilidade acumulada;
* Histórico recente das verificações;
* Informações de atualização em tempo real.

---

# Organização do código

O projeto foi desenvolvido utilizando a Arduino IDE.

Embora a implementação seja realizada em um único projeto, o código encontra-se organizado em módulos responsáveis por funções específicas, facilitando a manutenção e futuras expansões.

De forma simplificada, o firmware é composto por:

* Inicialização do sistema;
* Gerenciamento da conectividade Wi-Fi;
* Rotinas de monitoramento ICMP;
* Rotinas de monitoramento HTTP;
* Cálculo das estatísticas;
* Servidor HTTP;
* Geração dinâmica da interface web.

---

# Tecnologias utilizadas

* ESP32
* Arduino IDE
* Linguagem C++
* Wi-Fi
* HTTP
* HTTPS
* ICMP (Ping)
* HTML
* CSS
---

# Compilação

## Requisitos

* Arduino IDE
* Placa ESP32 instalada no Gerenciador de Placas
* Bibliotecas utilizadas pelo projeto

Após abrir o projeto na Arduino IDE:

1. Selecione a placa ESP32 correspondente.
2. Configure a porta serial.
3. Compile o projeto.
4. Grave o firmware na placa.

Após a programação, o equipamento estará pronto para iniciar o monitoramento assim que conectado à rede configurada.

---

# Aplicações

O projeto pode ser empregado em diversos cenários, entre eles:

* Monitoramento de servidores;
* Monitoramento de roteadores;
* Monitoramento de equipamentos IoT;
* Monitoramento de serviços web;
* Laboratórios de redes;
* Ambientes educacionais;
* Estudos sobre sistemas embarcados;
* Projetos acadêmicos.

---

# Limitações

Por se tratar de uma aplicação executada em um microcontrolador, alguns compromissos foram adotados durante o desenvolvimento:

* Quantidade limitada de memória RAM;
* Histórico mantido apenas durante a execução do equipamento;
* Configuração realizada diretamente no código-fonte;
* Ausência de armazenamento persistente das estatísticas.

Essas limitações foram consideradas adequadas aos objetivos didáticos e experimentais do projeto.

---

# Trabalhos futuros

Entre as possíveis evoluções do sistema destacam-se:

* Interface para configuração dos hosts via navegador;
* Armazenamento permanente das estatísticas;
* Exportação de relatórios;
* Suporte a autenticação de usuários;
* Envio de notificações automáticas;
* Integração com plataformas externas de monitoramento;
* Suporte a IPv6;
* Atualização remota do firmware (OTA).

---

# Objetivos do projeto

Este projeto foi desenvolvido com finalidades técnicas e educacionais, buscando explorar o potencial do ESP32 em aplicações de monitoramento de redes.

Além da implementação prática, o desenvolvimento serviu como base para estudos relacionados à programação embarcada, protocolos de comunicação, desenvolvimento de interfaces web embarcadas e análise de disponibilidade de serviços em redes IP.

O projeto demonstra que sistemas embarcados podem executar tarefas de monitoramento de forma confiável para aplicações de pequeno porte, constituindo uma alternativa de baixo custo para fins didáticos, laboratoriais e experimentais.

---

# Licença

Este projeto é disponibilizado para fins acadêmicos e de estudo.

A utilização, modificação e redistribuição são permitidas conforme os termos da licença adotada neste repositório.
