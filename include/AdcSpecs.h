#ifndef ADCSPECS_H
#define ADCSPECS_H

// The minimum value for a 10-bit ADC (Analog-to-Digital Converter)
constexpr int ADC_MIN_VALUE = 0;
// The maximum value for a 10-bit ADC (Analog-to-Digital Converter)
constexpr int ADC_MAX_VALUE = 1023;
// The center value for a 10-bit ADC (Analog-to-Digital Converter)
constexpr int ADC_CENTER_VALUE = (ADC_MIN_VALUE + ADC_MAX_VALUE) / 2;

#endif