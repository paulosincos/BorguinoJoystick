#include "transformers/ToggleSwitchToPushButtonTransform.h"

#include <Arduino.h>

namespace borguino::transformers {

ToggleSwitchToPushButtonTransform::ToggleSwitchToPushButtonTransform(ValueProvider<bool> &input,
                                                                     uint32_t pushDurationMs)
    : input(input), pushDurationMs(pushDurationMs), lastInputState(input.getValue()) {}

bool ToggleSwitchToPushButtonTransform::getValue() const {
  const bool inputState = input.getValue();
  const uint32_t now = millis();

  if (inputState != lastInputState) {
    lastInputState = inputState;
    pulseActive = true;
    pulseStartedAtMs = now;
  }

  if (!pulseActive) {
    return false;
  }

  if (pushDurationMs == 0) {
    pulseActive = false;
    return true;
  }

  if ((now - pulseStartedAtMs) >= pushDurationMs) {
    pulseActive = false;
    return false;
  }

  return true;
}

}  // namespace borguino::transformers