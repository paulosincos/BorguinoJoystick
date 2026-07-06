#ifndef PIN_INPUT_H
#define PIN_INPUT_H

#include <cstdint>
#include <Bounce2.h>

#include "SignalInput.h"

class DigitalPinInput : public GenericSignalInput<bool> {
public:
  explicit DigitalPinInput(uint8_t pin);

  bool getValue() const override;
  void update() override;

protected:
  uint8_t pin;
  Bounce debouncer;
};

class AnalogPinInput : public GenericSignalInput<float> {
public:
  explicit AnalogPinInput(uint8_t pin);

  float getValue() const override;
  void update() override;

protected:
  uint8_t pin;
};

#endif
