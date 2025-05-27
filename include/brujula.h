/*
              _ _______
    /\        | |__   __|
   /  \   _ __| |_ | | ___  ___
  / /\ \ | '__| __|| |/ _ \/ __|
 / ____ \| |  | |_ | |  __/ (__
/_/    \_\_|   \__||_|\___|\___|

CARTOGRAFÍAS SONORAS
Honorino García Mayo 2025

Panel Principal de control: POSICIÓN y MODO
Lectura del Magnetómetro QMC5883L
*/

#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <U8g2lib.h>

QMC5883LCompass compass; // Magnetómetro

int LecturaCompass = 0;

// PARAMS ENVIO RUMBO
unsigned long PTimeCompass = 0;
unsigned long timerCompass = 0;
int TimeOutCompass = 300;
int UmbralCompass = 1;
bool MovimientoCompass = true;

int rumboPrevio = 0;
int varCompass = 0;
/////////////////////

// Envio posicion compas Granular
void EnvioGranular(int rumboGranular)
{
  varCompass = abs(rumboGranular - rumboPrevio);

  if (varCompass > UmbralCompass)
  {
    PTimeCompass = millis();
  }
  timerCompass = millis() - PTimeCompass;

  if (timerCompass < TimeOutCompass)
  {
    MovimientoCompass = true;
  }
  else
  {
    MovimientoCompass = false;
  }

  if(MovimientoCompass == true)
  {
    OSCMessage Rumbo("/rumbo");
    Rumbo.add(int(rumboGranular));
    Udp.beginPacket(outIP, outPort);
    Rumbo.send(Udp);
    Udp.endPacket();
    Rumbo.empty();

    rumboPrevio = rumboGranular;
  }
}

// LECTURA BRÚJULA
int LecturaRumbo()
{
  int x, y, z;
  int acimut;
  compass.read();
  acimut = compass.getAzimuth();
  LecturaCompass = acimut;

  return LecturaCompass;
}
/////////// FIN LECTURA BRÚJULA /////////////

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