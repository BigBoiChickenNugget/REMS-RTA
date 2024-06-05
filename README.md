# REMS-RTA

This program consists of two different Arduinos: A Mega representing the REMS (Remote Environment Management System), and a Nano representing the RTA (REMS Testing Application).

The REMS primarily consists of a webpage that sends requests to the RTA (turn on light, turn on cool, etc.).

### To-do:
- Lots of stuff, but mainly make the REMS-RTA.py a service. I don't have experience with systemd services though, so not sure how well it'll go.
- Also create a system to automate multiple RTAs. Right now the RTA port is hardcoded, but I'd like to create a system where multiple RTAs are accounted for automatically.
