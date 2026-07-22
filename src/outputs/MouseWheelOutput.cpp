#include "outputs/MouseWheelOutput.h"

#include <Mouse.h>

namespace {
constexpr int8_t MOUSE_DELTA_MIN = -127;
constexpr int8_t MOUSE_DELTA_MAX = 127;
}

namespace borguino::outputs {

MouseWheelOutput::MouseWheelOutput(RangedValueProvider<uint32_t> &input,
                                   uint16_t deadzone,
                                   uint16_t divisor,
                                   bool invertDirection)
    : input(input), deadzone(deadzone), divisor(divisor == 0 ? 1 : divisor), invertDirection(invertDirection) {
}

// [Vibe-Coded]
int8_t MouseWheelOutput::toRelativeDelta(const RangedValueProvider<uint32_t> &input,
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

void MouseWheelOutput::update() {
  int8_t wheelDelta = toRelativeDelta(input, input.getValue(), deadzone, divisor);
  if (invertDirection) {
    wheelDelta = static_cast<int8_t>(-wheelDelta);
  }

  if (wheelDelta == 0) {
    return;
  }

  Mouse.move(0, 0, wheelDelta);
}

}  // namespace borguino::outputs
