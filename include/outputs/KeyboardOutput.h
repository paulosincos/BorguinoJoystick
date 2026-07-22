#ifndef BORGUINO_OUTPUTS_KEYBOARD_OUTPUT_H
#define BORGUINO_OUTPUTS_KEYBOARD_OUTPUT_H

#include <cstdint>

#include <Keyboard.h>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

class KeyboardOutput : public SignalOutput {
public:
  explicit KeyboardOutput(ValueProvider<bool> &input, uint8_t key);

  void update() override;

protected:
  void setValue(bool value);

  ValueProvider<bool> &input;
  uint8_t key;
  bool lastValue = false;
};

}  // namespace borguino::outputs

#endif
