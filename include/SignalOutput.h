#ifndef SIGNAL_OUTPUT_H
#define SIGNAL_OUTPUT_H

#include "SignalInput.h"

/**
 * @brief SignalOutput is an abstract base class that defines the interface for signal output targets.
 *
 * This class provides a common interface for various types of signal outputs, such as joystick, mouse and keyboard outputs.
 * Derived classes must implement the update() method to update their state.
 */
class SignalOutput {
public:
virtual ~SignalOutput() = default;
/**
 * @brief Update the state of the signal output
 *
 * This method should be called regularly (e.g., in the main loop/engine)
 * to update the state of the output.
 */
virtual void update() = 0;
};

#endif
