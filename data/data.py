import serial
import os
import time

# Ports on which the REMS and RTA Arduinos are.
rems1Port = "/dev/ttyACM0"
rems2Port = "/dev/ttyACM1"
rems3Port = "/dev/ttyUSB1"

while True:
    # Open the serial ports
    rems1 = serial.Serial(rems1Port, 9600)
    rems2 = serial.Serial(rems2Port, 9600)
    rems3 = serial.Serial(rems3Port, 9600)

    # Read the data from the serial ports
    rems1Data = rems1.readline()
    rems2Data = rems2.readline()
    rems3Data = rems3.readline()

    # Write the data to the file
    with open("rems1.txt", "a") as f:
        f.write(rems1Data)
    with open("rems2.txt", "a") as f:
        f.write(rems2Data)
    with open("rems3.txt", "a") as f:
        f.write(rems3Data)

    # Wait for 10 seconds
    time.sleep(10)
