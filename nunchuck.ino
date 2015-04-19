#define JOYSTICK_HIGH 200
#define JOYSTICK_LOW 55

#define DEBOUNCE_INTERVAL 200

int lastJoystickX;
int lastJoystickY;
int lastC;
int lastZ;
unsigned long timeSinceLastButtonPress = 0;

void scanNunchuck() {
  nunchuck_get_data();
  if (mode != MAIN_MENU) {
    if (nunchuck_joyx() > JOYSTICK_HIGH && lastJoystickX <= JOYSTICK_HIGH) {
      changeScale(scale[0] + 1);
    } else if (nunchuck_joyx() < JOYSTICK_LOW && lastJoystickX >= JOYSTICK_LOW) {
      changeScale(scale[0] - 1);
    }
    if (nunchuck_joyy() > JOYSTICK_HIGH && lastJoystickY <= JOYSTICK_HIGH) {
      scaleType = (scaleType + 1) % SCALE_TYPES;
      changeScale(scale[0]);
    } else if (nunchuck_joyy() < JOYSTICK_LOW && lastJoystickY >= JOYSTICK_LOW) {
      scaleType = (scaleType + 1) % SCALE_TYPES;
      changeScale(scale[0]);
    }
  }
  if (nunchuck_cbutton() && !lastC && millis() - DEBOUNCE_INTERVAL > timeSinceLastButtonPress) {
    if (mode == MAIN_MENU) {
      mode = FREE;
    }
    timeSinceLastButtonPress = millis();
  }
  if (nunchuck_zbutton() && !lastZ && millis() - DEBOUNCE_INTERVAL > timeSinceLastButtonPress) {
    if (mode == MAIN_MENU) {
      mode = GAME;
    } else if (mode == FREE || mode == GAME) {
      mode = MAIN_MENU;
    }
    timeSinceLastButtonPress = millis();
  }
  lastJoystickX = nunchuck_joyx();
  lastJoystickY = nunchuck_joyy();
  lastC = nunchuck_cbutton();
  lastZ = nunchuck_zbutton();
}
