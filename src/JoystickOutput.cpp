#include "JoystickOutput.h"
#include "AdcSpecs.h"

#include <cmath>

namespace {
constexpr float RADIANS_TO_DEGREES_FACTOR = 180.0f / PI;
constexpr float DEGREES_TO_RADIANS_FACTOR = PI / 180.0f;
}

JoystickButtonOutput::JoystickButtonOutput(Joystick_ &joystick, uint8_t buttonNumber, ValueProvider<bool> &input) : JoystickOutput(joystick), buttonNumber(buttonNumber), input(input) {
}

void JoystickButtonOutput::update() {
    joystick.setButton(buttonNumber, input.getValue());
}

JoystickRangedOutput::JoystickRangedOutput(Joystick_ &joystick, JoystickRangedOutputType outputType, RangedValueProvider<uint32_t> &input) : JoystickOutput(joystick), outputType(outputType), input(input) {
    auto minValue = input.minValue();
    auto maxValue = input.maxValue();
    switch (outputType) {
        case Accelerator:
            joystick.setAcceleratorRange(minValue, maxValue);
            break;
        case Brake:
            joystick.setBrakeRange(minValue, maxValue);
            break;
        case RotateXAxis:
            joystick.setRxAxisRange(minValue, maxValue);
            break;
        case RotateYAxis:
            joystick.setRyAxisRange(minValue, maxValue);
            break;
        case RotateZAxis:
            joystick.setRzAxisRange(minValue, maxValue);
            break;
        case Rudder:
            joystick.setRudderRange(minValue, maxValue);
            break;
        case Steering:
            joystick.setSteeringRange(minValue, maxValue);
            break;
        case Throttle:
            joystick.setThrottleRange(minValue, maxValue);
            break;
        case XAxis:
            joystick.setXAxisRange(minValue, maxValue);
            break;
        case YAxis:
            joystick.setYAxisRange(minValue, maxValue);
            break;
        case ZAxis:
            joystick.setZAxisRange(minValue, maxValue);
            break;
    }
}

void JoystickRangedOutput::update() {
    auto value = input.getValue();
    switch (outputType) {
        case Accelerator:
            joystick.setAccelerator(value);
            break;
        case Brake:
            joystick.setBrake(value);
            break;
        case RotateXAxis:
            joystick.setRxAxis(value);
            break;
        case RotateYAxis:
            joystick.setRyAxis(value);
            break;
        case RotateZAxis:
            joystick.setRzAxis(value);
            break;
        case Rudder:
            joystick.setRudder(value);
            break;
        case Steering:
            joystick.setSteering(value);
            break;
        case Throttle:
            joystick.setThrottle(value);
            break;
        case XAxis:
            joystick.setXAxis(value);
            break;
        case YAxis:
            joystick.setYAxis(value);
            break;
        case ZAxis:
            joystick.setZAxis(value);
            break;
    }
}

JoystickHatOutput::JoystickHatOutput(Joystick_ &joystick, uint8_t hatNumber, ValueProvider<bool> *const *inputs, size_t inputCount, bool combineInputs)
    : JoystickOutput(joystick), hatNumber(hatNumber), inputs(inputs), inputCount(inputCount), combineInputs(combineInputs), lastHatDirection(-2) {
}

int16_t JoystickHatOutput::getHatDirection() const {
    if (inputCount == 0 || inputs == nullptr) {
        return -1;
    }

    const float stepDegrees = 360.0f / static_cast<float>(inputCount);

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
        const int baseDirection = static_cast<int>((static_cast<float>(firstActiveInput) * stepDegrees) + 0.5f);
        return static_cast<int16_t>(baseDirection % 360);
    }

    if (std::fabs(vectorX) < 0.0001f && std::fabs(vectorY) < 0.0001f) {
        return -1;
    }

    float direction = std::atan2(vectorY, vectorX) * RADIANS_TO_DEGREES_FACTOR;
    if (direction < 0.0f) {
        direction += 360.0f;
    }

    const int normalizedDirection = static_cast<int>(direction + 0.5f) % 360;
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