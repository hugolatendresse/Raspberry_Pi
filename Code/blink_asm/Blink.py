#!/usr/bin/env python3
########################################################################
# Filename    : Blink.py
# Description : Basic usage of GPIO. Let led blink.
# auther      : www.freenove.com
# modification: 2019/12/28
########################################################################
import RPi.GPIO as GPIO
import time

ledPin = 11    # define ledPin

def setup():
    GPIO.setmode(GPIO.BOARD)       # use PHYSICAL GPIO Numbering
    GPIO.setup(ledPin, GPIO.OUT)   # set the ledPin to OUTPUT mode
    GPIO.output(ledPin, GPIO.LOW)  # make ledPin output LOW level 
    print ('using pin%d'%ledPin)


def print_address(address):
    import mmap
    import os

    # Check the system's page size
    page_size = os.sysconf('SC_PAGE_SIZE')
    print("Page size:", page_size)
    
    # Ensure the offset is a multiple of the page size
    aligned_address = address - (address % page_size)
    
    # Now use aligned_address in mmap
    print("tentative address:", address)
    print("aligned_address:", aligned_address)
    aligned_address = address
    # Open /dev/mem
    fd = os.open('/dev/mem', os.O_RDWR | os.O_SYNC)
    
    # Constants
    size = 4  # We are reading a 32-bit integer
    
    # Memory map the address
    mem = mmap.mmap(fd, size, mmap.MAP_SHARED, mmap.PROT_READ | mmap.PROT_WRITE, offset=address)
    
    # Read the 32-bit value
    value = int.from_bytes(mem.read(size), byteorder='little')
    
    # Clean up
    mem.close()
    os.close(fd)
    print(f"The 32-bit value at address {hex(address)} is: {value}")

def p_all():
    print_address(0x7e2000e8)
    print_address(0x47e2000e8)
    print_address(0x4C02000e8)


def loop():
    while True:
        GPIO.output(ledPin, GPIO.LOW)  # make ledPin output LOW level to turn on led
        print ('led turned on >>>')     # print information on terminal
        p_all()
        time.sleep(1)                   # Wait for 1 second
        GPIO.output(ledPin, GPIO.HIGH)   # make ledPin output HIGH level to turn off led
        print ('led turned off <<<')
        time.sleep(1)                   # Wait for 1 second
        p_all()

def destroy():
    GPIO.cleanup()                      # Release all GPIO

if __name__ == '__main__':    # Program entrance
    print ('Program is starting ... \n')
    setup()
    try:
        loop()
    except KeyboardInterrupt:   # Press ctrl-c to end the program.
        destroy()

