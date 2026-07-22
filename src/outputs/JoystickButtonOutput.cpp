#include "outputs/JoystickButtonOutput.h"

namespace borguino::outputs {

JoystickButtonOutput::JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, ValueProvider<bool> &input)
    : JoystickOutput(joystick), buttonNumber(buttonNumber), input(input) {
  setValue(lastValue);
}

void JoystickButtonOutput::update() {
  auto value = input.getValue();
  if (value == lastValue) {
    return;
  }

  setValue(value);
  lastValue = value;
}

void JoystickButtonOutput::setValue(bool value) {
  joystick.setButton(buttonNumber, value);
}

}  // namespace borguino::outputs