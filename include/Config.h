#ifndef BORGUINO_CONFIG_H
#define BORGUINO_CONFIG_H

#include <stddef.h>
#include <Joystick.h>

#include "SignalInput.h"
#include "SignalOutput.h"

namespace borguino::config {

extern Joystick_ joystick;

extern SignalInput* const inputs[];
extern const size_t inputCount;

extern SignalOutput* const outputs[];
extern const size_t outputCount;

} // namespace borguino::config

#endif
