/*
    CARTOGRAFÍAS SONORAS
    Honorino Garcia Mayo 2025
    Dibuja en Pantalla la brujula
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