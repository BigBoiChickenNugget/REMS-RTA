// Libraries for Ethernet connection.
#include "../Webserver.h"

// Libraries for temperature sensors (need to implement).
#include <OneWire.h>
#include <DallasTemperature.h>


OneWire onewire_1(ONE_WIRE_BUS_1);
OneWire onewire_2(ONE_WIRE_BUS_2);
OneWire onewire_3(ONE_WIRE_BUS_3);

DallasTemperature sensor_1(&onewire_1);
DallasTemperature sensor_2(&onewire_2);
DallasTemperature sensor_3(&onewire_3);

// Mac address of Arduino REMS board.
byte mac[] = {
    0x2C, 0xF7, 0xF1, 0x08, 0x33, 0x4E
};

// IP address for the webpage.
IPAddress ip(192, 168, 3, 160);

EthernetServer server(80);

// String that'll store the response from the webpage.
String httpResponse;

void setup() {

    // Begin serial monitor.
    Serial.begin(9600);

    // Start webserver.
    Ethernet.begin(mac, ip);
    server.begin();

    // Setup all pins.
    pinMode(HEATREQUEST, OUTPUT);
    pinMode(COOLREQUEST, OUTPUT);
    digitalWrite(HEATREQUEST, HIGH);
    digitalWrite(COOLREQUEST, HIGH);

    pinMode(SOUNDSENSOR1, INPUT);
    pinMode(SOUNDSENSOR2, INPUT);
    pinMode(SOUNDSENSOR3, INPUT);
    pinMode(SOUNDSENSOR4, INPUT);

    pinMode(MOTIONSENSOR1, INPUT);
    pinMode(MOTIONSENSOR2, INPUT);
    pinMode(MOTIONSENSOR3, INPUT);
    pinMode(MOTIONSENSOR4, INPUT);

    pinMode(SMOKEALARM, INPUT);

    pinMode(POWERSHUTOFF, OUTPUT);
    digitalWrite(POWERSHUTOFF, HIGH);

    pinMode(WATERSHUTOFF, OUTPUT);
    digitalWrite(WATERSHUTOFF, HIGH);

    // Start temperature sensors.
    sensor_1.begin();
    sensor_2.begin();
    sensor_3.begin();
}

void loop() {


    // Listen for incoming clients.
    EthernetClient client = server.available();

    // If a client is found...
    if (client) {

	// If the client is availalble, read the incoming HTTP request.
	if (client.available()) {

	    // Calls a function to read the HTTP request and stores it in the httpResponse global String.
	    boolean request = readRequest(client);

	    // Displays the updated webpage in line with the request, and sends whatever commands the HTTP request asked to do.
	    ClientResponse(client);

	    if (request) {
		Serial.println("GOING THROUGH");
		client.println("TESTING 1 2 3");
		RTACommand(client);
	    }
	    else {
		client.println("FIRST TEST");
		Serial.println("  HEAT OFF  ");
		Serial.println("  COOL OFF  ");
	    }

	    // End html
	    client.println("</body>");
	    client.println("</html>");

	    httpResponse = "";

	    delay(1);
	    client.stop();
	}
    }
}
