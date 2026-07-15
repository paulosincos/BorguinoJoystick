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
  explicit JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, ValueProvider<bool> &input);

  void update() override;

protected:
  uint8_t buttonNumber;
  ValueProvider<bool> &input;
};

class JoystickXAxisOutput : public JoystickOutput
{
public:
  explicit JoystickXAxisOutput(Joystick_ &joystick, ValueProvider<uint32_t> &input);

  void update() override;

protected:
  ValueProvider<uint32_t> &input;
};

class JoystickYAxisOutput : public JoystickOutput
{
public:
  explicit JoystickYAxisOutput(Joystick_ &joystick, ValueProvider<uint32_t> &input);

  void update() override;

protected:
  ValueProvider<uint32_t> &input;
};

class JoystickZAxisOutput : public JoystickOutput
{
public:
  explicit JoystickZAxisOutput(Joystick_ &joystick, ValueProvider<uint32_t> &input);

  void update() override;

protected:
  ValueProvider<uint32_t> &input;
};

#endif
