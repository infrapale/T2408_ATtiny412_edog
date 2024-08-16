#include "Arduino.h"
#include <Wire.h>
#include "main.h"
#include "cmd.h"
#include "io.h"
#include "buff.h"
#include "eep.h"
//#include "ee_prom.h"
//#include "helper.h"

uint8_t dummy_byte;
extern volatile main_data_st main_data;
extern volatile i2c_buff_st i2c_buff;

const cmd_data_st cmd_data[CMD_NBR_OF] = 
{ //                       TX RX  Ptr
  [CMD_WD_UNDEF]        = { 0, 0, &dummy_byte},
  [CMD_SET_WD_INTERVAL] = { 0, 4, (uint8_t *)&main_data.wd_interval_ms},
  [CMD_GET_WD_INTERVAL] = { 4, 0, (uint8_t *)&main_data.wd_interval_ms},
  [CMD_SET_SLEEP_TIME]  = { 0, 4, &dummy_byte},
  [CMD_GET_SLEEP_TIME]  = { 4, 0, &dummy_byte},
  [CMD_CLEAR_WATCHDOG]  = { 0, 0, &dummy_byte},
  [CMD_SWITCH_OFF]      = { 0, 0, &dummy_byte},
  [CMD_SET_EEPROM_ADDR] = { 2, 0, (uint8_t *)&main_data.eeprom_addr},
  [CMD_EEPROM_LOAD]     = { 0, 0, &dummy_byte},
  [CMD_EEPROM_SAVE]     = { 0, 0, &dummy_byte},
  [CMD_POWER_OFF_0]     = { 0, 0, &dummy_byte},
  [CMD_EXT_RESET]       = { 0, 0, &dummy_byte},
  [CMD_EEPROM_READ]     = { 0, 8, &dummy_byte},
  [CMD_EEPROM_WRITE]    = { 8, 0, &dummy_byte},
  [CMD_GET_RESTARTS]    = { 1, 0, (uint8_t *)&main_data.nbr_restarts},
};

uint8_t cmd_get_rx_len(uint8_t cmd)
{
  uint8_t len = 0;
  if (cmd < CMD_NBR_OF) len = cmd_data[cmd].rx_bytes;
  return len;
}
uint8_t cmd_get_tx_len(uint8_t cmd)
{
  uint8_t len = 0;
  if (cmd < CMD_NBR_OF) len = cmd_data[cmd].tx_bytes;
  return len;
}

uint8_t *cmd_get_data_ptr(uint8_t cmd)
{
  uint8_t *ptr = NULL;
  if (cmd < CMD_NBR_OF) ptr = cmd_data[cmd].data;
  return ptr;
}


void cmd_execute_cmd(uint8_t cmd)
{
  // io_blink_color_times(PIN_PWR_OFF, cmd, 2);
  switch(cmd)
  {
    case CMD_WD_UNDEF:
      break;
    case CMD_SET_WD_INTERVAL:
      main_data.wd_interval_ms = buff_get_u32((uint8_t*)i2c_buff.cmd, 1);
      //uint32_t buff_get_u32(uint8_t *buff, uint8_t indx)
      eep_req_save(EEPROM_MAIN_DATA);
      break;
    case CMD_GET_WD_INTERVAL:
      break;
    case CMD_SET_SLEEP_TIME:
      break;
    case CMD_GET_SLEEP_TIME:
      break; 
    case CMD_CLEAR_WATCHDOG:
      break;
    case CMD_SWITCH_OFF:
      break; 
    case CMD_SET_EEPROM_ADDR:
      break;
    case CMD_EEPROM_LOAD:
      break;   
    case CMD_EEPROM_SAVE:
      break;    
    case CMD_POWER_OFF_0:
      break; 
    case CMD_EXT_RESET:
      break;  
    case CMD_EEPROM_READ:
      break; 
    case CMD_EEPROM_WRITE:
      break; 
    case CMD_GET_RESTARTS:
      break; 

  }
}

void cmd_get_data(uint8_t cmd)
{
  uint8_t tx_len = 0;
  switch(cmd)
  {
    case CMD_WD_UNDEF:
      break;
    case CMD_SET_WD_INTERVAL:
       break;
    case CMD_GET_WD_INTERVAL:
      buff_set_u32((uint8_t*)i2c_buff.tx, 0, main_data.wd_interval_ms);  
      // buff_set_u32((uint8_t*)i2c_buff.tx, 0, 0x11223344);  
      tx_len = 4;  
      break;
    case CMD_SET_SLEEP_TIME:
      break;
    case CMD_GET_SLEEP_TIME:
      buff_set_u32((uint8_t*)i2c_buff.tx, 0, main_data.wd_interval_ms);  
      tx_len = 4;  
      break;
    case CMD_CLEAR_WATCHDOG:
      break;
    case CMD_SWITCH_OFF:
      break; 
    case CMD_SET_EEPROM_ADDR:
      break;
    case CMD_EEPROM_LOAD:
      break;   
    case CMD_EEPROM_SAVE:
      break;    
    case CMD_POWER_OFF_0:
      break; 
    case CMD_EXT_RESET:
      break;  
    case CMD_EEPROM_READ:
      break; 
    case CMD_EEPROM_WRITE:
      break; 
    case CMD_GET_RESTARTS:
      i2c_buff.tx[0] = main_data.nbr_restarts; 
      tx_len = 1;  

      break; 
  }

    if (tx_len > 0)
    {
      Wire.write((uint8_t *)i2c_buff.tx, tx_len); 
    }
   //io_blink_color_times(PIN_PWR_OFF, cmd, 2);
}