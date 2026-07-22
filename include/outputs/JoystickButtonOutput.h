#ifndef BORGUINO_OUTPUTS_JOYSTICK_BUTTON_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_BUTTON_OUTPUT_H

#include <cstdint>

#include "outputs/JoystickOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

class JoystickButtonOutput : public JoystickOutput {
public:
  explicit JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, ValueProvider<bool> &input);

  void update() override;
  void setValue(bool value);

protected:
  uint8_t buttonNumber;
  ValueProvider<bool> &input;
  bool lastValue = false;
};

}  // namespace borguino::outputs

#endif