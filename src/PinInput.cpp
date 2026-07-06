#include "PinInput.h"

#include <Arduino.h>

DigitalPinInput::DigitalPinInput(uint8_t pin) : pin(pin) {
  debouncer.attach(pin, INPUT_PULLUP);
  debouncer.interval(25);
}

bool DigitalPinInput::getValue() const {
  return !debouncer.read();
}

void DigitalPinInput::update() {
  debouncer.update();
}

AnalogPinInput::AnalogPinInput(uint8_t pin) : pin(pin) {
}

float AnalogPinInput::getValue() const {
  return analogRead(pin) / 1023.0; // Normalize to range [0, 1]
}

void AnalogPinInput::update() {
  // No update needed for analog inputs
}