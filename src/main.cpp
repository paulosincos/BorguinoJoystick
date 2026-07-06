#include <Arduino.h>
#include <Bounce2.h>
#include <Joystick.h>

#include "PinInput.h"
#include "JoystickOutput.h"

// Initializes the Joystick
Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 
                   1, 1,          // Total buttons, Total Hat Switches
                   true, true, false,      // X Axis, Y Axis, Z Axis
                   true, true, false,      // Rx, Ry, Rz
                   false, false,           // Rudder, Throttle
                   false, false, false);   // Accelerator, Brake, Steering


DigitalPinInput pinD2Input(2);
AnalogPinInput analogInput(A0);
SignalInput* inputs[] = {&pinD2Input, &analogInput};

JoystickButtonOutput joystickButtonOutput(joystick, 0, pinD2Input);
SignalOutput* outputs[] = {&joystickButtonOutput};

void setup() {
  joystick.begin();
}

void loop() {
  for (SignalInput* input : inputs) {
    input->update();
  }

  for (SignalOutput* output : outputs) {
    output->update();
  }

  delay(10);
}