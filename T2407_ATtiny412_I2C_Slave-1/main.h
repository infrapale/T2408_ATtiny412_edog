#ifndef __MAIN_H__
#define __MAIN_H__

#define PA1 (2u)
#define PA2 (3u)
#define PA3 (4u)
#define PA6 (0u)
#define PA7 (1u)

#define PIN_LED     PA3
#define PIN_PWR_OFF PA7

#define  I2C_ADDR           (0x24)
#define  I2C_RX_BUFF_SIZE   (9)
#define  I2C_TX_BUFF_SIZE   (8)

typedef struct
{
  uint32_t wd_interval_ms;
  uint32_t wd_next_hit_ms;
  uint8_t  wd_is_active;
  uint16_t eeprom_addr;
} main_data_st;

typedef struct
{
  uint8_t rx[I2C_RX_BUFF_SIZE];
  uint8_t cmd[I2C_RX_BUFF_SIZE];
  uint8_t tx[I2C_TX_BUFF_SIZE];
  uint8_t rx_indx;
  uint8_t cmd_len;
} i2c_buff_st;

#endif