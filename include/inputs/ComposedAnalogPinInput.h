#ifndef BORGUINO_INPUTS_COMPOSED_ANALOG_PIN_INPUT_H
#define BORGUINO_INPUTS_COMPOSED_ANALOG_PIN_INPUT_H

#include <cstdint>

#include "AnalogPinInput.h"
#include "ValueProvider.h"

namespace borguino::inputs {

class ComposedAnalogPinInput : public RangedValueProvider<uint32_t> {
public:
  ComposedAnalogPinInput(AnalogPinInput &negativeInput, AnalogPinInput &positiveInput);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  AnalogPinInput &negativeInput;
  AnalogPinInput &positiveInput;
};

}  // namespace borguino::inputs

#endif