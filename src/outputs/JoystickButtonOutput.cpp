#include "outputs/JoystickButtonOutput.h"

namespace borguino::outputs {

JoystickButtonOutput::JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, ValueProvider<bool> &input)
    : JoystickOutput(joystick), buttonNumber(buttonNumber), input(input) {
}

void JoystickButtonOutput::update() {
  joystick.setButton(buttonNumber, input.getValue());
}

}  // namespace borguino::outputs