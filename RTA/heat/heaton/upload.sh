#!/bin/bash

arduino-cli compile --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heaton/heaton.ino
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heaton/heaton.ino
