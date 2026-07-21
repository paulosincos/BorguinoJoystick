#include "outputs/JoystickHatOutput.h"

#include <cmath>

namespace {
constexpr float PI_VALUE = PI;
constexpr float RADIANS_TO_DEGREES_FACTOR = 180.0f / PI_VALUE;
constexpr float DEGREES_TO_RADIANS_FACTOR = PI_VALUE / 180.0f;
constexpr float FULL_CIRCLE_DEGREES = 360.0f;
constexpr float ZERO_VECTOR_EPSILON = 0.0001f;
constexpr float HALF_DEGREE = 0.5f;
}

namespace borguino::outputs {

JoystickHatOutput::JoystickHatOutput(Joystick_ &joystick, uint8_t hatNumber, ValueProvider<bool> *const *inputs, size_t inputCount, bool combineInputs)
    : JoystickOutput(joystick), hatNumber(hatNumber), inputs(inputs), inputCount(inputCount), combineInputs(combineInputs), lastHatDirection(-2) {
}

int16_t JoystickHatOutput::getHatDirection() const {
  if (inputCount == 0 || inputs == nullptr) {
    return -1;
  }

  const float stepDegrees = FULL_CIRCLE_DEGREES / static_cast<float>(inputCount);

  int firstActiveInput = -1;
  int activeCount = 0;
  float vectorX = 0.0f;
  float vectorY = 0.0f;

  for (size_t i = 0; i < inputCount; ++i) {
    if (!inputs[i]->getValue()) {
      continue;
    }

    if (firstActiveInput < 0) {
      firstActiveInput = static_cast<int>(i);
    }

    ++activeCount;

    if (!combineInputs) {
      continue;
    }

    const float angleDegrees = static_cast<float>(i) * stepDegrees;
    const float angleRadians = angleDegrees * DEGREES_TO_RADIANS_FACTOR;
    vectorX += std::cos(angleRadians);
    vectorY += std::sin(angleRadians);
  }

  if (activeCount == 0) {
    return -1;
  }

  if (!combineInputs || activeCount == 1) {
    const int baseDirection = static_cast<int>((static_cast<float>(firstActiveInput) * stepDegrees) + HALF_DEGREE);
    return static_cast<int16_t>(baseDirection % 360);
  }

  if (std::fabs(vectorX) < ZERO_VECTOR_EPSILON && std::fabs(vectorY) < ZERO_VECTOR_EPSILON) {
    return -1;
  }

  float direction = std::atan2(vectorY, vectorX) * RADIANS_TO_DEGREES_FACTOR;
  if (direction < 0.0f) {
    direction += FULL_CIRCLE_DEGREES;
  }

  const int normalizedDirection = static_cast<int>(direction + HALF_DEGREE) % 360;
  return static_cast<int16_t>(normalizedDirection);
}

void JoystickHatOutput::update() {
  const int16_t hatDirection = getHatDirection();
  if (hatDirection == lastHatDirection) {
    return;
  }

  joystick.setHatSwitch(hatNumber, hatDirection);
  lastHatDirection = hatDirection;
}

}  // namespace borguino::outputs