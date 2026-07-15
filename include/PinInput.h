#ifndef PIN_INPUT_H
#define PIN_INPUT_H

#include <cstdint>
#include <Bounce2.h>

#include "SignalInput.h"

class DigitalPinInput : public GenericSignalInput<bool>, public UpdatableSignalInput {
public:
  explicit DigitalPinInput(uint8_t pin);

  bool getValue() const override;
  void update() override;

  protected:
  uint8_t pin;
  Bounce debouncer;
};

class AnalogPinInput : public GenericSignalInput<uint32_t>, public UpdatableSignalInput {
public:
  explicit AnalogPinInput(uint8_t pin);

  uint32_t getValue() const override;
  void update() override;

protected:
  uint8_t pin;
};

class ComposedAnalogPinInput : public GenericSignalInput<uint32_t> {
public:
  ComposedAnalogPinInput(AnalogPinInput &negativeInput, AnalogPinInput &positiveInput);

  uint32_t getValue() const override;
protected:
  AnalogPinInput &negativeInput;
  AnalogPinInput &positiveInput;
};
#endif
