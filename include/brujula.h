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

// LECTURA BRÚJULA
int LecturaRumbo(){
  int x, y, z;
  int acimut;
  compass.read();
  acimut = compass.getAzimuth();
  LecturaCompass = acimut;

  return LecturaCompass;
}
/////////// FIN LECTURA BRÚJULA /////////////