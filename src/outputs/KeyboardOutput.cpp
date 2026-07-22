#include "outputs/KeyboardOutput.h"

namespace borguino::outputs {

KeyboardOutput::KeyboardOutput(ValueProvider<bool> &input, uint8_t key)
    : input(input), key(key) {
}

void KeyboardOutput::update() {
  const bool value = input.getValue();
  if (value == lastValue) {
    return;
  }

  setValue(value);
  lastValue = value;
}

void KeyboardOutput::setValue(bool value) {
  if (value) {
    Keyboard.press(key);
    return;
  }

  Keyboard.release(key);
}

}  // namespace borguino::outputs
