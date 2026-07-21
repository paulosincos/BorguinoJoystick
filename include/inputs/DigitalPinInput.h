#ifndef BORGUINO_INPUTS_DIGITAL_PIN_INPUT_H
#define BORGUINO_INPUTS_DIGITAL_PIN_INPUT_H

#include <cstdint>
#include <Bounce2.h>

#include "SignalInput.h"
#include "ValueProvider.h"

namespace borguino::inputs {

class DigitalPinInput : public SignalInput, public ValueProvider<bool> {
public:
  explicit DigitalPinInput(uint8_t pin);

  bool getValue() const override;
  void update() override;

protected:
  uint8_t pin;
  Bounce debouncer;
};

}  // namespace borguino::inputs

#endif