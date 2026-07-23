#include "transformers/InvertDigitalTransform.h"

namespace borguino::transformers {

InvertDigitalTransform::InvertDigitalTransform(ValueProvider<bool> &input)
    : input(input) {}

bool InvertDigitalTransform::getValue() const {
  return !input.getValue();
}

}  // namespace borguino::transformers
