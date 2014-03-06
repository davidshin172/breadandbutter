#include <Arduino.h>

namespace BreadAndButter {
  const uint8_t NUM_ANALOG_IN_PINS = 5;
  const uint8_t NUM_DIGITAL_IN_PINS = 5;
  const uint8_t NUM_DIGITAL_OUT_PINS = 5;

  struct Enumeration {
    unsigned int total;
    bool analogIn[NUM_ANALOG_IN_PINS];
    bool digitalIn[NUM_DIGITAL_IN_PINS];
    bool digitalOut[NUM_DIGITAL_OUT_PINS];
  };

  void InitShield();
  void InitEnumeration();
  unsigned int AnalogRead(uint8_t pin);
  int DigitalRead(uint8_t pin);
  void DigitalWrite(uint8_t pin, int state);
  void DigitalPwmWrite(uint8_t pin, unsigned char value);
  
  bool IsPwmCompatible(uint8_t digitalOutPin);
  
  Enumeration Enumerate();
}
