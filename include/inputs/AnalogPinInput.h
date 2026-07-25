#ifndef BORGUINO_INPUTS_ANALOG_PIN_INPUT_H
#define BORGUINO_INPUTS_ANALOG_PIN_INPUT_H

#include <cstddef>
#include <cstdint>

#include "AdcSpecs.h"
#include "SignalInput.h"
#include "ValueProvider.h"

namespace borguino::inputs {

/**
 * @brief AnalogPinInput represents an analog input pin with optional filtering.
 */
class AnalogPinInput : public SignalInput, public RangedValueProvider<uint32_t> {
public:
  /**
   * @brief FilterOptions struct defines the configuration for filtering analog input values.
   */
  struct FilterOptions {
    explicit FilterOptions(uint32_t hysteresisThreshold = 4,
                           uint32_t medianAvgThreshold = 16,
                           uint8_t deadzonePercentage = 0,
                           uint8_t centerPercentage = 50,
                           bool normalizeOutsideDeadzone = true)
        : hysteresisThreshold(hysteresisThreshold),
          medianAvgThreshold(medianAvgThreshold),
          deadzonePercentage(deadzonePercentage),
          centerPercentage(centerPercentage),
          normalizeOutsideDeadzone(normalizeOutsideDeadzone) {
    }

    uint32_t hysteresisThreshold;
    uint32_t medianAvgThreshold;
    uint8_t deadzonePercentage;
    uint8_t centerPercentage;
    bool normalizeOutsideDeadzone;
  };

  /**
   * @brief Construct a new Analog Pin Input object
   * @param pin The analog pin number
   * @param filterOptions Optional pointer to filter options (default is nullptr/filters disabled)
   */
  explicit AnalogPinInput(uint8_t pin, const FilterOptions *filterOptions = nullptr);

  /**
   * @brief Get the current value of the analog pin
   * @return The current analog value (e.g., 0 to 1023)
   */
  uint32_t getValue() const override;

  /**
   * @brief Update the state of the analog pin input
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the pin.
   */
  void update() override;

  /**
   * @brief Get the minimum possible value of the analog pin
   * @return The minimum analog value (e.g., 0)
   */
  uint32_t minValue() const override;

  /**
   * @brief Get the maximum possible value of the analog pin
   * @return The maximum analog value (e.g., 1023)
   */
  uint32_t maxValue() const override;

protected:
  uint8_t pin;

  bool filterValue = false;
  static constexpr size_t SAMPLE_BUFFER_SIZE = 7;
  FilterOptions filterOptions;
  uint32_t centerValue = ADC_CENTER_VALUE;
  uint32_t deadzoneLowerBound = ADC_CENTER_VALUE;
  uint32_t deadzoneUpperBound = ADC_CENTER_VALUE;

  uint16_t samples[SAMPLE_BUFFER_SIZE];
  size_t sampleCount = 0;
  size_t sampleIndex = 0;
  uint32_t sampleSum = 0;
  uint32_t filteredValue = ADC_CENTER_VALUE;

  void initFilteredMode();
  void updateFilteredValue();
  void pushSampleToWindow(uint16_t sample);
  uint32_t computeMovingAverage() const;
  uint32_t computeMedianFromWindow() const;
  uint32_t selectRobustTarget(uint32_t average, uint32_t median) const;
  void initDeadzoneBounds();
  uint32_t applyDeadzone(uint32_t value) const;
  uint32_t applyHysteresisStep(uint32_t current, uint32_t target) const;
};

}  // namespace borguino::inputs

#endif