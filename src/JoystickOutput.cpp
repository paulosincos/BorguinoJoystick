#include "JoystickOutput.h"

JoystickButtonOutput::JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, GenericSignalInput<bool> &input) : JoystickOutput(joystick), buttonNumber(buttonNumber), input(input) {
}

void JoystickButtonOutput::update() {
    joystick.setButton(buttonNumber, input.getValue());
}
