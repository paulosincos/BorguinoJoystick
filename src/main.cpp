#include <Arduino.h>
#include "Engine.h"

void setup() {
  borguino::engine::setup();
}

void loop() {
  borguino::engine::updateInputs();
  borguino::engine::updateOutputs();

  delay(10);
}
