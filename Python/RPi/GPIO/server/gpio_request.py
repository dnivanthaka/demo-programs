#!/usr/bin/env python

import RPi.GPIO as GPIO

class GPIO_Request:
    OFF = False
    ON  = True

    MODE_OUT = GPIO.OUT
    MODE_IN  = GPIO.IN

    GPIO_0  = 3
    GPIO_1  = 5
    GPIO_4  = 7
    GPIO_7  = 26
    GPIO_8  = 24
    GPIO_9  = 21
    GPIO_10 = 19
    GPIO_11 = 23
    GPIO_14 = 8
    GPIO_15 = 10
    GPIO_17 = 11
    GPIO_18 = 12
    GPIO_21 = 13
    GPIO_22 = 15
    GPIO_23 = 16
    GPIO_24 = 18
    GPIO_25 = 22

    PORTS_LIST = [ 0, 1, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 21, 22, 23, 24, 25 ]

    def __init__(self):
        for port in self.PORTS_LIST:
            GPIO.setup( eval('self.GPIO_' + str(port)), GPIO.OUT )
            GPIO.output( eval('self.GPIO_' + str(port)), self.OFF )

    def setport_mode(self, port, state):
        GPIO.setup( eval('self.GPIO_' + str(port)), state )

    def setport_value(self, port, value):
        GPIO.output( eval('self.GPIO_' + str(port)), value )

    def getport_value(self, port):
        return GPIO.input( eval('self.GPIO_' + str(port)) )

