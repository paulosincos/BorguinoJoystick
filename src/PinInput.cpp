#include <Arduino.h>

#include "AdcSpecs.h"
#include "PinInput.h"

DigitalPinInput::DigitalPinInput(uint8_t pin) : pin(pin) {
  debouncer.attach(pin, INPUT_PULLUP);
  debouncer.interval(25);
}

bool DigitalPinInput::getValue() const {
  return !debouncer.read();
}

void DigitalPinInput::update() {
  debouncer.update();
}

AnalogPinInput::AnalogPinInput(uint8_t pin) : AnalogPinInput(pin, false) {
}

AnalogPinInput::AnalogPinInput(uint8_t pin, bool filterValue) : pin(pin), filterValue(filterValue) {
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
  // TODO: consider using pointer in init function to avoid branching in update() function
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
  sampleSum = ADC_CENTER_VALUE * SAMPLE_BUFFER_SIZE;
  filteredValue = ADC_CENTER_VALUE;
}

void AnalogPinInput::updateFilteredValue() {
  uint16_t rawValue = analogRead(pin);

  if (sampleCount < SAMPLE_BUFFER_SIZE) {
    samples[sampleCount++] = rawValue;
  } else {
    sampleSum -= samples[sampleIndex];
    samples[sampleIndex] = rawValue;
  }

  sampleSum += rawValue;
  sampleIndex = (sampleIndex + 1) % SAMPLE_BUFFER_SIZE;

  uint32_t average = sampleSum / sampleCount;

  uint16_t sorted[SAMPLE_BUFFER_SIZE];
  size_t sortCount = sampleCount;
  for (size_t i = 0; i < sortCount; ++i) {
    sorted[i] = samples[i];
  }
  for (size_t i = 0; i + 1 < sortCount; ++i) {
    for (size_t j = 0; j + 1 < sortCount - i; ++j) {
      if (sorted[j] > sorted[j + 1]) {
        uint16_t tmp = sorted[j];
        sorted[j] = sorted[j + 1];
        sorted[j + 1] = tmp;
      }
    }
  }

  uint32_t median = sorted[sortCount / 2];
  if ((sortCount % 2) == 0 && sortCount > 1) {
    median = (uint32_t(sorted[sortCount / 2 - 1]) + uint32_t(sorted[sortCount / 2])) / 2;
  }

  uint32_t targetValue = (average + median) / 2;

  if (filteredValue == ADC_CENTER_VALUE) {
    filteredValue = targetValue;
  } else {
    int32_t delta = int32_t(targetValue) - int32_t(filteredValue);
    if (delta > int32_t(HYSTERESIS_THRESHOLD)) {
      filteredValue += HYSTERESIS_THRESHOLD;
    } else if (delta < -int32_t(HYSTERESIS_THRESHOLD)) {
      filteredValue -= HYSTERESIS_THRESHOLD;
    }
  }
}

ComposedAnalogPinInput::ComposedAnalogPinInput(AnalogPinInput &negativeInput, AnalogPinInput &positiveInput) : negativeInput(negativeInput), positiveInput(positiveInput) {
}

uint32_t ComposedAnalogPinInput::getValue() const {
  uint32_t negativeValue = -negativeInput.getValue();
  uint32_t positiveValue = positiveInput.getValue();
  return negativeValue + positiveValue;
}

uint32_t ComposedAnalogPinInput::minValue() const {
  return -negativeInput.maxValue();
}

uint32_t ComposedAnalogPinInput::maxValue() const {
  return positiveInput.maxValue();
}