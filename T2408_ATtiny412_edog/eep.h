/*
my_eeprom  
EEPROM Memory Map and Functions

https://docs.arduino.cc/learn/built-in-libraries/eeprom/

*/


#ifndef __MY_EEPROM_H__
#define __MY_EEPROM_H__

#define ATTINY412_EEPROM_SIZE 128

#define EEPROM_ADDR_MAIN_DATA     0x00
#define EEPROM_ADDR_RESTARTS      0x20
#define EEPROM_ADDR_1             0x30
#define EEPROM_ADDR_2             0x40

typedef enum
{
  EEPROM_MAIN_DATA     = 0,
  EEPROM_RESTARTS,
  EEPROM_NBR_OF
 } eeprom_index_et;

void epp_initialize_data(void);

void eep_req_save(uint8_t eep_indx);

void eep_time_machine(void);


#endif
