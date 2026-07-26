#ifndef BORGUINO_OUTPUTS_KEYBOARD_OUTPUT_H
#define BORGUINO_OUTPUTS_KEYBOARD_OUTPUT_H

#include <cstdint>

#include <Keyboard.h>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

/**
 * @brief Output that sends a keyboard key press when the input value is true.
 */
class KeyboardOutput : public SignalOutput {
public:
  /**
   * @brief Construct a new KeyboardOutput object
   * @param input The ValueProvider<bool> that provides the input value
   * @param key The key to send when the input value is true
   */
  explicit KeyboardOutput(ValueProvider<bool> &input, uint8_t key);

  /**
   * @brief Update the state of the keyboard output
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the output.
   */
  void update() override;

protected:
  void setValue(bool value);

  ValueProvider<bool> &input;
  uint8_t key;
  bool lastValue = false;
};

}  // namespace borguino::outputs

#endif
