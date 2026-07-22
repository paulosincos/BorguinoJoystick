#ifndef BORGUINO_OUTPUTS_JOYSTICK_RANGED_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_RANGED_OUTPUT_H

#include <cstdint>

#include "outputs/JoystickOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

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

class JoystickRangedOutput : public JoystickOutput {
public:
  explicit JoystickRangedOutput(Joystick_ &joystick, JoystickRangedOutputType outputType, RangedValueProvider<uint32_t> &input);

  void update() override;

protected:
  void setRange(uint32_t minValue, uint32_t maxValue);
  void setValue(uint32_t value);
  
  JoystickRangedOutputType outputType;
  RangedValueProvider<uint32_t> &input;
  uint32_t lastValue = 0;
};

}  // namespace borguino::outputs

#endif