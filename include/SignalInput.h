#ifndef SIGNAL_INPUT_H
#define SIGNAL_INPUT_H

class SignalInput {
public:
  virtual ~SignalInput() = default;
  virtual void update() = 0;
};

template <typename T>
class GenericSignalInput: public SignalInput {
public:
  virtual T getValue() const = 0;
};

#endif
