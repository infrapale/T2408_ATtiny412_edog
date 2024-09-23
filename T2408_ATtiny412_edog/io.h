#ifndef __IO_H__
#define __IO_H__

/**********************************************************************
  IO Definitions and Functions
***********************************************************************
                ---------------------
                |                   |
    3.3-5V    --| (1) VDD   GND (8) |-- GND
                |                   |
    PWR_OFF_0 --| (2) PA6   PA3 (7) |-- LED
                |                   |
    PWR_OFF_1 --| (3) PA7   PA0 (6) |-- UPDI
                |                   |
    I2C SDA   --| (4) PA1   PA2 (5) |-- I2C SCL
                |                   |
                ---------------------
                                               
**********************************************************************/


#define PA1 (2u)
#define PA2 (3u)
#define PA3 (4u)
#define PA6 (0u)
#define PA7 (1u)

#define PIN_I2C_SDA         PA1
#define PIN_I2C_SCL         PA2

#define PIN_LED             PA3
#define PIN_PWR_OFF_0       PA6
#define PIN_PWR_OFF_1       PA7


void io_initialize(void);

void io_blink_color_times(uint8_t pin, uint8_t n, uint16_t us);

void io_goto_sleep(void);

void io_power_off(void);

void io_power_on(void);

#endif