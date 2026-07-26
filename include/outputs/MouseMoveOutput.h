#ifndef BORGUINO_OUTPUTS_MOUSE_MOVE_OUTPUT_H
#define BORGUINO_OUTPUTS_MOUSE_MOVE_OUTPUT_H

#include <cstdint>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

/**
 * @brief Output that sends mouse movement based on the input values.
 */
class MouseMoveOutput : public SignalOutput {
public:
  /**
   * @brief Construct a new MouseMoveOutput object
   * @param xInput The RangedValueProvider<uint32_t> that provides the X-axis input value
   * @param yInput The RangedValueProvider<uint32_t> that provides the Y-axis input value
   * @param deadzone The deadzone threshold for input values (default: 24)
   * @param divisor The divisor to scale the input values (default: 128)
   * @param invertY Whether to invert the Y-axis movement (default: true)
   */
  explicit MouseMoveOutput(RangedValueProvider<uint32_t> &xInput,
                           RangedValueProvider<uint32_t> &yInput,
                           uint16_t deadzone = 24,
                           uint16_t divisor = 128,
                           bool invertY = true);

  /**
   * @brief Update the state of the mouse movement output
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

  RangedValueProvider<uint32_t> &xInput;
  RangedValueProvider<uint32_t> &yInput;
  uint16_t deadzone;
  uint16_t divisor;
  bool invertY;
};

}  // namespace borguino::outputs

#endif
