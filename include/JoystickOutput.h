#ifndef JOYSTICK_OUTPUT_H
#define JOYSTICK_OUTPUT_H

#include <Joystick.h>

#include "PinInput.h"
#include "SignalOutput.h"

class JoystickOutput : public SignalOutput
{
public:
  explicit JoystickOutput(Joystick_ &joystick) : joystick(joystick) {};

protected:
  Joystick_ &joystick;
};

class JoystickButtonOutput : public JoystickOutput
{
public:
  explicit JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, GenericSignalInput<bool> &input);

  void update() override;

protected:
  uint8_t buttonNumber;
  GenericSignalInput<bool> &input;
};

#endif
