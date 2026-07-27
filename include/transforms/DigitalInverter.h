#ifndef BORGUINO_TRANSFORMS_DIGITAL_INVERTER_H
#define BORGUINO_TRANSFORMS_DIGITAL_INVERTER_H

#include "ValueProvider.h"

namespace borguino::transforms {

class DigitalInverter : public ValueProvider<bool> {
public:
  explicit DigitalInverter(ValueProvider<bool> &input);

  bool getValue() const override;

protected:
  ValueProvider<bool> &input;
};

}  // namespace borguino::transforms

#endif
