#ifndef BORGUINO_OUTPUTS_MOUSE_MOVE_OUTPUT_H
#define BORGUINO_OUTPUTS_MOUSE_MOVE_OUTPUT_H

#include <cstdint>

#include "SignalOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

class MouseMoveOutput : public SignalOutput {
public:
  // [Vibe-Coded]
  explicit MouseMoveOutput(RangedValueProvider<uint32_t> &xInput,
                           RangedValueProvider<uint32_t> &yInput,
                           uint16_t deadzone = 24,
                           uint16_t divisor = 128,
                           bool invertY = true);

  void update() override;

protected:
  static int8_t toRelativeDelta(const RangedValueProvider<uint32_t> &input,
                                uint32_t rawValue,
                                uint16_t deadzone,
                                uint16_t divisor);

  RangedValueProvider<uint32_t> &xInput;
  RangedValueProvider<uint32_t> &yInput;
  uint16_t deadzone;
  uint16_t divisor;
  bool invertY;
};

}  // namespace borguino::outputs

#endif
