#include <Arduino.h>
#include "main.h"
#include <EEPROM.h>
#include "eep.h"

#define EEP_SAVE_INTERVAL_ms   1000
#define EEP_CNTR_START            4

typedef struct
{
  uint8_t  addr;
  uint8_t  save_cntr ;
} eep_st;

eep_st eep[EEPROM_NBR_OF] =
{
  [EEPROM_MAIN_DATA]  = {EEPROM_ADDR_MAIN_DATA, 0},
  [EEPROM_RESTARTS]   = {EEPROM_ADDR_RESTARTS, 0},
};

uint32_t next_run = 0;

extern main_data_st main_data;
extern restarts_st restarts;

void epp_initialize_data(void)
{
  for(uint8_t i = 0; i < EEPROM_NBR_OF; i++)
  {
    eep[i].save_cntr = EEP_CNTR_START;
  }
  next_run = millis() + EEP_SAVE_INTERVAL_ms;
  EEPROM.get(EEPROM_ADDR_MAIN_DATA, main_data);
  EEPROM.get(EEPROM_ADDR_RESTARTS, restarts);
}

void eep_req_save(uint8_t eep_indx)
{
  eep[eep_indx].save_cntr = EEP_CNTR_START;
}

void eep_time_machine(void)
{
  if (millis() > next_run)
  {
    next_run = millis() + EEP_SAVE_INTERVAL_ms; 
    for(uint8_t indx = 0; indx < EEPROM_NBR_OF; indx++)
    {
      if (eep[indx].save_cntr == 1 )
      {
          eep[indx].save_cntr = 0;
          switch(indx)
          {
            case EEPROM_MAIN_DATA:
              EEPROM.put(EEPROM_ADDR_MAIN_DATA, main_data);
              break;
            case EEPROM_RESTARTS:
              EEPROM.put(EEPROM_ADDR_RESTARTS, restarts);
              break;
          } 
      }
      else
      {
        eep[indx].save_cntr--;
      }  
    }
  }  
}
