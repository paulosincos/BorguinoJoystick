#include "transformers/ComposedAnalogAxis.h"

namespace borguino::transformers {

ComposedAnalogAxis::ComposedAnalogAxis(inputs::AnalogPinInput &firstInput, inputs::AnalogPinInput &secondInput)
    : firstInput(firstInput), secondInput(secondInput) {
}

uint32_t ComposedAnalogAxis::getValue() const {
  uint32_t firstValue = -firstInput.getValue();
  uint32_t secondValue = secondInput.getValue();
  return firstValue + secondValue;
}

uint32_t ComposedAnalogAxis::minValue() const {
  return -firstInput.maxValue();
}

uint32_t ComposedAnalogAxis::maxValue() const {
  return secondInput.maxValue();
}

}  // namespace borguino::transformers
