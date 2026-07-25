#ifndef BORGUINO_INPUTS_DIGITAL_PIN_INPUT_H
#define BORGUINO_INPUTS_DIGITAL_PIN_INPUT_H

#include <cstdint>
#include <Arduino.h>
#include <Bounce2.h>

#include "SignalInput.h"
#include "ValueProvider.h"

namespace borguino::inputs {

/**
 * @brief A class that represents a digital pin input with debouncing.
 *
 * This class provides an interface for reading the state of a digital pin
 * while applying debouncing to filter out noise and false triggers.
 */
class DigitalPinInput : public SignalInput, public ValueProvider<bool> {
public:
  /**
   * @brief Construct a new Digital Pin Input object
   * @param pin The digital pin number
   * @param mode The pin mode (default is INPUT_PULLUP)
   */
  explicit DigitalPinInput(uint8_t pin, int mode = INPUT_PULLUP);

  /**
   * @brief Get the current value of the digital pin
   * @return true if the pin is HIGH, false if LOW
   */
  bool getValue() const override;

  /**
   * @brief Update the state of the digital pin input
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the debounced state of the pin.
   */
  void update() override;

protected:
  uint8_t pin;
  Bounce debouncer;
};

}  // namespace borguino::inputs

#endif