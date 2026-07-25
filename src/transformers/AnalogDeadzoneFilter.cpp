#include "transformers/AnalogDeadzoneFilter.h"

namespace {

uint32_t mapRange(uint32_t value, uint32_t inMin, uint32_t inMax,
                  uint32_t outMin, uint32_t outMax) {
  if (inMax <= inMin) {
    return outMin;
  }

  const uint64_t inSpan = static_cast<uint64_t>(inMax) - static_cast<uint64_t>(inMin);
  const uint64_t outSpan = static_cast<uint64_t>(outMax) - static_cast<uint64_t>(outMin);
  const uint64_t scaled = static_cast<uint64_t>(value - inMin) * outSpan;
  return static_cast<uint32_t>(static_cast<uint64_t>(outMin) + (scaled / inSpan));
}

}  // namespace

namespace borguino::transformers {

AnalogDeadzoneFilter::AnalogDeadzoneFilter(RangedValueProvider<uint32_t> &input,
                                           uint8_t deadzonePercentage,
                                           uint8_t centerPercentage,
                                           bool normalizeOutsideDeadzone)
    : input(input), normalizeOutsideDeadzone(normalizeOutsideDeadzone) {
  if (deadzonePercentage > 100) {
    deadzonePercentage = 100;
  }
  if (centerPercentage > 100) {
    centerPercentage = 100;
  }

  rangeMin = input.minValue();
  rangeMax = input.maxValue();
  if (rangeMax < rangeMin) {
    const uint32_t tmp = rangeMin;
    rangeMin = rangeMax;
    rangeMax = tmp;
  }

  const uint32_t span = rangeMax - rangeMin;
  centerValue = rangeMin + static_cast<uint32_t>((static_cast<uint64_t>(span) * centerPercentage) / 100);

  // deadzonePercentage is the total deadzone width relative to the full range.
  const uint32_t deadzoneRadius = static_cast<uint32_t>((static_cast<uint64_t>(span) * deadzonePercentage) / 200);
  deadzoneLowerBound = (centerValue > deadzoneRadius) ? (centerValue - deadzoneRadius) : rangeMin;

  const uint64_t upper64 = static_cast<uint64_t>(centerValue) + static_cast<uint64_t>(deadzoneRadius);
  deadzoneUpperBound = (upper64 > rangeMax) ? rangeMax : static_cast<uint32_t>(upper64);

  if (deadzoneLowerBound < rangeMin) {
    deadzoneLowerBound = rangeMin;
  }
  if (deadzoneUpperBound > rangeMax) {
    deadzoneUpperBound = rangeMax;
  }
}

uint32_t AnalogDeadzoneFilter::getValue() const {
  uint32_t value = input.getValue();
  if (value < rangeMin) {
    value = rangeMin;
  }
  if (value > rangeMax) {
    value = rangeMax;
  }

  if (value >= deadzoneLowerBound && value <= deadzoneUpperBound) {
    return centerValue;
  }

  if (!normalizeOutsideDeadzone) {
    return value;
  }

  if (value < deadzoneLowerBound) {
    return mapRange(value, rangeMin, deadzoneLowerBound, rangeMin, centerValue);
  }

  return mapRange(value, deadzoneUpperBound, rangeMax, centerValue, rangeMax);
}

uint32_t AnalogDeadzoneFilter::minValue() const {
  return rangeMin;
}

uint32_t AnalogDeadzoneFilter::maxValue() const {
  return rangeMax;
}

}  // namespace borguino::transformers