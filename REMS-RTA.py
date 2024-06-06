# Import the serial library for communication with the serial monitors.
import serial

# Ports on which the REMS and RTA Arduinos are.
rems1Port = "/dev/ttyACM0"
rems2Port = "/dev/ttyACM1"
rtaPort = "/dev/ttyUSB0"

# Open a serial connection with the RTA and REMS.
REMS1 = serial.Serial("/dev/ttyACM0", 9600);
REMS2 = serial.Serial("/dev/ttyACM1", 9600);
RTA = serial.Serial("/dev/ttyUSB0", 9600);

# Keep running.
while True:

    # Read the incoming commands from the REMS serial monitor.
    remsCommand = str(REMS1.readline());

    # If the user wants the heat to be on, print 'A' to the RTA serial monitor.
    if "HEAT ON" in remsCommand:
        print("HEAT");
        RTA.write(bytes("A", "utf-8"))

        # If the user wants the heat to be off, print 'B' to the RTA serial monitor.
    elif "HEAT OFF" in remsCommand:
        print("NO HEAT")
        RTA.write(bytes("B", "utf-8"))

    # If the user wants the cooling to be on, print 'C' to the RTA serial monitor.
    if "COOL ON" in remsCommand:
        print("COOL");
        RTA.write(bytes("C", "utf-8"))

    # If the user wants the cooling to be off, print 'D' to the RTA serial monitor.
    if "COOL OFF" in remsCommand:
        print("COOL OFF");
        RTA.write(bytes("D", "utf-8"))

