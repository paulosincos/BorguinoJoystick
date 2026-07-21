#ifndef SIGNAL_INPUT_H
#define SIGNAL_INPUT_H

class SignalInput {
public:
  virtual ~SignalInput() = default;
  virtual void update() = 0;
};
#endif
