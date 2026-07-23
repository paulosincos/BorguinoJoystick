#include "transformers/PushButtonToToggleSwitchTransform.h"

namespace borguino::transformers {

PushButtonToToggleSwitchTransform::PushButtonToToggleSwitchTransform(ValueProvider<bool> &input, bool initialState)
    : input(input), lastInputState(input.getValue()), outputState(initialState) {}

bool PushButtonToToggleSwitchTransform::getValue() const {
  const bool inputState = input.getValue();

  if (inputState && !lastInputState) {
    outputState = !outputState;
  }

  lastInputState = inputState;
  return outputState;
}

}  // namespace borguino::transformers