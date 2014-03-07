#include <BreadAndButter.h>
#include <SPI.h> // MCP23S17 dependency
#include <MCP23S17.h>

namespace BreadAndButter {
  namespace {
    const uint8_t ANALOG_IN_PIN_MAPPING[NUM_ANALOG_IN_PINS] = {A0, A1, A2, A3, A4};
    const uint8_t DIGITAL_IN_PIN_MAPPING[NUM_DIGITAL_IN_PINS] = {0, 1, 2, 3, 4};
    const uint8_t DIGITAL_OUT_PIN_MAPPING[NUM_DIGITAL_OUT_PINS] = {5, 6, 7, 8, 9};

    const uint8_t ERROR_LED_PIN = 13;
    const uint8_t ERROR_BLINK_INTERVAL_MS = 100;

    const uint8_t ENUMERATOR_PIN_OFFSET = 1; // Enumerator's pins starts from 1, oddly enough
    const uint8_t ANALOG_IN_PIN_OFFSET = 0;
    const uint8_t DIGITAL_IN_PIN_OFFSET = 6;
    const uint8_t DIGITAL_OUT_PIN_OFFSET = 11;

    MCP enumerator(0);

    void Error()
    {
      while (true) {
        pinMode(ERROR_LED_PIN, OUTPUT);
        digitalWrite(ERROR_LED_PIN, HIGH);
        delay(ERROR_BLINK_INTERVAL_MS);
        digitalWrite(ERROR_LED_PIN, LOW);
        delay(ERROR_BLINK_INTERVAL_MS);
      }
    }
  }

  void InitShield()
  {
    for (unsigned int i = 0; i < NUM_DIGITAL_IN_PINS; i++) {
      pinMode(DIGITAL_IN_PIN_MAPPING[i], INPUT);
    }
    for (unsigned int i = 0; i < NUM_DIGITAL_OUT_PINS; i++) {
      pinMode(DIGITAL_OUT_PIN_MAPPING[i], OUTPUT);
    }
  }

  unsigned int AnalogRead(uint8_t pin)
  {
    if (pin >= NUM_ANALOG_IN_PINS) {
      Error();
    }
    return analogRead(ANALOG_IN_PIN_MAPPING[pin]);
  }

  int DigitalRead(uint8_t pin)
  {
    if (pin >= NUM_DIGITAL_IN_PINS) {
      Error();
    }

    return digitalRead(DIGITAL_IN_PIN_MAPPING[pin]);
  }

  void DigitalWrite(uint8_t pin, int state)
  {
#ifdef BB_DEBUG
    if (state != LOW && state != HIGH) {
      Error();
    }
#endif
    if (pin >= NUM_DIGITAL_OUT_PINS) {
      Error();
    }
    digitalWrite(DIGITAL_OUT_PIN_MAPPING[pin], state);
  }

  void DigitalPwmWrite(uint8_t pin, unsigned char value)
  {
    if (pin >= NUM_DIGITAL_OUT_PINS) {
      Error();
    }
#ifdef BB_DEBUG
    for (unsigned int i = 0; i < NUM_PWM_COMPATIBLE_PINS; i++) {
      if (pin == PWM_COMPATIBLE_PINS[i]) {
        analogWrite(DIGITAL_OUT_PIN_MAPPING[pin], value);
        return;
      }
    }
#else
    analogWrite(DIGITAL_OUT_PIN_MAPPING[pin], value);
#endif
    Error();
  }

  Enumeration Enumerate()
  {
    Enumeration result;
    result.total = 0;

    for (int i = 0; i < NUM_ANALOG_IN_PINS; i++) {
      if (enumerator.digitalRead(i + ANALOG_IN_PIN_OFFSET + ENUMERATOR_PIN_OFFSET)) {
        result.total++;
        result.analogIn[i] = true;
      } else {
        result.analogIn[i] = false;
      }
    }

    for (int i = 0; i < NUM_DIGITAL_IN_PINS; i++) {
      if (enumerator.digitalRead(i + DIGITAL_IN_PIN_OFFSET + ENUMERATOR_PIN_OFFSET)) {
        result.total++;
        result.digitalIn[i] = true;
      } else {
        result.digitalIn[i] = false;
      }
    }

    for (int i = 0; i < NUM_DIGITAL_OUT_PINS; i++) {
      if (enumerator.digitalRead(i + DIGITAL_OUT_PIN_OFFSET + ENUMERATOR_PIN_OFFSET)) {
        result.total++;
        result.digitalOut[i] = true;
      } else {
        result.digitalOut[i] = false;
      }
    }
    return result;
  }

  bool IsPwmCompatible(uint8_t digitalOutPin)
  {
	if (digitalOutPin >= NUM_DIGITAL_OUT_PINS) {
      Error();
    }
    for (unsigned int i = 0; i < NUM_PWM_COMPATIBLE_PINS; i++) {
      if (digitalOutPin == PWM_COMPATIBLE_PINS[i]) {
        return true;
      }
    }
    return false;
  }
}
