#include "Arduino.h"
#include "main.h"
#include "cmd.h"
#include "io.h"
#include "buff.h"
//#include "ee_prom.h"
//#include "helper.h"

uint8_t dummy_byte;
extern volatile main_data_st main_data;
extern volatile i2c_buff_st i2c_buff;

const cmd_data_st cmd_data[CMD_NBR_OF] = 
{ //                       TX RX  Ptr
  [CMD_WD_UNDEF]        = { 0, 0, &dummy_byte},
  [CMD_SET_WD_INTERVAL] = { 0, 4, (uint8_t *)&main_data.wd_interval_ms},
  [CMD_RD_WD_INTERVAL]  = { 4, 0, (uint8_t *)&main_data.wd_interval_ms},
  [CMD_SET_SLEEP_TIME]  = { 0, 4, &dummy_byte},
  [CMD_RD_SLEEP_TIME]   = { 4, 0, &dummy_byte},
  [CMD_CLEAR_WATCHDOG]  = { 0, 0, &dummy_byte},
  [CMD_SWITCH_OFF]      = { 0, 0, &dummy_byte},
  [CMD_SET_EEPROM_ADDR] = { 2, 0, (uint8_t *)&main_data.eeprom_addr},
  [CMD_EEPROM_LOAD]     = { 0, 0, &dummy_byte},
  [CMD_EEPROM_SAVE]     = { 0, 0, &dummy_byte},
  [CMD_POWER_OFF_0]     = { 0, 0, &dummy_byte},
  [CMD_EXT_RESET]       = { 0, 0, &dummy_byte},
  [CMD_EEPROM_READ]     = { 0, 8, &dummy_byte},
  [CMD_EEPROM_WRITE]    = { 8, 0, &dummy_byte},
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
  io_blink_color_times(PIN_PWR_OFF, cmd, 2);
  switch(cmd)
  {
    case CMD_WD_UNDEF:
      break;
    case CMD_SET_WD_INTERVAL:
      main_data.wd_interval_ms = buff_get_u32(i2c_buff.cmd, 1);
       break;
    case CMD_RD_WD_INTERVAL:
      break;
    case CMD_SET_SLEEP_TIME:
      break;
    case CMD_RD_SLEEP_TIME:
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

  }
}