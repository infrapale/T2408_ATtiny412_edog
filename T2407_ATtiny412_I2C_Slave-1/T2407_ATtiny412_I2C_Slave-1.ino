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

uint8_t RxByte;
uint8_t tbuff[] = {0x56,0x45,0x34,0x23,0x12,0x01};

volatile main_data_st main_data;
volatile i2c_buff_st i2c_buff; 
extern cmd_data_st cmd_data[];
 
void i2c_receive_event(int rx_bytes)
{
  uint8_t msg_len = 0;
  i2c_buff.rx_indx = 0;

  // loop over each incoming byte
  for (int i = 0; i < rx_bytes; i++)
  {
    i2c_buff.rx[i2c_buff.rx_indx] = Wire.read();
    if (! msg_len) 
    { // this was the first byte of a message, 
      msg_len = cmd_get_rx_len(i2c_buff.rx[0]);
      msg_len = 5;
    }

    i2c_buff.rx_indx++; 

    if (i2c_buff.rx_indx >= msg_len) break;
  }
  for (uint8_t j=0; j < msg_len; j++) 
  {
    i2c_buff.cmd[j] = i2c_buff.rx[j];
  }
  i2c_buff.cmd_len = msg_len;       
  i2c_buff.rx_indx = 0;
  msg_len = 0;  
}

// void i2c_receive_event(int rx_bytes)
// {
//   uint8_t msg_len = 0;
//   i2c_buff.rx_indx = 0;

//   // loop over each incoming byte
//   for (int i = 0; i < rx_bytes; i++)
//   {
//     i2c_buff.rx[i2c_buff.rx_indx] = Wire.read();
//     if (! msg_len) 
//     { // this was the first byte of a message, 
//       msg_len = cmd_get_rx_len(i2c_buff.rx[0]);
//       msg_len = 5;
//     }

//     i2c_buff.rx_indx++; 

//     if (i2c_buff.rx_indx >= msg_len) 
//     {
//       for (uint8_t j=0; j < msg_len; j++) 
//       {
//         i2c_buff.cmd[j] = i2c_buff.rx[j];
//       }

//       i2c_buff.cmd_len = msg_len;       
//       i2c_buff.rx_indx = 0;
//       msg_len = 0;
//     }
//   }
  
// }
void i2c_request_event()
{
   uint8_t cmd = i2c_buff.cmd[0];
   uint8_t *data_ptr = cmd_get_data_ptr(cmd);
   uint8_t tx_len = cmd_get_tx_len(cmd); 
   uint32_t test = 0x44556677;

   buff_set_u32(i2c_buff.tx, 0, main_data.wd_interval_ms);
   //buff_set_u32(i2c_buff.tx, 0, *data_ptr);
   Wire.write((uint8_t *)i2c_buff.tx, tx_len); 
   //io_blink_color_times(PIN_PWR_OFF, cmd, 2);
   // if (tx_len > 0) Wire.write(tx_buff, tx_len); 
   
}

 
void setup() {
  main_data.wd_interval_ms = 0x4269;
  io_initialize();
  Wire.begin(I2C_ADDR); // Initialize I2C (Slave Mode)
  Wire.onRequest(i2c_request_event);
  Wire.onReceive( i2c_receive_event );
}


void loop() {

  if (i2c_buff.cmd_len > 0) 
  {
    // io_blink_color_times(PIN_PWR_OFF , i2c_buff.cmd[0]+0, 2);
    // io_blink_color_times(PIN_PWR_OFF , i2c_buff.cmd_len, 4);
    cmd_execute_cmd(i2c_buff.cmd[0]);
    i2c_buff.cmd_len = 0;

    
  }
  // io_blink_color_times(PIN_PWR_OFF , 40, 5);

  // digitalWrite(PIN_LED, HIGH);
  // delay(1000);
  // digitalWrite(PIN_LED, LOW);
  // delay(1000);
}