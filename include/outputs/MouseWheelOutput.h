#ifndef BORGUINO_OUTPUTS_MOUSE_WHEEL_OUTPUT_H
#define BORGUINO_OUTPUTS_MOUSE_WHEEL_OUTPUT_H

#include <cstdint>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

/**
 * @brief Output that sends mouse wheel movement based on the input value.
 */
class MouseWheelOutput : public SignalOutput {
public:
  /**
   * @brief Construct a new MouseWheelOutput object
   * @param input The RangedValueProvider<uint32_t> that provides the input value
   * @param deadzone The deadzone threshold for input values (default: 24)
   * @param divisor The divisor to scale the input values (default: 192)
   * @param invertDirection Whether to invert the wheel direction (default: false)
   */
  explicit MouseWheelOutput(RangedValueProvider<uint32_t> &input,
                            uint16_t deadzone = 24,
                            uint16_t divisor = 192,
                            bool invertDirection = false);

  /**
   * @brief Update the state of the mouse wheel output
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the output.
   */
  void update() override;

protected:
  static int8_t toRelativeDelta(const RangedValueProvider<uint32_t> &input,
                                uint32_t rawValue,
                                uint16_t deadzone,
                                uint16_t divisor);

  RangedValueProvider<uint32_t> &input;
  uint16_t deadzone;
  uint16_t divisor;
  bool invertDirection;
};

}  // namespace borguino::outputs

#endif
