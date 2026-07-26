#ifndef BORGUINO_OUTPUTS_JOYSTICK_HAT_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_HAT_OUTPUT_H

#include <cstddef>
#include <cstdint>

#include "ValueProvider.h"
#include "outputs/JoystickOutput.h"

namespace borguino::outputs {

/**
 * @brief Output that sends joystick hat values based on the input values.
 */
class JoystickHatOutput : public JoystickOutput {
public:
  /**
   * @brief Construct a new JoystickHatOutput object
   * @param joystick The Joystick_ instance to send the output to
   * @param hatNumber The hat number to send the output to
   * @param inputs An array of ValueProvider<bool> pointers that provide the input values for the hat directions
   * @param inputCount The number of input providers in the inputs array
   * @param combineInputs Whether to combine multiple inputs for the same direction (default: false)
   */
  explicit JoystickHatOutput(Joystick_ &joystick, uint8_t hatNumber, ValueProvider<bool> *const *inputs, size_t inputCount, bool combineInputs);

  /**
   * @brief Update the state of the joystick hat output
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the output.
   */
  void update() override;

protected:
  int16_t getHatDirection() const;
  void setValue(int16_t value);

  static constexpr int16_t HAT_CENTERED = -1;
  uint8_t hatNumber;
  ValueProvider<bool> *const *inputs;
  size_t inputCount;
  bool combineInputs;
  int16_t lastHatDirection = HAT_CENTERED;
};

}  // namespace borguino::outputs

#endif