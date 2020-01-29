//=================================================================
/* Author: Henry James
 * Date: 23 01 2020
 *
 * This programme is to control a laser lumia device
 * created by Bradely Hind.
 */
//=================================================================
byte digital_pins[] = {0, 1, 3, 4, 7, 8, 12, 13};
byte pwm_pins[] = {5, 6, 9, 10, 11};

// digi input
byte J_UP = 0;
byte J_DOWN = 1;
byte J_LEFT = 3;
byte J_RIGHT = 4;
byte J_AUTO_OFF = 7;
byte FULL_SPIN = 8;
byte L_MAX = 12;
byte L_MIN = 13;


byte analog_in = A0;
int brightness_potentiometer;

// PWM output
byte L_BRIGHTNESS = 5;
byte M_S_LEFT = 6;
byte M_S_RIGHT = 9;
byte M_L_L = 10;
byte M_L_R = 11;

// 0 up 1 down
byte laser_direction = 0;
//=================================================================
void setup() {
  Serial.begin(9600);

  for (byte i; i < 9; i++) {
    pinMode(digital_pins[i], INPUT_PULLUP);
  }

  for (byte i; i < 6; i++) {
    pinMode(pwm_pins[i], OUTPUT);
  }
}
//=================================================================
void loop() {
  set_laser_brightness();

  // keep lazy susan turning
  analogWrite(M_S_LEFT, 255);

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
  brightness_potentiometer = analogRead(analog_in);

  // do some scaling to make the analog in match the laser pwm
  brightness_potentiometer = brightness_potentiometer / 10;
  analogWrite(L_BRIGHTNESS, brightness_potentiometer);
}
//=================================================================
void move_laser(byte = laser_direction) {
  // moves laser up or down dependant on laser_direction
  if (laser_direction == 0) {
    analogWrite(M_L_L, 255);
    delay(1000);
  }
  if (laser_direction == 1) {
    analogWrite(M_L_R, 255);
    delay(1000);
  }
}
//=================================================================
void manual_mode() {

}
//=================================================================
