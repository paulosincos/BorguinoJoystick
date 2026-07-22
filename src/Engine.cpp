#include "Engine.h"

#include "Config.h"

namespace borguino::engine {

void setup() {
  borguino::config::joystick.begin();
}

void updateInputs() {
  for (size_t i = 0; i < borguino::config::inputCount; ++i) {
    borguino::config::inputs[i]->update();
  }
}

void updateOutputs() {
  for (size_t i = 0; i < borguino::config::outputCount; ++i) {
    borguino::config::outputs[i]->update();
  }
}

} // namespace borguino::engine
