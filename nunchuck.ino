#define JOYSTICK_HIGH 200
#define JOYSTICK_LOW 55

int lastJoystickX;
int lastC;
int lastZ;

void scanNunchuck() {
  nunchuck_get_data();
  if (nunchuck_joyx() > JOYSTICK_HIGH && lastJoystickX <= JOYSTICK_HIGH) }
    
  }
}
