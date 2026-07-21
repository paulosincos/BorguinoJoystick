#include <Arduino.h>
#include <Bounce2.h>
#include <Joystick.h>

#include "inputs/AllInputs.h"
#include "outputs/AllOutputs.h"

namespace borg_inputs = borguino::inputs;
namespace borg_outputs = borguino::outputs;

// Initializes the Joystick
Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 
                   1, 1,          // Total buttons, Total Hat Switches
                   true, true, true,      // X Axis, Y Axis, Z Axis
                   false, false, false,      // Rx, Ry, Rz
                   false, false,           // Rudder, Throttle
                   false, false, false);   // Accelerator, Brake, Steering

borg_inputs::DigitalPinInput pinD2Input(2);
borg_inputs::DigitalPinInput hatInput0(3);
borg_inputs::DigitalPinInput hatInput1(4);
borg_inputs::DigitalPinInput hatInput2(5);
borg_inputs::DigitalPinInput hatInput3(6);
borg_inputs::AnalogPinInput pinA0Input(A0);
borg_inputs::AnalogPinInput pinA1Input(A1);
borg_inputs::AnalogPinInput pinA2Input(A2);
borg_inputs::AnalogPinInput pinA3Input(A3);
SignalInput* inputs[] = {&pinD2Input, &hatInput0, &hatInput1, &hatInput2, &hatInput3, &pinA0Input, &pinA1Input, &pinA2Input, &pinA3Input};

ValueProvider<bool>* hatInputs[] = {&hatInput0, &hatInput1, &hatInput2, &hatInput3};

borg_inputs::ComposedAnalogPinInput pinA2A3Input(pinA2Input, pinA3Input);

borg_outputs::JoystickButtonOutput joystickButtonOutput(joystick, 0, pinD2Input);
borg_outputs::JoystickHatOutput joystickHatOutput(joystick, 0, hatInputs, 4, true);
borg_outputs::JoystickRangedOutput joystickXAxisOutput(joystick, borg_outputs::XAxis, pinA0Input);
borg_outputs::JoystickRangedOutput joystickYAxisOutput(joystick, borg_outputs::YAxis, pinA1Input);
borg_outputs::JoystickRangedOutput joystickZAxisOutput(joystick, borg_outputs::ZAxis, pinA2A3Input);
SignalOutput* outputs[] = {&joystickButtonOutput, &joystickHatOutput, &joystickXAxisOutput, &joystickYAxisOutput, &joystickZAxisOutput};

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