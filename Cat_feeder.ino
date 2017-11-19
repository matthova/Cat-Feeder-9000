// This is code for the cat feeder 9000™
// Every 24 hours, the cat feeder is spun to its next position
//
// By pushing a button, the feeder can be manually moved to its next position
// Once the button is pushed, the countdown is reset
//
// In other words, if it is supposed to rotate at 7AM, but you push the button at 6AM
// Its next rotation will be in 24 hours, at 6AM

// DECLARE I/O PINS
#define BUTTON_PIN 12
#define OPTICAL_PIN 11
#define MOTOR_PIN 9
#define MOTOR_POWER 255

// DECLARE NUMERICAL CONSTANTS
#define ONE_MINUTE 60000
#define ONE_HOUR 3600000
#define ONE_DAY 86400000

// Add elapsedMillis library to keep track of how much time has passed
#include <elapsedMillis.h>
//declaring this variable global to prevent it from resetting on each loop
elapsedMillis timeElapsed;

void setup() {
  // Declare IO
  pinMode(BUTTON_PIN, INPUT);
  pinMode(OPTICAL_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  // Set Motor to OFF
  analogWrite(MOTOR_PIN, 0);
}

// This function spins the tray to its next position
void spin_tray() {
  // Nudge the tray out of the "ON" zone
  analogWrite(MOTOR_PIN, MOTOR_POWER);
  delay(1500);

  // Nudge the tray and then check if the Optical endstop reached the endpoint
  while(digitalRead(OPTICAL_PIN) != 0) {
    analogWrite(MOTOR_PIN, MOTOR_POWER);
    delay(10);
    analogWrite(MOTOR_PIN, 0);
    delay(40);
  }
}

void loop() {
  // If the button has been pushed or its been more than 24 hours
  // SPIN THAT TRAY!!!! and reset the time counter too
  if (digitalRead(BUTTON_PIN) == 1 || timeElapsed > ONE_DAY) {
    timeElapsed = 0;
    spin_tray();
  }
  delay(10);
}