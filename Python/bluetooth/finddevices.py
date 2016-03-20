#!/usr/env python

import bluetooth

nearby_devices = bluetooth.discover_devices()

for bdaddr in nearby_devices:
    name = bluetooth.lookup_name( bdaddr )
    print name , "->" , bdaddr
