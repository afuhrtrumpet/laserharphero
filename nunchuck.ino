#define JOYSTICK_HIGH 200
#define JOYSTICK_LOW 55

int lastJoystickX;
int lastJoystickY;
int lastC;
int lastZ;

void scanNunchuck() {
  nunchuck_get_data();
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
  if (nunchuck_cbutton() && !lastC) {
    if (mode == MAIN_MENU) {
      mode = FREE;
    }
  }
  if (nunchuck_zbutton() && !lastZ) {
    if (mode == MAIN_MENU) {
      mode = GAME;
    }
  }
  lastJoystickX = nunchuck_joyx();
  lastJoystickY = nunchuck_joyy();
  lastC = nunchuck_cbutton();
  lastZ = nunchuck_zbutton();
}
