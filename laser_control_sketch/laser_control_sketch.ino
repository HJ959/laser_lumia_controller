//=================================================================
/* Author: Henry James
* Date: 23 01 2020
*
* This programme is to control a laser lumia device
* created by Bradely Hind.
*
* Rotation  | Low  | High
* Clockwise | 0, 3 | 1, 2
* Anti C'se | 1, 2 | 0, 3
*
* Laser     | Low  | High
* Clockwise | 4, 7 | 5, 6
* Anti C'se | 5, 6  | 4, 7
*/
//=================================================================
#include <stdio.h>
//=================================================================
#define PWM_HIGH 255
#define PWM_LOW 0

// digi input
#define J_UP 8
#define J_DOWN 9
#define J_LEFT 10
#define J_RIGHT 13
#define J_AUTO_OFF 12

// analogue in
#define potentiometer_in A0
#define L_MAX A1
#define L_MIN A2
#define FULL_SPIN A3

// PWM output
#define L_BRIGHTNESS 11

// motor control susan - output
#define M_S_L_1 0
#define M_S_L_2 1
#define M_S_R_1 2
#define M_S_R_2 3

// motor control laser - output
#define M_L_L_1 4
#define M_L_L_2 5
#define M_L_R_1 6
#define M_L_R_2 7
//=================================================================
// 0 up 1 down
byte laser_direction = 0;
int brightness_potentiometer;
byte input_pins[] = {8, 9, 10, 12, 13};
byte output_pins[] = {0, 1, 2, 3, 4, 5, 6, 7, 11};
char analogue_out_pins[3][3] = {"A1", "A2", "A3"};
//=================================================================
void setup() {
  Serial.begin(9600);

  for (byte i; i < 6; i++) {
    pinMode(input_pins[i], INPUT_PULLUP);
  }

  for (byte i; i < 9; i++) {
    pinMode(output_pins[i], OUTPUT);
  }

  for (byte i; i < 9; i++) {
    pinMode(analogue_out_pins[i], INPUT_PULLUP);
  }
}
//=================================================================
void loop() {
  set_laser_brightness();

  // keep lazy susan turning
  analogWrite(M_S_L_1, PWM_LOW);
  analogWrite(M_S_R_2, PWM_LOW);
  analogWrite(M_S_L_2, PWM_HIGH);
  analogWrite(M_S_R_1, PWM_HIGH);

  if (digitalRead(L_MAX) == LOW) {
    laser_direction = 0;
  }

  if (digitalRead(L_MIN) == LOW) {
    laser_direction = 1;
  }

  move_laser(laser_direction);

  // only continue auto when full rotation of lazy susan
  for (;;) {
    set_laser_brightness();
    if (digitalRead(FULL_SPIN) == LOW) {
      break;
    }
  }
}
//=================================================================
void manual_mode() {
  // function that will allow the joystick to control the laser
}
//=================================================================
void set_laser_brightness() {
  // Checks the analog in, sets the brightness of the laser via PWM
  brightness_potentiometer = analogRead(potentiometer_in);
  // do some scaling to make the analog in match the laser pwm
  brightness_potentiometer = brightness_potentiometer / 4;

  if (brightness_potentiometer < PWM_HIGH && brightness_potentiometer > PWM_LOW) {
                  analogWrite(L_BRIGHTNESS, brightness_potentiometer);
  }
}
//=================================================================
void move_laser(byte laser_direction) {
  // Moves laser up or down dependant on laser_direction
  // Laser     | Low  | High
  // Clockwise | 4, 7 | 5, 6
  // Anti C'se | 5, 6  | 4, 7
  if (laser_direction == 0) {
    analogWrite(M_L_L_1, PWM_LOW);
    analogWrite(M_L_R_2, PWM_LOW);
    analogWrite(M_L_R_1, PWM_HIGH);
    analogWrite(M_L_L_2, PWM_HIGH);
    delay(1000);
  }
  if (laser_direction == 1) {
    analogWrite(M_L_L_1, PWM_HIGH);
    analogWrite(M_L_R_2, PWM_HIGH);
    analogWrite(M_L_R_1, PWM_LOW);
    analogWrite(M_L_L_2, PWM_LOW);
    delay(1000);
  }
}
//=================================================================
//void manual_mode() {
//}
//=================================================================

