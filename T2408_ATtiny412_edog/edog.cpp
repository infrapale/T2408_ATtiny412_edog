#include <Arduino.h>
#include "main.h"

#define  WD_DEFAULT_INTERVAL  10000

typedef struct
{
  uint32_t timeout_at_ms;
  uint16_t forced_reset_ms;
  uint8_t  state;
} ed_st;

extern main_data_st main_data;
extern restarts_st restarts;

ed_st ed;

void edog_clear()
{
  ed.timeout_at_ms = millis() + main_data.wd_interval_ms;
}

void edog_force_reset(uint16_t reset_duration)
{
  ed.forced_reset_ms = reset_duration;
}

void edog_initialize(void)
{
    ed.state = 0;
    ed.timeout_at_ms = millis() + WD_DEFAULT_INTERVAL;
    ed.forced_reset_ms = 0;
}

void edog_state_machine(void)
{
    switch(ed.state)
    {
      case 0:
        ed.state = 10;
        break;
      case 10:
        if (main_data.wd_is_active)
        {
          ed.state = 100;
        }
        break;  
      case 100:  // WD is active
        break;
    }
}