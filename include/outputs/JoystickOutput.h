#ifndef BORGUINO_OUTPUTS_JOYSTICK_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_OUTPUT_H

#include <Joystick.h>

#include "SignalOutput.h"

namespace borguino::outputs {

class JoystickOutput : public SignalOutput {
public:
  explicit JoystickOutput(Joystick_ &joystick) : joystick(joystick) {}

protected:
  Joystick_ &joystick;
};

}  // namespace borguino::outputs

#endif