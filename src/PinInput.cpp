#include <Arduino.h>

#include "AdcSpecs.h"
#include "PinInput.h"

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

uint32_t AnalogPinInput::getValue() const {
  return analogRead(pin);
}

void AnalogPinInput::update() {
  // TODO: implement signal filtering if needed
}

ComposedAnalogPinInput::ComposedAnalogPinInput(AnalogPinInput &negativeInput, AnalogPinInput &positiveInput) : negativeInput(negativeInput), positiveInput(positiveInput) {
}

uint32_t ComposedAnalogPinInput::getValue() const {
  uint32_t negativeValue = -negativeInput.getValue(); // -1023..0
  uint32_t positiveValue = positiveInput.getValue(); // 0..1023
  return (ADC_MAX_VALUE + negativeValue + positiveValue) / 2; // 0..1023, where 512 is 0 negative and 0 positive
}