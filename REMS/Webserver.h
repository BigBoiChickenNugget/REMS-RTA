/*
   Webserver.h - Library for creating a webserver for the REMS homepage.
*/

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Ethernet.h>
#include "Arduino.h"

// Pins for making heating and cooling requests.
#define HEATREQUEST 31
#define COOLREQUEST 35

// Pins on which the sound sensors are.
#define SOUNDSENSOR1 23
#define SOUNDSENSOR2 25
#define SOUNDSENSOR3 27
#define SOUNDSENSOR4 23

// Pins on which the motion sensors are.
#define MOTIONSENSOR1 30
#define MOTIONSENSOR2 32
#define MOTIONSENSOR3 34
#define MOTIONSENSOR4 36

// Pin to receive smoke alarm on signal from RTA.
#define SMOKEALARM 43

// Pin to shut power off.
#define POWERSHUTOFF 21

// Pin to shut water off.
#define WATERSHUTOFF 33


// Temperature pins setup.
#define ONE_WIRE_BUS_1 37
#define ONE_WIRE_BUS_2 39
#define ONE_WIRE_BUS_3 41

class Webserver
{
    public:
	Webserver();
	void ClientResponse(EthernetClient client);
	void RTACommand(EthernetClient client);
	boolean searchResponse(String data, String key);
	boolean readRequest(EthernetClient client);
    private:
	EthernetClient _client;
	String _data;
	String _key;
}

#endif
