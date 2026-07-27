#include "transforms/InvertDigitalTransform.h"

namespace borguino::transforms {

InvertDigitalTransform::InvertDigitalTransform(ValueProvider<bool> &input)
    : input(input) {}

bool InvertDigitalTransform::getValue() const {
  return !input.getValue();
}

}  // namespace borguino::transforms
