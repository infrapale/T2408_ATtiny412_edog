#include "Arduino.h"
#include "main.h"
#include "io.h"

  void io_initialize(void)
  {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_PWR_OFF_0, OUTPUT);
    pinMode(PIN_PWR_OFF_1, OUTPUT);
    digitalWrite(PIN_PWR_OFF_0, LOW);
    digitalWrite(PIN_PWR_OFF_1, LOW);
  }

void io_blink_color_times(uint8_t pin, uint8_t n, uint16_t us)
{
  for (uint8_t i=0; i < n; i++)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(us);
    digitalWrite(pin, LOW);
    delayMicroseconds(us);
  }
}

void io_goto_sleep(void)
{
    // cntrl.sleep_state = SLEEP_STATE_CLOSING;
}

void io_power_off(void)
{
    digitalWrite(PIN_PWR_OFF_0, HIGH);
    #ifdef OPTION_COMBINED_CONTROL
      // digitalWrite(PIN_PWR_OFF_1, HIGH);
      digitalWrite(PIN_EXT_RESET, HIGH);
    #endif
}

void io_power_on(void)
{
    digitalWrite(PIN_PWR_OFF_0, LOW);
    #ifdef OPTION_COMBINED_CONTROL
      // digitalWrite(PIN_PWR_OFF_1, LOW);
      digitalWrite(PIN_EXT_RESET, LOW);
    #endif
}
