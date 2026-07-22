#include "outputs/JoystickHatOutput.h"

namespace {
constexpr float FULL_CIRCLE_DEGREES = 360.0f;
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
  int secondActiveInput = -1;
  int activeCount = 0;

  for (size_t i = 0; i < inputCount; ++i) {
    if (!inputs[i]->getValue()) {
      continue;
    }

    if (firstActiveInput < 0) {
      firstActiveInput = static_cast<int>(i);
    }

    ++activeCount;

    if (secondActiveInput < 0 && static_cast<int>(i) != firstActiveInput) {
      secondActiveInput = static_cast<int>(i);
    }
  }

  if (activeCount == 0) {
    return -1;
  }

  if (!combineInputs || activeCount == 1) {
    const int baseDirection = static_cast<int>((static_cast<float>(firstActiveInput) * stepDegrees) + HALF_DEGREE);
    return static_cast<int16_t>(baseDirection % 360);
  }

  if (activeCount > 2 || secondActiveInput < 0) {
    return -1;
  }

  const int first = firstActiveInput;
  const int second = secondActiveInput;
  const int indexDistance = (first > second) ? (first - second) : (second - first);
  const bool isAdjacent = (indexDistance == 1) || (indexDistance == static_cast<int>(inputCount) - 1);
  if (!isAdjacent) {
    return -1;
  }

  float firstAngle = static_cast<float>(first) * stepDegrees;
  float secondAngle = static_cast<float>(second) * stepDegrees;

  // Handle wrap-around adjacency (e.g., last index with index 0) before averaging.
  if ((firstAngle > secondAngle ? (firstAngle - secondAngle) : (secondAngle - firstAngle)) > (FULL_CIRCLE_DEGREES / 2.0f)) {
    if (firstAngle < secondAngle) {
      firstAngle += FULL_CIRCLE_DEGREES;
    } else {
      secondAngle += FULL_CIRCLE_DEGREES;
    }
  }

  float averagedDirection = (firstAngle + secondAngle) / 2.0f;
  if (averagedDirection >= FULL_CIRCLE_DEGREES) {
    averagedDirection -= FULL_CIRCLE_DEGREES;
  }

  const int normalizedDirection = static_cast<int>(averagedDirection + HALF_DEGREE) % 360;
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