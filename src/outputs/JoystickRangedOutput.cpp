#include "outputs/JoystickRangedOutput.h"

namespace borguino::outputs {

JoystickRangedOutput::JoystickRangedOutput(Joystick_ &joystick, JoystickRangedOutputType outputType, RangedValueProvider<uint32_t> &input)
    : JoystickOutput(joystick), outputType(outputType), input(input) {
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

}  // namespace borguino::outputs