#!/usr/bin/env python

from gpio_request import GPIO_Request
import time

gp = GPIO_Request()
gp.setport_mode( 0, GPIO_Request.MODE_IN )
while True:
    '''gp.setport_value(0, GPIO_Request.ON)
    time.sleep(1)
    gp.setport_value(0, GPIO_Request.OFF)
    time.sleep(1)'''
    print gp.getport_value(0)
    time.sleep(1)
