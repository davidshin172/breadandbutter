#include <BreadAndButter.h>
#include <SPI.h> // MCP23S17 dependency
#include <MCP23S17.h> // BreadAndButter dependency

using namespace BreadAndButter;

void setup() {
  InitShield();
  Serial.begin(9600);
}

void loop() {
  Enumeration result = Enumerate();
  Serial.print("Total Connected: ");
  Serial.println(result.total);

  Serial.print("AI: ");
  for (unsigned int i = 0; i < NUM_ANALOG_IN_PINS; i++) {
    if (result.analogIn[i]) {
      Serial.print(i);
      Serial.print(" ");
    }
  }
  Serial.println("");
  Serial.print("DI: ");
  for (unsigned int i = 0; i < NUM_DIGITAL_IN_PINS; i++) {
    if (result.digitalIn[i]) {
      Serial.print(i);
      Serial.print(" ");
    }
  }
  Serial.println("");
  Serial.print("DO: ");
  for (unsigned int i = 0; i < NUM_DIGITAL_OUT_PINS; i++) {
    if (result.digitalOut[i]) {
      Serial.print(i);
      Serial.print(" ");
    }
  }
  Serial.println("");
  delay(1000);
}
