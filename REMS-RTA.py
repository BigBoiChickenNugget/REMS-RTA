import serial

remsPort = "/dev/ttyACM0"
rtaPort = "/dev/ttyUSB0"

REMS = serial.Serial("/dev/ttyACM0", 9600);
RTA = serial.Serial("/dev/ttyUSB0", 9600);

while True:

    remsCommand = str(REMS.readline());
    if "HEAT ON" in remsCommand:
        RTA.write(bytes("HEAT ON", "utf-8"))

    elif "HEAT OFF" in remsCommand:
        RTA.write(bytes("HEAT OFF", "utf-8"))

    if "COOL ON" in remsCommand:
        RTA.write(bytes("COOL ON", "utf-8"))

    if "COOL OFF" in remsCommand:
        RTA.write(bytes("COOL OFF", "utf-8"))

