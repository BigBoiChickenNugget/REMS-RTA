import serial

remsPort = "/dev/ttyACM0"
rtaPort = "/dev/ttyUSB0"

REMS = serial.Serial("/dev/ttyACM0", 9600);
RTA = serial.Serial("/dev/ttyUSB0", 9600);

while True:

    remsCommand = str(REMS.readline());
    if "HEAT ON" in remsCommand:
        print("HEAT");
        RTA.write(bytes("A", "utf-8"))

    elif "HEAT OFF" in remsCommand:
        print("NO HEAT")
        RTA.write(bytes("B", "utf-8"))

    if "COOL ON" in remsCommand:
        print("COOL");
        RTA.write(bytes("C", "utf-8"))

    if "COOL OFF" in remsCommand:
        print("COOL OFF");
        RTA.write(bytes("D", "utf-8"))

