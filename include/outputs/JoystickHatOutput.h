#ifndef BORGUINO_OUTPUTS_JOYSTICK_HAT_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_HAT_OUTPUT_H

#include <cstddef>
#include <cstdint>

#include "ValueProvider.h"
#include "outputs/JoystickOutput.h"

namespace borguino::outputs {

class JoystickHatOutput : public JoystickOutput {
public:
  explicit JoystickHatOutput(Joystick_ &joystick, uint8_t hatNumber, ValueProvider<bool> *const *inputs, size_t inputCount, bool combineInputs);

  void update() override;

protected:
  int16_t getHatDirection() const;

  uint8_t hatNumber;
  ValueProvider<bool> *const *inputs;
  size_t inputCount;
  bool combineInputs;
  int16_t lastHatDirection;
};

}  // namespace borguino::outputs

#endif