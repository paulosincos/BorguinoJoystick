#ifndef BORGUINO_TRANSFORMS_PUSH_BUTTON_TO_TOGGLE_SWITCH_TRANSFORM_H
#define BORGUINO_TRANSFORMS_PUSH_BUTTON_TO_TOGGLE_SWITCH_TRANSFORM_H

#include "ValueProvider.h"

namespace borguino::transforms {

class PushButtonToToggleSwitchTransform : public ValueProvider<bool> {
public:
  explicit PushButtonToToggleSwitchTransform(ValueProvider<bool> &input, bool initialState = false);

  bool getValue() const override;

protected:
  ValueProvider<bool> &input;
  mutable bool lastInputState = false;
  mutable bool outputState = false;
};

}  // namespace borguino::transforms

#endif