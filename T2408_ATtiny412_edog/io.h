#ifndef __IO_H__
#define __IO_H__

void io_initialize(void);

void io_blink_color_times(uint8_t pin, uint8_t n, uint16_t us);

void io_goto_sleep(void);

void io_power_off(void);

void io_power_on(void);

#endif