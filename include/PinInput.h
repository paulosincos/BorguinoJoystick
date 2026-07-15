#ifndef PIN_INPUT_H
#define PIN_INPUT_H

#include <cstdint>
#include <Bounce2.h>

#include "AdcSpecs.h"
#include "SignalInput.h"

class DigitalPinInput : public SignalInput, public ValueProvider<bool> {
public:
  explicit DigitalPinInput(uint8_t pin);

  bool getValue() const override;
  void update() override;

  protected:
  uint8_t pin;
  Bounce debouncer;
};

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

class ComposedAnalogPinInput : public RangedValueProvider<uint32_t> {
public:
  ComposedAnalogPinInput(AnalogPinInput &negativeInput, AnalogPinInput &positiveInput);

  uint32_t getValue() const override;
  uint32_t minValue() const override;
  uint32_t maxValue() const override;
protected:
  AnalogPinInput &negativeInput;
  AnalogPinInput &positiveInput;
};
#endif
