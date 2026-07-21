#include "inputs/ComposedAnalogPinInput.h"

namespace borguino::inputs {

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

}  // namespace borguino::inputs