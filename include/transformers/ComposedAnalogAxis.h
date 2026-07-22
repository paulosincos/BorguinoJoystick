#ifndef BORGUINO_TRANSFORMERS_COMPOSED_ANALOG_AXIS_H
#define BORGUINO_TRANSFORMERS_COMPOSED_ANALOG_AXIS_H

#include <cstdint>

#include "inputs/AnalogPinInput.h"
#include "ValueProvider.h"

namespace borguino::transformers {

class ComposedAnalogAxis : public RangedValueProvider<uint32_t> {
public:
  ComposedAnalogAxis(inputs::AnalogPinInput &firstInput, inputs::AnalogPinInput &secondInput);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  inputs::AnalogPinInput &firstInput;
  inputs::AnalogPinInput &secondInput;
};

}  // namespace borguino::transformers

#endif
