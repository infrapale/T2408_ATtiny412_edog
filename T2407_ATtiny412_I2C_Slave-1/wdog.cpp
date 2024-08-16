#include <Arduino.h>
#include "main.h"

#define  WD_DEFAULT_INTERVAL  10000

typedef struct
{
  uint32_t timeout_at_ms;
  uint16_t forced_reset_ms;
  uint8_t  state;
} wd_st;

extern main_data_st main_data;
extern restarts_st restarts;

wd_st wd;

void wdog_clear()
{
  wd.timeout_at_ms = millis() + main_data.wd_interval_ms;
}

void wdog_initialize(void)
{
    wd.state = 0;
    wd.timeout_at_ms = millis() + WD_DEFAULT_INTERVAL;
}

void wdog_state_machine(void)
{
    switch(wd.state)
    {
      case 0:
        wd.state = 10;
        break;
      case 10:
        if (main_data.wd_is_active)
        {
          wd.state = 100;
        }
        break;  
      case 100:  // WD is active
        break;
    }
}