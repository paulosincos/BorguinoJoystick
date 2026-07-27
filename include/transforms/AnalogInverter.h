#ifndef BORGUINO_TRANSFORMS_ANALOG_INVERTER_H
#define BORGUINO_TRANSFORMS_ANALOG_INVERTER_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transforms {

class AnalogInverter : public RangedValueProvider<uint32_t> {
public:
  explicit AnalogInverter(RangedValueProvider<uint32_t> &input);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  RangedValueProvider<uint32_t> &input;
  uint32_t rangeMin = 0;
  uint32_t rangeMax = 0;
};

}  // namespace borguino::transforms

#endif
