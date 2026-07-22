#ifndef BORGUINO_OUTPUTS_MOUSE_BUTTON_OUTPUT_H
#define BORGUINO_OUTPUTS_MOUSE_BUTTON_OUTPUT_H

#include <cstdint>

#include <Mouse.h>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

class MouseButtonOutput : public SignalOutput {
public:
  explicit MouseButtonOutput(ValueProvider<bool> &input, uint8_t button = MOUSE_LEFT);

  void update() override;

protected:
  void setValue(bool value);

  ValueProvider<bool> &input;
  uint8_t button;
  bool lastValue = false;
};

}  // namespace borguino::outputs

#endif
