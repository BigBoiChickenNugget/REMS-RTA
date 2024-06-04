import serial
import os

port = "/dev/ttyACM0"
remsCommand = serial.Serial("/dev/ttyACM0", 9600)
print(f"connected to { remsCommand.name }")

while True:

    if "HEAT ON" in str(remsCommand.readline()):
        print("HEAT ON");
        os.system("arduino-cli compile --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heaton/heaton.ino")
        os.system("arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heaton/heaton.ino")

    elif "HEAT OFF" in str(remsCommand.readline()):
        print("HEAT OFF")
        os.system("arduino-cli compile --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heatoff/heatoff.ino")
        os.system("arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heatoff/heatoff.ino")
