#ifndef BORGUINO_TRANSFORMERS_COMPOSED_ANALOG_AXIS_H
#define BORGUINO_TRANSFORMERS_COMPOSED_ANALOG_AXIS_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transformers {

class ComposedAnalogAxis : public RangedValueProvider<uint32_t> {
public:
  ComposedAnalogAxis(RangedValueProvider<uint32_t> &rangeAInput, RangedValueProvider<uint32_t> &rangeBInput);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  RangedValueProvider<uint32_t> &rangeAInput;
  RangedValueProvider<uint32_t> &rangeBInput;

  uint32_t rangeAMin = 0;
  uint32_t rangeBMin = 0;
  uint32_t rangeASpan = 0;
  uint32_t rangeBSpan = 0;
  uint32_t axisMaxValue = 0;
  uint32_t axisCenterValue = 0;
};

}  // namespace borguino::transformers

#endif
