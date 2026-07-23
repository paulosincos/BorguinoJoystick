#include "transformers/InvertAnalogTransform.h"

namespace borguino::transformers {

InvertAnalogTransform::InvertAnalogTransform(RangedValueProvider<uint32_t> &input)
    : input(input) {
  rangeMin = input.minValue();
  rangeMax = input.maxValue();
  if (rangeMax < rangeMin) {
    const uint32_t tmp = rangeMin;
    rangeMin = rangeMax;
    rangeMax = tmp;
  }
}

uint32_t InvertAnalogTransform::getValue() const {
  const uint32_t value = input.getValue();
  if (value <= rangeMin) {
    return rangeMax;
  }
  if (value >= rangeMax) {
    return rangeMin;
  }
  return rangeMin + (rangeMax - value);
}

uint32_t InvertAnalogTransform::minValue() const {
  return rangeMin;
}

uint32_t InvertAnalogTransform::maxValue() const {
  return rangeMax;
}

}  // namespace borguino::transformers
