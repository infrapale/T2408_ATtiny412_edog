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
interval = 0x02030405
cmd = edog.CMD_SET_WD_INTERVAL
b_cmd = cmd.to_bytes(1,"little")
barr = interval.to_bytes(4,"little")
print(barr)
print(edog.CMD_SET_WD_INTERVAL)
barr2 = b_cmd + barr
print(barr2)

while(True):
    i2c.writeto(EDOG_ADDR, barr2)
    # '\x01\x12\x23\x45\x67')
    time.sleep(0.5)
    # rx_data = i2c.readfrom(EDOG_ADDR, 4)             # read 4 bytes from peripheral with 7-bit address 42
    rx_data = i2c.readfrom_mem(EDOG_ADDR, edog.CMD_RD_WD_INTERVAL, 4)        # read 4 bytes from peripheral with 7-bit address 42
    # i2c.readfrom_mem(EDOG_ADDR, 8, 3)
    print(rx_data)
    time.sleep(1.0)
    
i2c.readfrom_mem(EDOG_ADDR, 8, 3)      # read 3 bytes from memory of peripheral 42,
                                #   starting at memory-address 8 in the peripheral
i2c.writeto_mem(EDOG_ADDR, 2, b'\x10') # write 1 byte to memory of peripheral 42
                                #   starting at address 2 in the peripheral