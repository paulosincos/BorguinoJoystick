#include "transformers/DigitalToAnalogTransform.h"

#include <Arduino.h>

namespace borguino::transformers {

namespace {

uint32_t absoluteDistance(uint32_t a, uint32_t b) {
  return (a >= b) ? (a - b) : (b - a);
}

uint32_t clampToRange(uint32_t value, uint32_t minValue, uint32_t maxValue) {
  if (value < minValue) {
    return minValue;
  }
  if (value > maxValue) {
    return maxValue;
  }
  return value;
}

uint32_t interpolateLinear(uint32_t start, uint32_t target, uint32_t elapsed, uint32_t duration) {
  if (duration == 0 || elapsed >= duration) {
    return target;
  }

  const int64_t signedStart = static_cast<int64_t>(start);
  const int64_t signedDelta = static_cast<int64_t>(target) - static_cast<int64_t>(start);
  const int64_t signedProgress = (signedDelta * static_cast<int64_t>(elapsed)) / static_cast<int64_t>(duration);
  const int64_t interpolated = signedStart + signedProgress;

  if (interpolated <= 0) {
    return 0;
  }
  if (interpolated >= static_cast<int64_t>(UINT32_MAX)) {
    return UINT32_MAX;
  }
  return static_cast<uint32_t>(interpolated);
}

}  // namespace

DigitalToAnalogTransform::DigitalToAnalogTransform(ValueProvider<bool> &input,
                                                   uint32_t minValue,
                                                   uint32_t maxValue,
                                                   uint32_t activationTimeMs)
    : input(input), activationTimeMs(activationTimeMs) {
  if (maxValue >= minValue) {
    minOutputValue = minValue;
    maxOutputValue = maxValue;
  } else {
    minOutputValue = maxValue;
    maxOutputValue = minValue;
  }

  outputSpan = maxOutputValue - minOutputValue;
}

// [Vibe-Coded]
uint32_t DigitalToAnalogTransform::getValue() const {
  const bool inputState = input.getValue();
  const uint32_t now = millis();

  if (!initialized) {
    initialized = true;
    lastInputState = inputState;
    currentValue = inputState ? maxOutputValue : minOutputValue;
    transitionStartValue = currentValue;
    transitionTargetValue = currentValue;
    transitionStartMs = now;
    transitionDurationMs = 0;
    return currentValue;
  }

  if (transitionDurationMs > 0) {
    const uint32_t elapsed = now - transitionStartMs;
    if (elapsed >= transitionDurationMs) {
      currentValue = transitionTargetValue;
      transitionDurationMs = 0;
    } else {
      currentValue = interpolateLinear(transitionStartValue, transitionTargetValue, elapsed, transitionDurationMs);
      currentValue = clampToRange(currentValue, minOutputValue, maxOutputValue);
    }
  }

  if (activationTimeMs == 0) {
    currentValue = inputState ? maxOutputValue : minOutputValue;
    lastInputState = inputState;
    transitionStartValue = currentValue;
    transitionTargetValue = currentValue;
    transitionStartMs = now;
    transitionDurationMs = 0;
    return currentValue;
  }

  if (inputState != lastInputState) {
    const uint32_t nextTarget = inputState ? maxOutputValue : minOutputValue;
    const uint32_t distance = absoluteDistance(currentValue, nextTarget);

    transitionStartValue = currentValue;
    transitionTargetValue = nextTarget;
    transitionStartMs = now;

    if (outputSpan == 0 || distance == 0) {
      transitionDurationMs = 0;
      currentValue = nextTarget;
    } else {
      uint32_t duration = static_cast<uint32_t>((static_cast<uint64_t>(activationTimeMs) * distance) / outputSpan);
      if (duration == 0) {
        duration = 1;
      }
      transitionDurationMs = duration;
    }

    lastInputState = inputState;
  }

  if (transitionDurationMs == 0) {
    currentValue = transitionTargetValue;
  }

  return currentValue;
}

uint32_t DigitalToAnalogTransform::minValue() const {
  return minOutputValue;
}

uint32_t DigitalToAnalogTransform::maxValue() const {
  return maxOutputValue;
}

}  // namespace borguino::transformers