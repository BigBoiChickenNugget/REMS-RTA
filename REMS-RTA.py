# Import the serial library for communication with the serial monitors.
import serial

# Ports on which the REMS and RTA Arduinos are.
rems1Port = "/dev/ttyACM0"
#rems2Port = "/dev/ttyACM1"
rtaPort = "/dev/ttyUSB1"

# Open a serial connection with the RTA and REMS.
#REMS1 = serial.Serial("/dev/ttyACM0", 9600)
REMS2 = serial.Serial("/dev/ttyACM1", 9600)
#RTA1 = serial.Serial("/dev/ttyUSB0", 9600)
RTA2 = serial.Serial("/dev/ttyUSB1", 9600)

# Keep running.
while True:

    # Read the incoming commands from the REMS serial monitor.
    rems1Command = "hello" #str(REMS1.readline())
    rems2Command = str(REMS2.readline())

    # If the user wants the heat to be on, print 'A' to the RTA serial monitor.
    if "HEAT ON" in rems1Command:
        print("HEAT");
        RTA1.write(bytes("A", "utf-8"))

        # If the user wants the heat to be off, print 'B' to the RTA serial monitor.
    elif "HEAT OFF" in rems1Command:
        print("NO HEAT")
        RTA1.write(bytes("B", "utf-8"))

    # If the user wants the cooling to be on, print 'C' to the RTA serial monitor.
    if "COOL ON" in rems1Command:
        print("COOL");
        RTA1.write(bytes("C", "utf-8"))

    # If the user wants the cooling to be off, print 'D' to the RTA serial monitor.
    if "COOL OFF" in rems1Command:
        print("COOL OFF");
        RTA1.write(bytes("D", "utf-8"))

    # If the user wants the heat to be on, print 'A' to the RTA serial monitor.
    if "HEAT ON" in rems2Command:
        print("HEAT");
        RTA2.write(bytes("A", "utf-8"))

        # If the user wants the heat to be off, print 'B' to the RTA serial monitor.
    elif "HEAT OFF" in rems2Command:
        print("NO HEAT")
        RTA2.write(bytes("B", "utf-8"))

    # If the user wants the cooling to be on, print 'C' to the RTA serial monitor.
    if "COOL ON" in rems2Command:
        print("COOL");
        RTA2.write(bytes("C", "utf-8"))

    # If the user wants the cooling to be off, print 'D' to the RTA serial monitor.
    if "COOL OFF" in rems2Command:
        print("COOL OFF");
        RTA2.write(bytes("D", "utf-8"))
