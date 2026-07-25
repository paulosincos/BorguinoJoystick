#ifndef BORGUINO_OUTPUTS_JOYSTICK_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_OUTPUT_H

#include <Joystick.h>

#include "SignalOutput.h"

namespace borguino::outputs {

/**
 * @brief A base class that represents a joystick output.
 *
 * This class provides an interface for sending signals to a joystick device.
 */
class JoystickOutput : public SignalOutput {
public:
  explicit JoystickOutput(Joystick_ &joystick) : joystick(joystick) {}

protected:
  Joystick_ &joystick;
};

}  // namespace borguino::outputs

#endif