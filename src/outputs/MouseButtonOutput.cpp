#include "outputs/MouseButtonOutput.h"

namespace borguino::outputs {

MouseButtonOutput::MouseButtonOutput(ValueProvider<bool> &input, uint8_t button)
    : input(input), button(button) {
}

void MouseButtonOutput::update() {
  const bool value = input.getValue();
  if (value == lastValue) {
    return;
  }

  setValue(value);
  lastValue = value;
}

void MouseButtonOutput::setValue(bool value) {
  if (value) {
    Mouse.press(button);
    return;
  }

  Mouse.release(button);
}

}  // namespace borguino::outputs
