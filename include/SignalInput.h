#ifndef SIGNAL_INPUT_H
#define SIGNAL_INPUT_H

class SignalInput {
public:
  virtual ~SignalInput() = default;
};

template <typename T>
class GenericSignalInput: public SignalInput {
public:
  virtual T getValue() const = 0;
};

class UpdatableSignalInput {
public:
  virtual void update() = 0;
};

#endif
