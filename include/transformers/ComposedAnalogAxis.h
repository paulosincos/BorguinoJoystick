#ifndef BORGUINO_TRANSFORMERS_COMPOSED_ANALOG_AXIS_H
#define BORGUINO_TRANSFORMERS_COMPOSED_ANALOG_AXIS_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transformers {

/**
 * @brief ComposedAnalogAxis combines two analog inputs into a single axis value.
 */
class ComposedAnalogAxis : public RangedValueProvider<uint32_t> {
public:
  /**
   * @brief Construct a new ComposedAnalogAxis object
   * @param rangeAInput The first RangedValueProvider<uint32_t> input
   * @param rangeBInput The second RangedValueProvider<uint32_t> input
   */
  ComposedAnalogAxis(RangedValueProvider<uint32_t> &rangeAInput, RangedValueProvider<uint32_t> &rangeBInput);

  /**
   * @brief Get the current value of the composed axis
   * @return The current composed axis value
   */
  uint32_t getValue() const override;

  /**
   * @brief Get the minimum possible value of the composed axis
   * @return The minimum value of the composed axis
   */
  uint32_t minValue() const override;

  /**
   * @brief Get the maximum possible value of the composed axis
   * @return The maximum value of the composed axis
   */
  uint32_t maxValue() const override;

protected:
  RangedValueProvider<uint32_t> &rangeAInput;
  RangedValueProvider<uint32_t> &rangeBInput;

  uint32_t rangeAMin = 0;
  uint32_t rangeBMin = 0;
  uint32_t rangeASpan = 0;
  uint32_t rangeBSpan = 0;
  uint32_t axisMaxValue = 0;
  uint32_t axisCenterValue = 0;
};

}  // namespace borguino::transformers

#endif
