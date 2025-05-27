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
"config.h"
Configuración Comunicaciones
SSID: PERANCHU
PASS: TexucaLana72
Ip 192.168.1.205
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


const char *ssid = "PERANCHU";
const char *password = "TexucaLana72";

const IPAddress ip(192, 168, 1, 205);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

const IPAddress outIP(192, 168, 1, 100);  // IP Ordenador que recibe los datos
const unsigned int outPort = 9999;
const unsigned int localPort = 8888;


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