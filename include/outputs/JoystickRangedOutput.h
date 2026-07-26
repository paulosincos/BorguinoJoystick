#ifndef BORGUINO_OUTPUTS_JOYSTICK_RANGED_OUTPUT_H
#define BORGUINO_OUTPUTS_JOYSTICK_RANGED_OUTPUT_H

#include <cstdint>

#include "outputs/JoystickOutput.h"
#include "ValueProvider.h"

namespace borguino::outputs {

/**
 * @brief Enum representing the different types of joystick ranged outputs.
 */
enum JoystickRangedOutputType {
  Accelerator,
  Brake,
  RotateXAxis,
  RotateYAxis,
  RotateZAxis,
  Rudder,
  Steering,
  Throttle,
  XAxis,
  YAxis,
  ZAxis,
};

/**
 * @brief Output that sends joystick ranged values based on the input value.
 */
class JoystickRangedOutput : public JoystickOutput {
public:
  /**
   * @brief Construct a new JoystickRangedOutput object
   * @param joystick The Joystick_ instance to send the output to
   * @param outputType The type of joystick ranged output (e.g., Accelerator, Brake, etc.)
   * @param input The RangedValueProvider<uint32_t> that provides the input value
   */
  explicit JoystickRangedOutput(Joystick_ &joystick, JoystickRangedOutputType outputType, RangedValueProvider<uint32_t> &input);

  /**
   * @brief Update the state of the joystick ranged output
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the output.
   */
  void update() override;

protected:
  void setRange(uint32_t minValue, uint32_t maxValue);
  void setValue(uint32_t value);
  
  JoystickRangedOutputType outputType;
  RangedValueProvider<uint32_t> &input;
  uint32_t lastValue = 0;
};

}  // namespace borguino::outputs

#endif