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
Control de los multiplexiores 74hc165 - 74hc595
Control de los botones
*/


#include <Arduino.h>
#include <Shifter.h>
#include <RoxMux.h>

#define NUM_BUTTONS 8
RoxButton buttons[NUM_BUTTONS];

int num_button;

int counterPlaySpeed = 0;
int counterPitch = 0;

#define MUX_TOTAL 1
Rox74HC165<MUX_TOTAL> mux;   // Control multiplexor 74hc165

//pines control Mux LED
#define SER_IN 5
#define L_CLK 16
#define CLK 17

#define NUM_REGISTER 1 // 74HC595

//pins for 74HC165
#define PIN_DATA 23 // pin 9 on 74HC165 (DATA)
#define PIN_LOAD 19 // pin 1 on 74HC165 (LOAD)
#define PIN_CLK 18  // pin 2 on 74HC165 (CLK))

bool pinState[MUX_TOTAL * 8];

//Almacena los estados de los botones y LED
bool estado_btn_act[8] = {false, false, false, false, false, false, false, false};
bool estado_LED[8] = {false, false, false, false, false, false, false, false};

// MODO 0: Continuo  MODO 1: Granular
bool Modo = 0; // Modo 0 continuo, 1 granular

Shifter Mux_LED(SER_IN, L_CLK, CLK, NUM_REGISTER); // Instancia MUX 74HC595

// Lectura Botón MODO  4  VERDE
void LecturaModo()
{
  mux.update();

  buttons[4].update(mux.read(4), 50, LOW);  //elimina el bouncing

  if (buttons[4].released())   //Al soltar el botón
  {
    estado_btn_act[4] = 0;
    if (estado_btn_act[4] == 0 && estado_LED[4] == false)
    {
      Mux_LED.setPin(4, HIGH);
      Mux_LED.write();
      estado_LED[4] = true;

      Modo = 1;
    }
    else
    {
      Mux_LED.setPin(4, LOW);
      Mux_LED.write();
      estado_LED[4] = false;

      Modo = 0;
    }
  }
}
/////// FIN LECTURA BOTÓN MODO /////

//Lectura Botones Joystick - Pitch - Stop
void LecturaBotones()
{
  mux.update();
  for (int i = 0; i < NUM_BUTTONS; i++)
  {

    buttons[i].update(mux.read(i), 50, LOW);

    // AL PULSAR
    if (buttons[i].pressed())  //AL Pulsar
    {
      num_button = i;

      switch (num_button)
      {
      case 7: // Boton STOP AMARILLO
        Mux_LED.setPin(7, HIGH);
        Mux_LED.write();
        break;

      case 0: // Joystic arriba
        Mux_LED.setPin(0, HIGH);
        Mux_LED.setPin(1, LOW);
        Mux_LED.setPin(2, LOW);
        Mux_LED.setPin(3, LOW);
        Mux_LED.write();

        counterPlaySpeed = 1;
        //Serial.println(counterPlaySpeed);
        break;

      case 1: // Joystic abajo
        Mux_LED.setPin(0, LOW);
        Mux_LED.setPin(1, HIGH);
        Mux_LED.setPin(2, LOW);
        Mux_LED.setPin(3, LOW);
        Mux_LED.write();

        counterPlaySpeed = 0;
        //Serial.println(counterPlaySpeed);
        break;

      case 2: // Joystic derecha
        Mux_LED.setPin(0, LOW);
        Mux_LED.setPin(1, LOW);
        Mux_LED.setPin(2, HIGH);
        Mux_LED.setPin(3, LOW);
        Mux_LED.write();

        if ((counterPlaySpeed > -3) && (counterPlaySpeed < 2))
        {
          counterPlaySpeed += 1;
          //Serial.println(counterPlaySpeed);
        }
        break;

      case 3: // Joystic izquierda
        Mux_LED.setPin(0, LOW);
        Mux_LED.setPin(1, LOW);
        Mux_LED.setPin(2, LOW);
        Mux_LED.setPin(3, HIGH);
        Mux_LED.write();

        if ((counterPlaySpeed > -2) && (counterPlaySpeed < 3))
        {
          counterPlaySpeed -= 1;
          //Serial.println(counterPlaySpeed);
        }
        break;

      case 5: // PITCH -1 AZUL
        Mux_LED.setPin(5, HIGH);
        Mux_LED.write();
        break;

      case 6: // PITCH +1 ROJO
        Mux_LED.setPin(6, HIGH);
        Mux_LED.write();
        break;
      }
    }

    // AL LIBERAR
    else if (buttons[i].released(true))
    {
      num_button = i;

      switch (num_button)
      {
      case 7: // Boton Stop AMARILLO
        Mux_LED.clear();  //Limpia los LED
        Mux_LED.write();

        //Restaura estado boton MODE
        estado_btn_act[4] = 0;
        estado_LED[4] = false;

        Modo = 0;
        break;

      case 5: // PITCH -1 AZUL
        Mux_LED.setPin(5, LOW);
        Mux_LED.write();

        if((counterPitch > -8) && (counterPitch < 9)){
          counterPitch -= 1;
          Serial.println(counterPitch);
        }
        break;

      case 6: // PITCH +1 ROJO
        Mux_LED.setPin(6, LOW);
        Mux_LED.write();

         if((counterPitch > -9) && (counterPitch < 8)){
          counterPitch += 1;
          Serial.println(counterPitch);
        }
        break;

      //Joystick  Cambio estado LED
      case 0: // Joystic arriba
        Mux_LED.setPin(0, LOW);
        Mux_LED.setPin(1, LOW);
        Mux_LED.setPin(2, LOW);
        Mux_LED.setPin(3, LOW);
        Mux_LED.write();  
        break;

      case 1: // Joystic abajo
        Mux_LED.setPin(0, LOW);
        Mux_LED.setPin(1, LOW);
        Mux_LED.setPin(2, LOW);
        Mux_LED.setPin(3, LOW);
        Mux_LED.write();  
        break; 
        
      case 2: // Joystic derecha
        Mux_LED.setPin(0, LOW);
        Mux_LED.setPin(1, LOW);
        Mux_LED.setPin(2, LOW);
        Mux_LED.setPin(3, LOW);
        Mux_LED.write();  
        break;  

      case 3: // Joystic izquierda
        Mux_LED.setPin(0, LOW);
        Mux_LED.setPin(1, LOW);
        Mux_LED.setPin(2, LOW);
        Mux_LED.setPin(3, LOW);
        Mux_LED.write();  
        break;  
      }
    }
    //Al mantener  Reset Pitch ROJO
    else if(buttons[6].held())
    {
      Mux_LED.setPin(6, LOW);
      Mux_LED.write();
      counterPitch = 0;
      Serial.println(counterPitch);

    }
  }
}
///// FIN LECTURA BOTONES //////

// LIMPIEZA LED
void clearLED()
{
  Mux_LED.setPin(0, LOW);
  Mux_LED.setPin(1, LOW);
  Mux_LED.setPin(2, LOW);
  Mux_LED.setPin(3, LOW);
  Mux_LED.write();
}