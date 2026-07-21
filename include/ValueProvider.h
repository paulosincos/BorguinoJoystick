#ifndef VALUE_PROVIDER_H
#define VALUE_PROVIDER_H

template <typename T>
class ValueProvider {
public:
  virtual T getValue() const = 0;
};

template <typename T>
class RangedValueProvider: public ValueProvider<T> {
public:
  virtual T minValue() const = 0;
  virtual T maxValue() const = 0;
};
#endif
