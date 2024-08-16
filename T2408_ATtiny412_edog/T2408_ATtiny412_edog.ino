/*******************************************************************************

VDD       | 1    8| GND
TXD (PA6) | 2    7| (PA3) LED
RXD (PA7) | 3    6| (PA0) UPDI
SDA (PA1) | 4    5| (PA2) SCL

-------------------------------------------------------------------------------/
https://wiki-content.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter
https://inductive-kickback.com/2019/04/creating-an-i2c-slave-interface-for-a-sensor-or-peripheral/


*******************************************************************************/

#include "main.h"
#include <Wire.h>
#include "cmd.h"
#include "io.h"
#include "buff.h"
#include "eep.h"
#include <EEPROM.h>

uint8_t RxByte;
uint8_t tbuff[] = {0x56,0x45,0x34,0x23,0x12,0x01};

main_data_st main_data;
volatile i2c_buff_st i2c_buff; 
restarts_st restarts;

extern cmd_data_st cmd_data[];

uint32_t next_task_run_ms = 0;


void i2c_receive_event(int rx_bytes)
{
  uint8_t msg_len = 0;
  i2c_buff.rx_indx = 0;

  for (int i = 0; i < rx_bytes; i++)
  {
    i2c_buff.rx[i2c_buff.rx_indx] = Wire.read();
    i2c_buff.rx_indx++; 

    if (i2c_buff.rx_indx >= I2C_RX_BUFF_SIZE) break;
  }
  msg_len = rx_bytes;
  for (uint8_t i=0; i < msg_len; i++) 
  {
    i2c_buff.cmd[i] = i2c_buff.rx[i];
  }
  i2c_buff.cmd_len = msg_len;       
  i2c_buff.rx_indx = 0;
}


void i2c_request_event()
{
   uint8_t cmd = i2c_buff.cmd[0];
   cmd_get_data(cmd);
   
   
}

 
void setup() {
  main_data.wd_interval_ms = 0x4269;
  epp_initialize_data();
  next_task_run_ms = millis() + 1000;
  main_data.nbr_restarts = EEPROM.read(1);
  main_data.nbr_restarts++;
  EEPROM.write(1, main_data.nbr_restarts);
  io_initialize();
  io_blink_color_times(PIN_PWR_OFF , main_data.nbr_restarts, 2);
  Wire.begin(I2C_ADDR); // Initialize I2C (Slave Mode)
  Wire.onRequest(i2c_request_event);
  Wire.onReceive( i2c_receive_event );
}


void loop() {
  if (i2c_buff.cmd_len > 0) 
  {
    // io_blink_color_times(PIN_PWR_OFF , i2c_buff.cmd_len, 4);
    cmd_execute_cmd(i2c_buff.cmd[0]);
    i2c_buff.cmd_len = 0;
  }
  if(millis() > next_task_run_ms){
    next_task_run_ms = millis() + 1000;
    eep_time_machine();
  }

}