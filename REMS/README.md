# RTA

Webpage has checkboxes on it for now. Clicking a checkbox and clicking the corresponding button sends a POST request which the REMS Mega can read and performs actions respectively. The eventual plan is to communicate between each other through a 12 pin connector, but since that chooses to not work, at the moment I've implemented a sloppy solution where the REMS prints out commands to the serial monitor and a Python service reads those and pushes respective sketches onto the RTA. Still much development needed in that regard.
