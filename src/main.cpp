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
*/

#include <Arduino.h>
#include <Wire.h>
#include <OSCMessage.h>
#include "pantalla.h"
#include "brujula.h"
#include "botones.h"

// MODOS
int continuo = 0;
int granular = 0;

// Primera entrada a las posiciones, configuraciones de MODO
bool continuoMes = false;
bool granularMes = false;

// Almacena posicion de MODO
bool posContinuo;
bool posGranular;

float headingDegrees;
int rumboContinuo = 0;

void setup()
{
  Serial.begin(115200);
  delay(300);

  Wire.begin();
  delay(300);

  compass.init();
  compass.setSmoothing(10, true);

  mux.begin(PIN_DATA, PIN_LOAD, PIN_CLK); // inicio multiplexor 74hc165

  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    // the .begin() method starts the debouncing timer
    buttons[i].begin();
  }

  Mux_LED.clear();
  Mux_LED.write();
  delay(500);

  // Secuencia arranque LEDS
  for (int i = 0; i < 8; i++)
  {
    Mux_LED.setPin(i, HIGH);
    Mux_LED.write();
    delay(100);
    Mux_LED.setPin(i, LOW);
    Mux_LED.write();
    delay(100);
  }

  u8g2.begin(); // Inicio Pantalla
  delay(100);

  PantallaInicio();

  u8g2.clear();
  u8g2.clearBuffer();
  delay(100);

  ConexionWiFi();
}
////// FIN SETUP /////////////////

void loop()
{
  // Si existe conexión
  if (conexion)
  {
    LecturaModo(); // LECTURA BOTON MODO "botones.h"

    if (Modo == 0)
    { // MODO Continuo

      if (continuoMes == false)
      {             // Primera vez que entra en MODO Continuo
        clearLED(); // Apaga LED que estén encendidos  "botones.h"
        delay(100);

        continuoMes = true;
        granularMes = false;
      }
      // Dibujo Pantalla
      DibujoContinuo();
    }
    ////// FIN MODO CONTINUO //////

    if (Modo == 1)
    { // MODO Granular

      if (granularMes == false)
      {
        clearLED(); // Apaga LED que estén encendidos  "botones.h"
        delay(100);

        counterPlaySpeed = 0;
        counterPitch = 0;

        continuoMes = false;
        granularMes = true;
      }

      rumboContinuo = LecturaRumbo(); // Lectura Brújula "brujula.h"

      LecturaBotones();

      EnvioGranular(rumboContinuo);

      // Dibujo Pantalla
      u8g2.clearBuffer();
      u8g2.firstPage();
      do
      {
        drawCompass(rumboContinuo, counterPlaySpeed, counterPitch);  //Dibujo en Pantalla
      } while (u8g2.nextPage());
      delay(100);
    }
  }
}

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
