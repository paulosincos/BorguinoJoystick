#include "transformers/AnalogToDigitalTransform.h"

namespace borguino::transformers {

AnalogToDigitalTransform::AnalogToDigitalTransform(RangedValueProvider<uint32_t> &input,
                                                   uint8_t thresholdPercentage,
                                                   uint8_t hysteresisPercentage)
    : input(input) {
  if (thresholdPercentage > 100) {
    thresholdPercentage = 100;
  }
  if (hysteresisPercentage > 100) {
    hysteresisPercentage = 100;
  }

  minValue = this->input.minValue();
  maxValue = this->input.maxValue();
  const uint32_t span = (maxValue >= minValue) ? (maxValue - minValue) : 0;

  switchValue = minValue + static_cast<uint32_t>((static_cast<uint64_t>(span) * thresholdPercentage) / 100);
  hysteresisOffset = static_cast<uint32_t>((static_cast<uint64_t>(span) * hysteresisPercentage) / 100);
}

// [Vibe-Coded]
bool AnalogToDigitalTransform::getValue() const {
  const uint32_t value = input.getValue();

  if (!stateInitialized) {
    state = value >= switchValue;
    stateInitialized = true;
    return state;
  }

  if (state) {
    const uint32_t turnOffThreshold = (switchValue > hysteresisOffset) ? (switchValue - hysteresisOffset) : minValue;
    if (value < turnOffThreshold) {
      state = false;
    }
    return state;
  }

  const uint64_t onThreshold64 = static_cast<uint64_t>(switchValue) + static_cast<uint64_t>(hysteresisOffset);
  const uint32_t turnOnThreshold = (onThreshold64 > maxValue) ? maxValue : static_cast<uint32_t>(onThreshold64);
  if (value > turnOnThreshold) {
    state = true;
  }

  return state;
}

}  // namespace borguino::transformers
