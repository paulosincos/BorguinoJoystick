#ifndef BORGUINO_OUTPUTS_JOYSTICK_BUTTON_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_BUTTON_OUTPUT_H

#include <cstdint>

#include "outputs/JoystickOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

/**
 * @brief Output that sends a joystick button press when the input value is true.
 */
class JoystickButtonOutput : public JoystickOutput {
public:
  /**
   * @brief Construct a new JoystickButtonOutput object
   * @param joystick The Joystick_ instance to send the output to
   * @param buttonNumber The button number to send when the input value is true
   * @param input The ValueProvider<bool> that provides the input value
   */
  explicit JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, ValueProvider<bool> &input);

  /**
   * @brief Update the state of the joystick button output
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the output.
   */
  void update() override;

protected:
  void setValue(bool value);
  
  uint8_t buttonNumber;
  ValueProvider<bool> &input;
  bool lastValue = false;
};

}  // namespace borguino::outputs

#endif