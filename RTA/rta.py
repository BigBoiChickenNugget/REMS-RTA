import serial
import os

port = "/dev/ttyACM0"
remsCommand = serial.Serial("/dev/ttyACM0", 9600)
print(f"connected to { remsCommand.name }")

while True:
    if "TRY HEAT" in str(remsCommand.readline()):
        print("RUN HEAT");
        os.system("arduino-cli compile --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heat.ino")
        os.system("arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano ~/ArduinoRTA/heat/heat.ino")



