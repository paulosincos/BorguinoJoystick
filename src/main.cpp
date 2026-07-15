#include <Arduino.h>
#include <Bounce2.h>
#include <Joystick.h>

#include "PinInput.h"
#include "JoystickOutput.h"

// Initializes the Joystick
Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 
                   1, 0,          // Total buttons, Total Hat Switches
                   true, true, true,      // X Axis, Y Axis, Z Axis
                   false, false, false,      // Rx, Ry, Rz
                   false, false,           // Rudder, Throttle
                   false, false, false);   // Accelerator, Brake, Steering


DigitalPinInput pinD2Input(2);
AnalogPinInput pinA0Input(A0);
AnalogPinInput pinA1Input(A1);
AnalogPinInput pinA2Input(A2);
AnalogPinInput pinA3Input(A3);
SignalInput* inputs[] = {&pinD2Input, &pinA0Input, &pinA1Input, &pinA2Input, &pinA3Input};

ComposedAnalogPinInput pinA2A3Input(pinA2Input, pinA3Input);

JoystickButtonOutput joystickButtonOutput(joystick, 0, pinD2Input);
JoystickRangedOutput joystickXAxisOutput(joystick, XAxis, pinA0Input);
JoystickRangedOutput joystickYAxisOutput(joystick, YAxis, pinA1Input);
JoystickRangedOutput joystickZAxisOutput(joystick, ZAxis, pinA2A3Input);
SignalOutput* outputs[] = {&joystickButtonOutput, &joystickXAxisOutput, &joystickYAxisOutput, &joystickZAxisOutput};

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