#ifndef BORGUINO_TRANSFORMS_DIGITAL_TO_ANALOG_CONVERTER_H
#define BORGUINO_TRANSFORMS_DIGITAL_TO_ANALOG_CONVERTER_H

#include <cstdint>

#include "AdcSpecs.h"
#include "ValueProvider.h"

namespace borguino::transforms {

/**
 * @brief DigitalToAnalogTransform converts a digital boolean input value to an analog output value based on specified thresholds and activation time.
 */
class DigitalToAnalogConverter : public RangedValueProvider<uint32_t> {
public:
  /**
   * @brief Construct a new DigitalToAnalogConverter object
   * @param input The ValueProvider<bool> that provides the input value
   * @param minValue The minimum output value (default: ADC_MIN_VALUE)
   * @param maxValue The maximum output value (default: ADC_MAX_VALUE)
   * @param activationTimeMs The time in milliseconds to transition from false to true output (default: 100)
   * @param falseValue The output value when the input is false (default: minValue)
   * @param trueValue The output value when the input is true (default: maxValue)
   */
  explicit DigitalToAnalogConverter(ValueProvider<bool> &input,
                                    uint32_t minValue = ADC_MIN_VALUE,
                                    uint32_t maxValue = ADC_MAX_VALUE,
                                    uint32_t activationTimeMs = 100,
                                    uint32_t falseValue = UINT32_MAX,
                                    uint32_t trueValue = UINT32_MAX);

  /**
   * @brief Get the current analog output value based on the digital input and thresholds.
   * @return The current output value of type uint32_t
   */
  uint32_t getValue() const override;
  /**
   * @brief Get the minimum possible output value
   * @return The minimum output value of type uint32_t
   */
  uint32_t minValue() const override;
  /**
   * @brief Get the maximum possible output value
   * @return The maximum output value of type uint32_t
   */
  uint32_t maxValue() const override;

protected:
  ValueProvider<bool> &input;
  uint32_t minOutputValue = 0;
  uint32_t maxOutputValue = 0;
  uint32_t falseOutputValue = 0;
  uint32_t trueOutputValue = 0;
  uint32_t outputSpan = 0;
  uint32_t activationTimeMs = 0;

  mutable bool initialized = false;
  mutable bool lastInputState = false;
  mutable uint32_t currentValue = 0;

  mutable uint32_t transitionStartValue = 0;
  mutable uint32_t transitionTargetValue = 0;
  mutable uint32_t transitionStartMs = 0;
  mutable uint32_t transitionDurationMs = 0;
};

}  // namespace borguino::transforms

#endif