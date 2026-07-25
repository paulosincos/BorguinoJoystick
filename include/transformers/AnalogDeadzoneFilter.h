#ifndef BORGUINO_TRANSFORMERS_ANALOG_DEADZONE_FILTER_H
#define BORGUINO_TRANSFORMERS_ANALOG_DEADZONE_FILTER_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transformers {

class AnalogDeadzoneFilter : public RangedValueProvider<uint32_t> {
public:
  explicit AnalogDeadzoneFilter(RangedValueProvider<uint32_t> &input,
                                uint8_t deadzonePercentage = 4,
                                uint8_t centerPercentage = 50,
                                bool normalizeOutsideDeadzone = true);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  RangedValueProvider<uint32_t> &input;
  uint32_t rangeMin = 0;
  uint32_t rangeMax = 0;
  uint32_t centerValue = 0;
  uint32_t deadzoneLowerBound = 0;
  uint32_t deadzoneUpperBound = 0;
  bool normalizeOutsideDeadzone = true;
};

}  // namespace borguino::transformers

#endif