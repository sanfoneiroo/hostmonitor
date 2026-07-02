#include "monitor.h"
#include "config.h"

unsigned long tempoBoot = 0; // tempo em que o dispositivo iniciou

//=====================================
// BUFFER
//=====================================

Resultado resultados[MAX_RESULTADOS];

int totalResultados = 0;


void adicionarResultado(Resultado r){

    // procura se já existe

    for(int i=0;i<totalResultados;i++){

        if(

            resultados[i].tipo == r.tipo

            &&

            resultados[i].host == r.host

            &&

            resultados[i].porta == r.porta

        ){

            resultados[i] = r;

            return;

        }

    }

    // adiciona novo

    if(totalResultados < MAX_RESULTADOS){

        resultados[totalResultados] = r;

        totalResultados++;

    }

}



//=====================================
// WIFI
//=====================================

void conectarWifi() {

    Serial.println();

    Serial.println(

        "Conectando WiFi..."

    );

    WiFi.disconnect(true);

    delay(1000);

    WiFi.mode(WIFI_STA);

    WiFi.begin(

        ssid,

        password

    );

    while(

        WiFi.status()

        !=

        WL_CONNECTED

    ){

        delay(500);

        Serial.print(".");

    }

    Serial.println();

    Serial.print("IP: ");

    Serial.println(

        WiFi.localIP()

    );

}



//=====================================
// NTP
//=====================================

void sincronizarHorario() {

    configTime(

        -3 * 3600,

        0,

        "pool.ntp.org",

        "time.nist.gov"

    );

    struct tm timeinfo;

    Serial.print(

        "Sincronizando NTP"

    );

    while(

        !getLocalTime(

            &timeinfo

        )

    ){

        Serial.print(".");

        delay(500);

    }

    Serial.println();

    Serial.println(

        "Horario sincronizado"

    );

}



//=====================================
// AUXILIARES
//=====================================

String horarioAtual() {

    struct tm timeinfo;

    if(

        !getLocalTime(

            &timeinfo

        )

    )

        return "SEM HORA";

    char buffer[30];

    strftime(

        buffer,

        sizeof(buffer),

        "%d/%m/%Y %H:%M:%S",

        &timeinfo

    );

    return String(buffer);

}



//=====================================
// TESTE HTTP
//=====================================

void testarHTTP(

    const char* nome,
    const char* url

){

    Resultado r;
    
    r.nome = nome;

    r.tipo = "HTTP/HTTPS";

    r.host = url;

    r.porta = 0;

    r.horario =

        horarioAtual();

    r.timestamp =

        time(nullptr);

    unsigned long t0 = millis();

    HTTPClient http;

    http.begin(url);

    r.codigoHttp =

        http.GET();

    r.tempo =

        millis()-t0;

    r.online =

        r.codigoHttp > 0;

    http.end();

    adicionarResultado(r);

}



//=====================================
// TESTE TCP
//=====================================

void testarTCP(

    const char* nome,
    const char* host,

    int porta

){

    Resultado r;

    r.nome = nome;

    r.tipo = "TCP";

    r.host = host;

    r.porta = porta;

    r.horario =

        horarioAtual();

    r.timestamp =

        time(nullptr);

    r.codigoHttp = -1;

    WiFiClient client;

    unsigned long t0 = millis();

    r.online =

        client.connect(

            host,

            porta

        );

    r.tempo =

        millis()-t0;

    client.stop();

    adicionarResultado(r);

}



//=====================================
// SERIAL
//=====================================

void exibirResultadosSerial(){

    Serial.println();

    Serial.println(

    "========================"

    );

    Serial.println(

    "RESULTADOS"

    );

    Serial.println(

    "========================"

    );

    for(

        int i=0;

        i<totalResultados;

        i++

    ){

        Resultado r =

            resultados[i];

        Serial.print(

            "Tipo: "

        );

        Serial.println(

            r.tipo

        );

        Serial.print(

            "Host: "

        );

        Serial.println(

            r.host

        );

        if(

            r.porta > 0

        ){

            Serial.print(

                "Porta: "

            );

            Serial.println(

                r.porta

            );

        }

        Serial.print(

            "Horario: "

        );

        Serial.println(

            r.horario

        );

        Serial.print(

            "Tempo: "

        );

        Serial.print(

            r.tempo

        );

        Serial.println(

            " ms"

        );

        Serial.print(

            "Status: "

        );

        Serial.println(

            r.online ?

            "ONLINE"

            :

            "OFFLINE"

        );

        if(

            r.tipo == "HTTP"

        ){

            Serial.print(

                "HTTP: "

            );

            Serial.println(

                r.codigoHttp

            );

        }

        Serial.println(

        "------------------------"

        );

    }

}


//=====================================
// TEMPO DE UPTIME DO ESP32
//=====================================

String uptimeMonitor(){

    unsigned long segundos =

        millis() / 1000;

    int dias =

        segundos / 86400;

    segundos %= 86400;

    int horas =

        segundos / 3600;

    segundos %= 3600;

    int minutos =

        segundos / 60;

    segundos %= 60;

    char buffer[50];

    sprintf(

        buffer,

        "%d dias %02d:%02d:%02lu",

        dias,

        horas,

        minutos,

        segundos

    );

    return String(buffer);

}