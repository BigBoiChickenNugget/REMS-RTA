# REMS-RTA

### Description

The Remote Environment Management System (REMS) is a system used to monitor and control the environment of a living location. The REMS Testing Application (RTA) is meant to simulate an actual living environment by receiving commands from the REMS board to activate or deactivate specific loads attached to the RTA and monitor the response of the REMS board in return. For a working example, consider that we wish to turn up the heat with the REMS board. The REMS board sends a command to turn on a "furnace" load attached to the RTA. The RTA then turns on the "furnace" load and then we're able to monitor the heat increase in the living location with the REMS board.

### Brief Overview of Format

The REMS board has been tested with a variety of different microcontrollers. Currently, the ESP32 with a W5500 to activate a webserver has been the most successful. The RTA board is currently an Arduino Nano. The REMS board sends commands to the RTA by sending a series of 1s or 0s to pins connected with the RTA. We ran into problems with the RTA board not being able to read 1s or 0s on those respective pins, so a temporary workaround was the REMS-RTA Python script. This script reads serial messages printed on the REMS board and prints the same message to the RTA board. The RTA board then reads the message and activates the respective load. While this is not an ideal solution due to the overhead and latency of the Python script, it allows the board to be functional until we can find a better solution.

### Installation

1. Clone the repository.
2. Install the required Arduino libraries.
3. Upload the `RTA.ino` file to the Arduino Nano.
4. Upload the respective board code to the microcontroller of choice.

