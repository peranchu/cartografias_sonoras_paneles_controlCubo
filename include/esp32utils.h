/*
              _ _______
    /\        | |__   __|
   /  \   _ __| |_ | | ___  ___
  / /\ \ | '__| __|| |/ _ \/ __|
 / ____ \| |  | |_ | |  __/ (__
/_/    \_\_|   \__||_|\___|\___|

CARTOGRAFÍAS SONORAS
Honorino García Mayo 2025

Panel Principal de control: POSICIÓN - MODO - VELOCIDAD - PICH
"esp32Utils.h"
Configuración Conexión WiFi
*/
#include <Arduino.h>
#include "config.h"

WiFiUDP Udp;

boolean conexion = false;

// Prototipo Función
void PantallaConexion(String);
void WiFiEvent(WiFiEvent_t event);

const char *estado[2] = {"desconectado", "conectado"}; // Estados conexión Pantalla

// Funciín Inicia Conexion WiFi
void ConexionWiFi()
{
    Serial.println("");

    WiFi.disconnect(true);
    WiFi.onEvent(WiFiEvent); // CallBack Eventos conexión

    WiFi.mode(WIFI_STA);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password);

    //Serial.print("iniciado Conexion:\t");
    //Serial.println(ssid);

    PantallaConexion(estado[0]); // Pinta en Pantalla el estado de la conexión "pantalla.h"

    delay(3000);
}
////// FIN CONEXIÓN WIFI ////////////////

// Manejo de Eventos WiFi
void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        // Cuando se conecta
        PantallaConexion(estado[1]);

        //Serial.println("Conexion establecida");
        //Serial.print("IP Address:\t");
        //Serial.println(WiFi.localIP());

        Udp.begin(WiFi.localIP(), localPort);
        conexion = true;
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        // Cuanndo se Deconecta
        //Serial.println("WiFi desconectada");
        conexion = false;

        PantallaConexion(estado[0]);
        break;
    }
}
////// FIN EVENTOS WIFI /////

/*
  _____           _                         __ _              _____
 / ____|         | |                       / _(_)            / ____|
| |     __ _ _ __| |_ ___   __ _ _ __ __ _| |_ _  __ _ ___  | (___   ___  _ __   ___  _ __ __ _ ___
| |    / _` | '__| __/ _ \ / _` | '__/ _` |  _| |/ _` / __|  \___ \ / _ \| '_ \ / _ \| '__/ _` / __|
| |___| (_| | |  | || (_) | (_| | | | (_| | | | | (_| \__ \  ____) | (_) | | | | (_) | | | (_| \__ \
 \_____\__,_|_|   \__\___/ \__, |_|  \__,_|_| |_|\__,_|___/ |_____/ \___/|_| |_|\___/|_|  \__,_|___/
                            __/ |
                           |___/

 Honorino García Mayo 2025
*/