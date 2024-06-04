#!/bin/bash

arduino-cli compile --fqbn arduino:avr:nano ~/ArduinoRTA/cool/coolon/coolon.ino
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano ~/ArduinoRTA/cool/coolon/coolon.ino
