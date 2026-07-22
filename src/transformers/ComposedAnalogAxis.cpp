#include "transformers/ComposedAnalogAxis.h"

namespace borguino::transformers {

namespace {

uint32_t rangeSpan(uint32_t min, uint32_t max) {
  return (max >= min) ? (max - min) : 0;
}

uint32_t normalizedValue(uint32_t value, uint32_t min, uint32_t span) {
  if (value <= min) {
    return 0;
  }

  const uint32_t shifted = value - min;
  return (shifted <= span) ? shifted : span;
}

uint32_t saturatingSum(uint32_t a, uint32_t b) {
  const uint64_t sum = static_cast<uint64_t>(a) + static_cast<uint64_t>(b);
  return (sum > UINT32_MAX) ? UINT32_MAX : static_cast<uint32_t>(sum);
}

}  // namespace

ComposedAnalogAxis::ComposedAnalogAxis(RangedValueProvider<uint32_t> &rangeAInput, RangedValueProvider<uint32_t> &rangeBInput)
    : rangeAInput(rangeAInput), rangeBInput(rangeBInput) {
  rangeAMin = this->rangeAInput.minValue();
  rangeBMin = this->rangeBInput.minValue();

  const uint32_t rangeAMax = this->rangeAInput.maxValue();
  const uint32_t rangeBMax = this->rangeBInput.maxValue();

  rangeASpan = rangeSpan(rangeAMin, rangeAMax);
  rangeBSpan = rangeSpan(rangeBMin, rangeBMax);

  axisCenterValue = rangeASpan;
  axisMaxValue = saturatingSum(rangeASpan, rangeBSpan);
}

uint32_t ComposedAnalogAxis::getValue() const {
  const int64_t center = static_cast<int64_t>(axisCenterValue);
  const int64_t normalizedA = static_cast<int64_t>(normalizedValue(rangeAInput.getValue(), rangeAMin, rangeASpan));
  const int64_t normalizedB = static_cast<int64_t>(normalizedValue(rangeBInput.getValue(), rangeBMin, rangeBSpan));

  // A before B: A pushes to lower values, B pushes to higher values.
  int64_t composed = center + normalizedB - normalizedA;
  if (composed < 0) {
    composed = 0;
  } else if (composed > static_cast<int64_t>(axisMaxValue)) {
    composed = static_cast<int64_t>(axisMaxValue);
  }

  return static_cast<uint32_t>(composed);
}

uint32_t ComposedAnalogAxis::minValue() const {
  return 0;
}

uint32_t ComposedAnalogAxis::maxValue() const {
  return axisMaxValue;
}

}  // namespace borguino::transformers
