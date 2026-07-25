#include "inputs/DigitalPinInput.h"

namespace {
constexpr uint32_t DIGITAL_PIN_DEBOUNCE_INTERVAL_MS = 25U;
}

namespace borguino::inputs {

DigitalPinInput::DigitalPinInput(uint8_t pin, int mode) : pin(pin) {
  debouncer.attach(pin, mode);
  debouncer.interval(DIGITAL_PIN_DEBOUNCE_INTERVAL_MS);
}

bool DigitalPinInput::getValue() const {
  return !debouncer.read();
}

void DigitalPinInput::update() {
  debouncer.update();
}

}  // namespace borguino::inputs