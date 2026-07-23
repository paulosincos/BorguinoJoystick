#ifndef BORGUINO_TRANSFORMERS_DIGITAL_TO_ANALOG_TRANSFORM_H
#define BORGUINO_TRANSFORMERS_DIGITAL_TO_ANALOG_TRANSFORM_H

#include <cstdint>

#include "AdcSpecs.h"
#include "ValueProvider.h"

namespace borguino::transformers {

class DigitalToAnalogTransform : public RangedValueProvider<uint32_t> {
public:
  explicit DigitalToAnalogTransform(ValueProvider<bool> &input,
                                    uint32_t minValue = ADC_MIN_VALUE,
                                    uint32_t maxValue = ADC_MAX_VALUE,
                                    uint32_t activationTimeMs = 0);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  ValueProvider<bool> &input;
  uint32_t minOutputValue = 0;
  uint32_t maxOutputValue = 0;
  uint32_t outputSpan = 0;
  uint32_t activationTimeMs = 0;

  mutable bool initialized = false;
  mutable bool lastInputState = false;
  mutable uint32_t currentValue = 0;

  mutable uint32_t transitionStartValue = 0;
  mutable uint32_t transitionTargetValue = 0;
  mutable uint32_t transitionStartMs = 0;
  mutable uint32_t transitionDurationMs = 0;
};

}  // namespace borguino::transformers

#endif