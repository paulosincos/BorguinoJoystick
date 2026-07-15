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
AnalogPinInput pinA0Input(A0);
AnalogPinInput pinA1Input(A1);
AnalogPinInput pinA2Input(A2);
AnalogPinInput pinA3Input(A3);
UpdatableSignalInput* inputs[] = {&pinD2Input, &pinA0Input, &pinA1Input, &pinA2Input, &pinA3Input};

ComposedAnalogPinInput pinA2A3Input(pinA2Input, pinA3Input);

JoystickButtonOutput joystickButtonOutput(joystick, 0, pinD2Input);
JoystickXAxisOutput joystickXAxisOutput(joystick, pinA0Input);
JoystickYAxisOutput joystickYAxisOutput(joystick, pinA1Input);
JoystickZAxisOutput joystickZAxisOutput(joystick, pinA2A3Input);
SignalOutput* outputs[] = {&joystickButtonOutput, &joystickXAxisOutput, &joystickYAxisOutput, &joystickZAxisOutput};

void setup() {
  joystick.begin();
}

void loop() {
  for (UpdatableSignalInput* input : inputs) {
    input->update();
  }

  for (SignalOutput* output : outputs) {
    output->update();
  }

  delay(10);
}