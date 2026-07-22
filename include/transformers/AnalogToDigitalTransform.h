#ifndef BORGUINO_TRANSFORMERS_ANALOG_TO_DIGITAL_TRANSFORM_H
#define BORGUINO_TRANSFORMERS_ANALOG_TO_DIGITAL_TRANSFORM_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transformers {

class AnalogToDigitalTransform : public ValueProvider<bool> {
public:
  explicit AnalogToDigitalTransform(RangedValueProvider<uint32_t> &input,
                                    uint8_t thresholdPercentage = 50,
                                    uint8_t hysteresisPercentage = 1);

  bool getValue() const override;

protected:
  RangedValueProvider<uint32_t> &input;
  uint32_t minValue = 0;
  uint32_t maxValue = 0;
  uint32_t switchValue = 0;
  uint32_t hysteresisOffset = 0;
  mutable bool state = false;
  mutable bool stateInitialized = false;
};

}  // namespace borguino::transformers

#endif
