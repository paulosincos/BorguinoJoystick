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

enum JoystickRangedOutputType {
    Accelerator,
    Brake,
    RotateXAxis,
    RotateYAxis,
    RotateZAxis,
    Rudder,
    Steering,
    Throttle,
    XAxis,
    YAxis,
    ZAxis,
};

class JoystickRangedOutput : public JoystickOutput
{
public:
  explicit JoystickRangedOutput(Joystick_ &joystick, JoystickRangedOutputType outputType, RangedValueProvider<uint32_t> &input);

  void update() override;

protected:
  JoystickRangedOutputType outputType;
  RangedValueProvider<uint32_t> &input;
};

#endif
