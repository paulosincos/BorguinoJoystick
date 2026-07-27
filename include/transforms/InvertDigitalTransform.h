#ifndef BORGUINO_TRANSFORMS_INVERT_DIGITAL_TRANSFORM_H
#define BORGUINO_TRANSFORMS_INVERT_DIGITAL_TRANSFORM_H

#include "ValueProvider.h"

namespace borguino::transforms {

class InvertDigitalTransform : public ValueProvider<bool> {
public:
  explicit InvertDigitalTransform(ValueProvider<bool> &input);

  bool getValue() const override;

protected:
  ValueProvider<bool> &input;
};

}  // namespace borguino::transforms

#endif
