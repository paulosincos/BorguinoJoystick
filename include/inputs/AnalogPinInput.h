#ifndef BORGUINO_INPUTS_ANALOG_PIN_INPUT_H
#define BORGUINO_INPUTS_ANALOG_PIN_INPUT_H

#include <cstddef>
#include <cstdint>

#include "AdcSpecs.h"
#include "SignalInput.h"
#include "ValueProvider.h"

namespace borguino::inputs {

class AnalogPinInput : public SignalInput, public RangedValueProvider<uint32_t> {
public:
  explicit AnalogPinInput(uint8_t pin,
                          bool filterValue = false,
                          uint32_t hysteresisThreshold = 4,
                          uint32_t medianAvgThreshold = 16,
                          uint8_t deadzonePercentage = 0,
                          uint8_t centerPercentage = 50,
                          bool normalizeOutsideDeadzone = true);

  uint32_t getValue() const override;
  void update() override;

  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  uint8_t pin;

  bool filterValue;
  static constexpr size_t SAMPLE_BUFFER_SIZE = 7;
  uint32_t hysteresisThreshold = 4;
  uint32_t medianAvgThreshold = 16;
  uint8_t deadzonePercentage = 0;
  uint32_t centerValue = ADC_CENTER_VALUE;
  uint32_t deadzoneLowerBound = ADC_CENTER_VALUE;
  uint32_t deadzoneUpperBound = ADC_CENTER_VALUE;
  bool normalizeOutsideDeadzone = true;

  uint16_t samples[SAMPLE_BUFFER_SIZE];
  size_t sampleCount = 0;
  size_t sampleIndex = 0;
  uint32_t sampleSum = 0;
  uint32_t filteredValue = ADC_CENTER_VALUE;

  void initFilteredValue();
  void updateFilteredValue();
  void pushSampleToWindow(uint16_t sample);
  uint32_t computeMovingAverage() const;
  uint32_t computeMedianFromWindow() const;
  uint32_t selectRobustTarget(uint32_t average, uint32_t median) const;
  void initDeadzoneBounds(uint8_t centerPercentage);
  uint32_t applyDeadzone(uint32_t value) const;
  uint32_t applyHysteresisStep(uint32_t current, uint32_t target) const;
};

}  // namespace borguino::inputs

#endif