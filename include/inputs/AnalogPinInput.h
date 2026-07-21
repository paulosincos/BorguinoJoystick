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
  explicit AnalogPinInput(uint8_t pin);
  explicit AnalogPinInput(uint8_t pin, bool filterValue);

  uint32_t getValue() const override;
  void update() override;

  uint32_t minValue() const override;
  uint32_t maxValue() const override;

protected:
  uint8_t pin;

  bool filterValue;
  static constexpr size_t SAMPLE_BUFFER_SIZE = 7;
  static constexpr uint32_t HYSTERESIS_THRESHOLD = 4;
  static constexpr uint32_t MEDIAN_AVG_THRESHOLD = 16;

  uint16_t samples[SAMPLE_BUFFER_SIZE];
  size_t sampleCount = 0;
  size_t sampleIndex = 0;
  uint32_t sampleSum = 0;
  uint32_t filteredValue = ADC_CENTER_VALUE;

  void initFilteredValue();
  void updateFilteredValue();
};

}  // namespace borguino::inputs

#endif