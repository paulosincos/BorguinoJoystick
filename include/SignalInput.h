#ifndef SIGNAL_INPUT_H
#define SIGNAL_INPUT_H

/**
 * @brief SignalInput is an abstract base class that defines the interface for signal input sources.
 *
 * This class provides a common interface for various types of signal inputs, such as analog and digital inputs.
 * Derived classes must implement the update() method to update their state.
 */
class SignalInput {
public:
  virtual ~SignalInput() = default;
  /**
   * @brief Update the state of the signal input
   *
   * This method should be called regularly (e.g., in the main loop/engine)
   * to update the state of the input.
   */
  virtual void update() = 0;
};
#endif
