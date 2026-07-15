#include "JoystickOutput.h"
#include "AdcSpecs.h"

JoystickButtonOutput::JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, GenericSignalInput<bool> &input) : JoystickOutput(joystick), buttonNumber(buttonNumber), input(input) {
}

void JoystickButtonOutput::update() {
    joystick.setButton(buttonNumber, input.getValue());
}

JoystickXAxisOutput::JoystickXAxisOutput(Joystick_ &joystick, GenericSignalInput<uint32_t> &input) : JoystickOutput(joystick), input(input) {
    joystick.setXAxisRange(ADC_MIN_VALUE, ADC_MAX_VALUE);
}

void JoystickXAxisOutput::update() {
    joystick.setXAxis(input.getValue());
}

JoystickYAxisOutput::JoystickYAxisOutput(Joystick_ &joystick, GenericSignalInput<uint32_t> &input) : JoystickOutput(joystick), input(input) {
    joystick.setYAxisRange(ADC_MIN_VALUE, ADC_MAX_VALUE);
}

void JoystickYAxisOutput::update() {
    joystick.setYAxis(input.getValue());
}

JoystickZAxisOutput::JoystickZAxisOutput(Joystick_ &joystick, GenericSignalInput<uint32_t> &input) : JoystickOutput(joystick), input(input) {
    joystick.setZAxisRange(ADC_MIN_VALUE, ADC_MAX_VALUE);
}

void JoystickZAxisOutput::update() {
    joystick.setZAxis(input.getValue());
}