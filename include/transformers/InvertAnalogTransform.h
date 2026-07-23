#ifndef BORGUINO_TRANSFORMERS_INVERT_ANALOG_TRANSFORM_H
#define BORGUINO_TRANSFORMERS_INVERT_ANALOG_TRANSFORM_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transformers {

class InvertAnalogTransform : public RangedValueProvider<uint32_t> {
public:
  explicit InvertAnalogTransform(RangedValueProvider<uint32_t> &input);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  RangedValueProvider<uint32_t> &input;
  uint32_t rangeMin = 0;
  uint32_t rangeMax = 0;
};

}  // namespace borguino::transformers

#endif
