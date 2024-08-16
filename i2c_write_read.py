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



interval = 0x12345678

rx_data = i2c.readfrom_mem(EDOG_ADDR, edog.CMD_GET_WD_INTERVAL, 4)        # read 4 bytes from peripheral with 7-bit address 42
# i2c.readfrom_mem(EDOG_ADDR, 8, 3)
print("Initial read CMD_GET_WD_INTERVAL: ", get_hex_arr_str(rx_data))


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
                                