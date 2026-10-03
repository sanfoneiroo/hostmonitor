# Hardware Network Monitor (Hostmonitor)

Este projeto investiga e demonstra o uso de plataformas embarcadas de baixo custo para monitoramento de infraestrutura de redes e serviços web. 

O objetivo é provar que tarefas de validação de *uptime* — tradicionalmente executadas por servidores complexos — podem ser delegadas a microcontroladores operando de forma 100% local, autônoma e com baixo consumo de energia.

Atualmente, o repositório abriga **duas versões** do projeto, cada uma com uma filosofia de arquitetura e interface distintas:

### [Versão Piloto: ESP32 (Dashboard Web)](./esp32)
A versão original focada em riqueza de dados. O ESP32 atua como o motor de monitoramento e o próprio servidor de interface.
* **Interface:** Dashboard web responsivo (HTML/CSS/JS) servido diretamente do microcontrolador.
* **Recursos:** Ping ICMP nativo, histórico recente, estatísticas de uptime e tempo de resposta em milissegundos.
* **Cenário:** Ideal para quem deseja acompanhar métricas detalhadas em qualquer navegador da rede sem subir instâncias de ferramentas pesadas (como Zabbix/Grafana).

### [Versão Minimalista: Arduino Uno + W5500 (NOC Físico)](./arduino)
Uma reescrita arquitetural focada em resiliência extrema de hardware e operação 24/7.
* **Interface:** Puramente tátil e física, sinalizando o status da rede (UP/DOWN) em tempo real via painel de LEDs.
* **Recursos:** Contorno de limites severos de hardware (2KB RAM), Watchdog Timer nativo contra travamentos, teste cru de soquetes TCP locais e injeção de cabeçalhos HTTP brutos.
* **Cenário:** Projetado para ser pendurado em um rack de Homelab ou ambiente de produção como um "Painel NOC" inquebrável, imune a quedas de roteador e sem depender de telas para avisar quando um serviço cai.

---