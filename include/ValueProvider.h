#ifndef VALUE_PROVIDER_H
#define VALUE_PROVIDER_H

/**
 * @brief ValueProvider is an abstract base class that defines the interface for providing values of type T.
 *
 * This class provides a common interface for various types of value providers, such as analog and digital inputs.
 * Also, it can be used as mapper, transform, decorator, proxy, facade or etc.
 * Derived classes must implement the getValue() method to provide the current value.
 * 
 * @param T The type of value provided by the derived class
 */
template <typename T>
class ValueProvider {
public:
  /**
   * @brief Get the current value
   * @return The current value of type T
   */
  virtual T getValue() const = 0;
};

/**
 * @brief RangedValueProvider is an abstract base class that extends ValueProvider to provide a range of values.
 *
 * This class provides a common interface for value providers that have a defined minimum and maximum value.
 * Derived classes must implement the minValue() and maxValue() methods to provide the range of values.
 * 
 * @param T The type of value provided by the derived class
 */
template <typename T>
class RangedValueProvider: public ValueProvider<T> {
public:
  /**
   * @brief Get the minimum possible value
   * @return The minimum value of type T
   */
  virtual T minValue() const = 0;
  /**
   * @brief Get the maximum possible value
   * @return The maximum value of type T
   */
  virtual T maxValue() const = 0;
};
#endif
