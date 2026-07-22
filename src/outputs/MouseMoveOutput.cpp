#include "outputs/MouseMoveOutput.h"

#include <Mouse.h>

namespace {
constexpr int8_t MOUSE_DELTA_MIN = -127;
constexpr int8_t MOUSE_DELTA_MAX = 127;
}

namespace borguino::outputs {

MouseMoveOutput::MouseMoveOutput(RangedValueProvider<uint32_t> &xInput,
                                 RangedValueProvider<uint32_t> &yInput,
                                 uint16_t deadzone,
                                 uint16_t divisor,
                                 bool invertY)
    : xInput(xInput), yInput(yInput), deadzone(deadzone), divisor(divisor == 0 ? 1 : divisor), invertY(invertY) {
}

// [Vibe-Coded]
int8_t MouseMoveOutput::toRelativeDelta(const RangedValueProvider<uint32_t> &input,
                                        uint32_t rawValue,
                                        uint16_t deadzone,
                                        uint16_t divisor) {
  const int32_t minValue = static_cast<int32_t>(input.minValue());
  const int32_t maxValue = static_cast<int32_t>(input.maxValue());
  const int32_t center = minValue + ((maxValue - minValue) / 2);
  const int32_t signedDistance = static_cast<int32_t>(rawValue) - center;
  const int32_t absDistance = signedDistance >= 0 ? signedDistance : -signedDistance;

  if (absDistance <= static_cast<int32_t>(deadzone)) {
    return 0;
  }

  int32_t magnitude = absDistance / static_cast<int32_t>(divisor);
  if (magnitude == 0) {
    magnitude = 1;
  }

  int32_t delta = signedDistance > 0 ? magnitude : -magnitude;
  if (delta > MOUSE_DELTA_MAX) {
    delta = MOUSE_DELTA_MAX;
  }
  if (delta < MOUSE_DELTA_MIN) {
    delta = MOUSE_DELTA_MIN;
  }

  return static_cast<int8_t>(delta);
}

void MouseMoveOutput::update() {
  const int8_t xDelta = toRelativeDelta(xInput, xInput.getValue(), deadzone, divisor);
  int8_t yDelta = toRelativeDelta(yInput, yInput.getValue(), deadzone, divisor);
  if (invertY) {
    yDelta = static_cast<int8_t>(-yDelta);
  }

  if (xDelta == 0 && yDelta == 0) {
    return;
  }

  Mouse.move(xDelta, yDelta, 0);
}

}  // namespace borguino::outputs
