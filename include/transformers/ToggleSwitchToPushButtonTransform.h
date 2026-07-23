#ifndef BORGUINO_TRANSFORMERS_TOGGLE_SWITCH_TO_PUSH_BUTTON_TRANSFORM_H
#define BORGUINO_TRANSFORMERS_TOGGLE_SWITCH_TO_PUSH_BUTTON_TRANSFORM_H

#include <cstdint>

#include "ValueProvider.h"

namespace borguino::transformers {

class ToggleSwitchToPushButtonTransform : public ValueProvider<bool> {
public:
  explicit ToggleSwitchToPushButtonTransform(ValueProvider<bool> &input, uint32_t pushDurationMs = 100);

  bool getValue() const override;

protected:
  ValueProvider<bool> &input;
  uint32_t pushDurationMs = 100;

  mutable bool lastInputState = false;
  mutable bool pulseActive = false;
  mutable uint32_t pulseStartedAtMs = 0;
};

}  // namespace borguino::transformers

#endif