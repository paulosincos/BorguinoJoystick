#ifndef BORGUINO_OUTPUTS_MOUSE_BUTTON_OUTPUT_H
#define BORGUINO_OUTPUTS_MOUSE_BUTTON_OUTPUT_H

#include <cstdint>

#include <Mouse.h>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

/**
 * @brief Output that sends a mouse button press when the input value is true.
 */
class MouseButtonOutput : public SignalOutput {
public:
  /**
   * @brief Construct a new MouseButtonOutput object
   * @param input The ValueProvider<bool> that provides the input value
   * @param button The mouse button to send when the input value is true (default: MOUSE_LEFT)
   */
  explicit MouseButtonOutput(ValueProvider<bool> &input, uint8_t button = MOUSE_LEFT);

  /**
   * @brief Update the state of the mouse button output
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the output.
   */
  void update() override;

protected:
  void setValue(bool value);

  ValueProvider<bool> &input;
  uint8_t button;
  bool lastValue = false;
};

}  // namespace borguino::outputs

#endif
