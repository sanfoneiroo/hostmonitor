#include "web.h"

#include "monitor.h"

#include "config.h"

#include <WebServer.h>


WebServer server(80);

// INICIALIZA WEB

void iniciarWeb(){

    server.on(

        "/",

        [](){

            server.send(

                200,

                "text/html",

                gerarHTML()

            );

        }

    );

    server.begin();

    Serial.println(

        "Servidor web iniciado"

    );

}

// ATENDE REQUISIÇÕES

void atenderWeb(){

    server.handleClient();

}

// GERA HTML

String gerarHTML(){

    String html;

    html += R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta charset="utf-8">

<meta name="viewport"

content="width=device-width, initial-scale=1">

<title>Monitor de Host</title>

<style>

body {

    font-family: Consolas, monospace;

    max-width: 900px;

    margin: 20px auto;

    background: #0b1e0b;

    color: #ffffff;

    text-shadow: 0 0 2px rgba(255,255,255,0.2);

}

table {

    width: 100%;

    border-collapse: collapse;

    font-size: 14px;

}

th,
td {

    border: 1px solid #1f5f1f;

    padding: 6px;

}

th {

    background: #143814;

    color: #ffffff;

}

tr:nth-child(even) {

    background: #112911;

}

.online {

    color: #00ff00;

    font-weight: bold;

}

.offline {

    color: #ff4444;

    font-weight: bold;

}

a {

    color: #ffffff;

    text-decoration: none;

}

</style>

</head>

<body>

)rawliteral";


    // CABEÇALHO

    html += "<h1>Monitor de Host</h1>";

    html += "<div class='info'>";

    html += "<b>ESP32 online há:</b> ";

    html += uptimeMonitor();

    html += "<br>";

    html += "<b>Última atualização:</b> ";

    html += horarioAtual();

    html += "<br>";

    html += "<b>WiFi:</b> ";

    html += WiFi.localIP().toString();

    html += "</div>";

    html += "<br>";


    // TABELA

    html += "<table>";

    html +=

    "<tr>"

    "<th>HOST</th>"

    "<th>Tipo</th>"

    "<th>Status</th>"

    "<th>Tempo</th>"

    "<th>Acesso</th>"

    "</tr>";


    for(

        int i=0;

        i<totalResultados;

        i++

    ){

        Resultado r = resultados[i];


        String url;


        if(

            r.tipo == "HTTP/HTTPS"

        ){

            url = r.host;

        }

        else {

            url =    "http://" + r.host + ":" +

                String(

                    r.porta

                );

        }


        html += "<tr>";


        html += "<td>";

        html += r.nome;

        html += "</td>";


        html += "<td>";

        html += r.tipo;

        if(

            r.porta > 0

        ){

            html += " :";
            
            html +=

                String(

                    r.porta

                );

        }

        html += "</td>";


        html += "<td>";

        html +=

            r.online

            ?

            "<span class='online'>ONLINE</span>"

            :

            "<span class='offline'>OFFLINE</span>";

        html += "</td>";


        html += "<td>";

        html +=

            String(

                r.tempo

            );

        html +=

            " ms";

        html +=

            "</td>";



        html +=

            "<td>";


        if(

            url.length() > 0

        ){

            html +=

                "<a href='"

                +

                url

                +

                "' target='_blank'>"

                "Abrir"

                "</a>";

        }

        else{

            html += "-";

        }


        html +=

            "</td>";


        html +=

            "</tr>";

    }


    html += R"rawliteral(

</table>

</body>

</html>

)rawliteral";


    return html;

}