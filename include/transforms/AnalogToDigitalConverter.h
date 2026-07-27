#ifndef BORGUINO_TRANSFORMS_ANALOG_TO_DIGITAL_CONVERTER_H
#define BORGUINO_TRANSFORMS_ANALOG_TO_DIGITAL_CONVERTER_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transforms {

/**
 * @brief converts an analog input value to a digital boolean output based on specified thresholds and hysteresis.
 */
class AnalogToDigitalConverter : public ValueProvider<bool> {
public:

  explicit AnalogToDigitalConverter(RangedValueProvider<uint32_t> &input,
                                    uint8_t trueRangeStartPercentage = 50,
                                    uint8_t trueRangeEndPercentage = 100,
                                    uint8_t hysteresisPercentage = 1);

  /**
   * @brief Get the current digital output value based on the analog input and thresholds.
   * @return The current boolean output value (true or false)
   */
  bool getValue() const override;

protected:
  RangedValueProvider<uint32_t> &input;
  uint32_t trueRangeStartValue = 0;
  uint32_t trueRangeEndValue = 0;
  uint32_t hysteresisOffset = 0;
  uint32_t startOnThreshold = 0;
  uint32_t endOnThreshold = 0;
  uint32_t startOffThreshold = 0;
  uint32_t endOffThreshold = 0;
  mutable bool state = false;
};

}  // namespace borguino::transforms

#endif
