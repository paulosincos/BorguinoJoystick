#ifndef BORGUINO_INPUTS_DIGITAL_PIN_INPUT_H
#define BORGUINO_INPUTS_DIGITAL_PIN_INPUT_H

#include <cstdint>
#include <Arduino.h>
#include <Bounce2.h>

#include "SignalInput.h"
#include "ValueProvider.h"

namespace borguino::inputs {

class DigitalPinInput : public SignalInput, public ValueProvider<bool> {
public:
  explicit DigitalPinInput(uint8_t pin, int mode = INPUT_PULLUP);

  bool getValue() const override;
  void update() override;

protected:
  uint8_t pin;
  Bounce debouncer;
};

}  // namespace borguino::inputs

#endif