#ifndef BORGUINO_OUTPUTS_MOUSE_WHEEL_OUTPUT_H
#define BORGUINO_OUTPUTS_MOUSE_WHEEL_OUTPUT_H

#include <cstdint>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

class MouseWheelOutput : public SignalOutput {
public:
  // [Vibe-Coded]
  explicit MouseWheelOutput(RangedValueProvider<uint32_t> &input,
                            uint16_t deadzone = 24,
                            uint16_t divisor = 192,
                            bool invertDirection = false);

  void update() override;

protected:
  static int8_t toRelativeDelta(const RangedValueProvider<uint32_t> &input,
                                uint32_t rawValue,
                                uint16_t deadzone,
                                uint16_t divisor);

  RangedValueProvider<uint32_t> &input;
  uint16_t deadzone;
  uint16_t divisor;
  bool invertDirection;
};

}  // namespace borguino::outputs

#endif
