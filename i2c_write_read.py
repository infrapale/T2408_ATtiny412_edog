from machine import I2C
import time
import edog

#  https://www.fredscave.com/44-micropython-data-types-bytes.html


EDOG_ADDR = 0x24
sdaPIN=machine.Pin(4)
sclPIN=machine.Pin(5)
i2c=I2C(0,sda=sdaPIN, scl=sclPIN, freq=400000)
       # create I2C peripheral at frequency of 400kHz
                                # depending on the port, extra parameters may be required                                # to select the peripheral and/or pins to use

#  i2c.scan()                      # scan for peripherals, returning a list of 7-bit addresses
# bytes rxdata

def get_hex_arr_str(arr):
    return (''.join("0x%02x " % i for i in arr))

def i2c_wr_u32(addr, u32):
    # barr = addr.to_bytes(1,"big") + u32.to_bytes(4,"big")
    barr = u32.to_bytes(4,"big")
    i2c.writeto_mem(EDOG_ADDR, addr, barr)
    print("i2c_wr_u32: ", get_hex_arr_str(barr))

def i2c_rd_u32(addr):
    u32 = 0
    rx_4 = i2c.readfrom_mem(EDOG_ADDR, addr, 4)
    u32 = (rx_4[0] << 24) | (rx_4[1] << 16) |(rx_4[2] << 8) |rx_4[3] 
    print("i2c_rd_u32: ", addr, get_hex_arr_str(rx_4), u32 )
    # barr = addr.to_bytes(1,"big") + u32.to_bytes(4,"big")
    return u32
    

def i2c_wr_8_bytes(addr, arr8):
    i2c.writeto_mem(EDOG_ADDR, addr, arr8)
    print("i2c_wr_8_bytes: ", get_hex_arr_str(arr8))

def i2c_rd_8_bytes(addr):
    rx_8 = i2c.readfrom_mem(EDOG_ADDR, edog.CMD_EEPROM_READ, 8)  
    print("i2c_rd_8_bytes: ", get_hex_arr_str(rx_8))
    return rx_8

interval = 0x12345678

interval = i2c_rd_u32(edog.CMD_GET_WD_INTERVAL)
interval = interval + 0x1234
i2c_wr_u32(edog.CMD_SET_WD_INTERVAL, interval)

while (False):
    pass
    

rx_data = i2c.readfrom_mem(EDOG_ADDR, edog.CMD_GET_WD_INTERVAL, 4)        # read 4 bytes from peripheral with 7-bit address 42

i2c_wr_u32(edog.CMD_SET_WD_INTERVAL, interval)

# i2c.readfrom_mem(EDOG_ADDR, 8, 3)
print("Initial read CMD_GET_WD_INTERVAL: ", get_hex_arr_str(rx_data))

base_val = 0x00

while(True):
    b8_wr = bytearray(base_val + i for i in range(8))
    i2c_wr_8_bytes(edog.CMD_EEPROM_WRITE, b8_wr)
    # print("bytearray: ", get_hex_arr_str(b8_wr))
    time.sleep(0.1)
    base_val = base_val + 0x10
    if base_val > 0xF0:
        base_val = 0x00
    i2c.writeto_mem(EDOG_ADDR, edog.CMD_EEPROM_LOAD, b'\x00')
    time.sleep(0.1)
    b8_rd = i2c_rd_8_bytes(edog.CMD_EEPROM_READ)


while(True):
    i2c_wr_u32(edog.CMD_SET_WD_INTERVAL, interval)
    # '\x01\x12\x23\x45\x67')
    time.sleep(0.5)
    # rx_data = i2c.readfrom(EDOG_ADDR, 4)             # read 4 bytes from peripheral with 7-bit address 42
    rx_data = i2c.readfrom_mem(EDOG_ADDR, edog.CMD_GET_WD_INTERVAL, 4)        # read 4 bytes from peripheral with 7-bit address 42
    # i2c.readfrom_mem(EDOG_ADDR, 8, 3)
    print("Read CMD_GET_WD_INTERVAL: ", get_hex_arr_str(rx_data))
    time.sleep(0.1)
    rx_data = i2c.readfrom_mem(EDOG_ADDR, edog.CMD_GET_RESTARTS, 1)
    print("Read CMD_GET_RESTARTS: ", get_hex_arr_str(rx_data))
    interval = interval + 16
    time.sleep(10.0)
    
    
    
i2c.readfrom_mem(EDOG_ADDR, 8, 3)      # read 3 bytes from memory of peripheral 42,
                                #   starting at memory-address 8 in the peripheral
i2c.writeto_mem(EDOG_ADDR, 2, b'\x10') # write 1 byte to memory of peripheral 42
                                #   starting at address 2 in the peripheral
                                