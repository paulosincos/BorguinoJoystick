#ifndef SIGNAL_OUTPUT_H
#define SIGNAL_OUTPUT_H

#include "SignalInput.h"

class SignalOutput {
public:
  virtual void update() = 0;
  virtual ~SignalOutput() = default;
};

#endif
