#include "transforms/AnalogToDigitalConverter.h"

#include <algorithm>

namespace borguino::transforms {

namespace {

uint8_t clampPercentage(uint8_t percentage) {
  return (percentage > 100) ? 100 : percentage;
}

uint32_t scaleRangeValue(uint32_t minValue, uint32_t maxValue, uint8_t percentage) {
  const uint32_t span = (maxValue >= minValue) ? (maxValue - minValue) : 0;
  return minValue + static_cast<uint32_t>((static_cast<uint64_t>(span) * clampPercentage(percentage)) / 100);
}

uint32_t scaleOffset(uint32_t minValue, uint32_t maxValue, uint8_t percentage) {
  const uint32_t span = (maxValue >= minValue) ? (maxValue - minValue) : 0;
  return static_cast<uint32_t>((static_cast<uint64_t>(span) * clampPercentage(percentage)) / 100);
}

uint32_t addSaturated(uint32_t value, uint32_t offset, uint32_t maximum) {
  const uint64_t result = static_cast<uint64_t>(value) + static_cast<uint64_t>(offset);
  return (result > maximum) ? maximum : static_cast<uint32_t>(result);
}

uint32_t subtractSaturated(uint32_t value, uint32_t offset, uint32_t minimum) {
  return (value > offset) ? (value - offset) : minimum;
}

}  // namespace

// [Vibe-Coded]
AnalogToDigitalConverter::AnalogToDigitalConverter(RangedValueProvider<uint32_t> &input,
                                                   uint8_t trueRangeStartPercentage,
                                                   uint8_t trueRangeEndPercentage,
                                                   uint8_t hysteresisPercentage)
    : input(input),
      trueRangeStartValue(scaleRangeValue(this->input.minValue(), this->input.maxValue(), trueRangeStartPercentage)),
      trueRangeEndValue(scaleRangeValue(this->input.minValue(), this->input.maxValue(), trueRangeEndPercentage)),
      hysteresisOffset(scaleOffset(this->input.minValue(), this->input.maxValue(), hysteresisPercentage)) {
  const uint32_t minimum = this->input.minValue();
  const uint32_t maximum = this->input.maxValue();

  if (trueRangeStartValue > trueRangeEndValue) {
    std::swap(trueRangeStartValue, trueRangeEndValue);
  }

  startOnThreshold = addSaturated(trueRangeStartValue, hysteresisOffset, maximum);
  endOnThreshold = subtractSaturated(trueRangeEndValue, hysteresisOffset, minimum);
  startOffThreshold = subtractSaturated(trueRangeStartValue, hysteresisOffset, minimum);
  endOffThreshold = addSaturated(trueRangeEndValue, hysteresisOffset, maximum);

  const uint32_t value = this->input.getValue();
  state = value >= startOnThreshold && value <= endOnThreshold;
}

bool AnalogToDigitalConverter::getValue() const {
  const uint32_t value = input.getValue();

  if (state) {
    if (value < startOffThreshold || value > endOffThreshold) {
      state = false;
    }
    return state;
  }

  if (value >= startOnThreshold && value <= endOnThreshold) {
    state = true;
  }

  return state;
}

}  // namespace borguino::transforms
