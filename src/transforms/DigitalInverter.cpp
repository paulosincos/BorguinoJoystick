#include "transforms/DigitalInverter.h"

namespace borguino::transforms {

DigitalInverter::DigitalInverter(ValueProvider<bool> &input)
    : input(input) {}

bool DigitalInverter::getValue() const {
  return !input.getValue();
}

}  // namespace borguino::transforms
