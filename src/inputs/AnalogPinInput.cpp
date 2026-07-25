#include <Arduino.h>

#include "inputs/AnalogPinInput.h"

namespace borguino::inputs {

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

AnalogPinInput::AnalogPinInput(uint8_t pin,
                               bool filterValue,
                               uint32_t hysteresisThreshold,
                               uint32_t medianAvgThreshold,
                               uint8_t deadzonePercentage,
                               uint8_t centerPercentage,
                               bool normalizeOutsideDeadzone)
    : pin(pin),
      filterValue(filterValue),
      hysteresisThreshold(hysteresisThreshold),
      medianAvgThreshold(medianAvgThreshold),
      deadzonePercentage(deadzonePercentage > 100 ? 100 : deadzonePercentage),
      normalizeOutsideDeadzone(normalizeOutsideDeadzone) {
  initDeadzoneBounds(centerPercentage);

  if (filterValue) {
    initFilteredValue();
  }
}

uint32_t AnalogPinInput::getValue() const {
  if (!filterValue) {
    return analogRead(pin);
  }
  return filteredValue;
}

uint32_t AnalogPinInput::minValue() const {
  return ADC_MIN_VALUE;
}

uint32_t AnalogPinInput::maxValue() const {
  return ADC_MAX_VALUE;
}

void AnalogPinInput::update() {
  if (filterValue) {
    updateFilteredValue();
  }
}

void AnalogPinInput::initFilteredValue() {
  for (size_t i = 0; i < SAMPLE_BUFFER_SIZE; ++i) {
    samples[i] = ADC_CENTER_VALUE;
  }
  sampleCount = 0;
  sampleIndex = 0;
  sampleSum = 0;
  filteredValue = ADC_CENTER_VALUE;
}

void AnalogPinInput::pushSampleToWindow(uint16_t sample) {
  if (sampleCount < SAMPLE_BUFFER_SIZE) {
    ++sampleCount;
  } else {
    sampleSum -= samples[sampleIndex];
  }

  samples[sampleIndex] = sample;
  sampleSum += sample;
  sampleIndex = (sampleIndex + 1) % SAMPLE_BUFFER_SIZE;
}

// [Vibe-Coded]
uint32_t AnalogPinInput::computeMovingAverage() const {
  if (sampleCount == 0) {
    return ADC_CENTER_VALUE;
  }
  return sampleSum / sampleCount;
}

// [Vibe-Coded]
uint32_t AnalogPinInput::computeMedianFromWindow() const {
  if (sampleCount == 0) {
    return ADC_CENTER_VALUE;
  }

  uint16_t sorted[SAMPLE_BUFFER_SIZE] = {};
  const size_t sortCount = sampleCount;
  for (size_t i = 0; i < sortCount; ++i) {
    sorted[i] = samples[i];
  }

  for (size_t i = 0; i + 1 < sortCount; ++i) {
    for (size_t j = 0; j + 1 < sortCount - i; ++j) {
      if (sorted[j] > sorted[j + 1]) {
        const uint16_t tmp = sorted[j];
        sorted[j] = sorted[j + 1];
        sorted[j + 1] = tmp;
      }
    }
  }

  uint32_t median = sorted[sortCount / 2];
  if ((sortCount % 2) == 0 && sortCount > 1) {
    median = (uint32_t(sorted[sortCount / 2 - 1]) + uint32_t(sorted[sortCount / 2])) / 2;
  }

  return median;
}

// [Vibe-Coded]
uint32_t AnalogPinInput::selectRobustTarget(uint32_t average, uint32_t median) const {
  uint32_t targetValue = median;
  const uint32_t avgMedianDistance = (average > median) ? (average - median) : (median - average);
  if (avgMedianDistance <= medianAvgThreshold) {
    targetValue = (average + median) / 2;
  }
  return targetValue;
}

void AnalogPinInput::initDeadzoneBounds(uint8_t centerPercentage) {
  if (centerPercentage > 100) {
    centerPercentage = 100;
  }

  const uint32_t rangeMin = ADC_MIN_VALUE;
  const uint32_t rangeMax = ADC_MAX_VALUE;
  const uint32_t span = rangeMax - rangeMin;
  centerValue = rangeMin + static_cast<uint32_t>((static_cast<uint64_t>(span) * centerPercentage) / 100);

  const uint32_t deadzoneRadius = static_cast<uint32_t>((static_cast<uint64_t>(span) * deadzonePercentage) / 200);
  deadzoneLowerBound = (centerValue > deadzoneRadius) ? (centerValue - deadzoneRadius) : rangeMin;

  const uint64_t upper64 = static_cast<uint64_t>(centerValue) + static_cast<uint64_t>(deadzoneRadius);
  deadzoneUpperBound = (upper64 > rangeMax) ? rangeMax : static_cast<uint32_t>(upper64);
}

uint32_t AnalogPinInput::applyDeadzone(uint32_t value) const {
  if (deadzonePercentage == 0) {
    return value;
  }

  uint32_t clamped = value;
  if (clamped < ADC_MIN_VALUE) {
    clamped = ADC_MIN_VALUE;
  }
  if (clamped > ADC_MAX_VALUE) {
    clamped = ADC_MAX_VALUE;
  }

  if (clamped >= deadzoneLowerBound && clamped <= deadzoneUpperBound) {
    return centerValue;
  }

  if (!normalizeOutsideDeadzone) {
    return clamped;
  }

  if (clamped < deadzoneLowerBound) {
    return mapRange(clamped, ADC_MIN_VALUE, deadzoneLowerBound, ADC_MIN_VALUE, centerValue);
  }

  return mapRange(clamped, deadzoneUpperBound, ADC_MAX_VALUE, centerValue, ADC_MAX_VALUE);
}

// [Vibe-Coded]
uint32_t AnalogPinInput::applyHysteresisStep(uint32_t current, uint32_t target) const {
  if (hysteresisThreshold == 0) {
    return target;
  }

  if (current == ADC_CENTER_VALUE) {
    return target;
  }

  const int32_t delta = int32_t(target) - int32_t(current);
  if (delta > int32_t(hysteresisThreshold)) {
    return current + hysteresisThreshold;
  }
  if (delta < -int32_t(hysteresisThreshold)) {
    return current - hysteresisThreshold;
  }

  return current;
}

void AnalogPinInput::updateFilteredValue() {
  // 1) Acquire raw sample and update the sliding window state.
  const uint16_t rawValue = analogRead(pin);
  pushSampleToWindow(rawValue);

  // 2) Combine average and median into a robust target estimate.
  const uint32_t average = computeMovingAverage();
  const uint32_t median = computeMedianFromWindow();
  const uint32_t targetValue = selectRobustTarget(average, median);
  const uint32_t deadzonedTargetValue = applyDeadzone(targetValue);

  // 3) Apply deadzone and dynamic smoothing.
  filteredValue = applyHysteresisStep(filteredValue, deadzonedTargetValue);
}

}  // namespace borguino::inputs
