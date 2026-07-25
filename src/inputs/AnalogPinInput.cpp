#include <Arduino.h>

#include "inputs/AnalogPinInput.h"

namespace borguino::inputs {

AnalogPinInput::AnalogPinInput(uint8_t pin,
                               bool filterValue,
                               uint32_t hysteresisThreshold,
                               uint32_t medianAvgThreshold)
    : pin(pin),
      filterValue(filterValue),
      hysteresisThreshold(hysteresisThreshold),
      medianAvgThreshold(medianAvgThreshold) {
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

  // 3) Apply dynamic smoothing.
  filteredValue = applyHysteresisStep(filteredValue, targetValue);
}

}  // namespace borguino::inputs
