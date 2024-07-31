// Libraries for Ethernet connection.
#include <SPI.h>
#include <Ethernet.h>

// Libraries for temperature sensors (need to implement).
#include <OneWire.h>
#include <DallasTemperature.h>

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

OneWire onewire_1(ONE_WIRE_BUS_1);
OneWire onewire_2(ONE_WIRE_BUS_2);
OneWire onewire_3(ONE_WIRE_BUS_3);

DallasTemperature sensor_1(&onewire_1);
DallasTemperature sensor_2(&onewire_2);
DallasTemperature sensor_3(&onewire_3);

#define GAS1 A7
#define GAS2 A8

// Mac address of Arduino REMS board.
byte mac[] = {
    0x2C, 0xF7, 0xF1, 0x08, 0x55, 0x4E
};

// IP address for the webpage.
IPAddress ip(192, 168, 3, 165);

EthernetServer server(80);

// String that'll store the response from the webpage.
String httpResponse;

// Array to store status of buttons. Order is heat, cool, power, water.
boolean status[] = {false, false, false, false};

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
	    readRequest(client);

	    // Displays the updated webpage in line with the request, and sends whatever commands the HTTP request asked to do.
	    ClientResponse(client);

	    delay(1);
	    client.stop();
	}
    }
}

// Function to display entire webpage and process the HTTP request.
void ClientResponse(EthernetClient client) {

    // Send http request.
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    // Begin HTML
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    // Code for the head portion of the webpage
    client.println("<head>");
    client.println("<title>REMS Gas Test</title>");

    client.println("</head>");

    // Start body portion of site. Header that has site label.
    client.println("<body>");
    client.println("<h1>REMS006 Gas Test</h1>");
    client.println("<h4>192.168.3.165</h4>");

	int gas1 = analogRead(GAS1);
	int gas2 = analogRead(GAS2);
	int random = analogRead(A3);
	int random2 = analogRead(A3);
	client.println("<p>" + String(gas1) + " A0 pin input (main reading)</p>");
	client.println("<p>" + String(gas2) + " En pin input</p>");
	client.println("<p>" + String(random) + " Random analog pin (ensure readings are different from A0 pin)</p>");
	client.println("<p>" + String(random2) + " Random analog pin (ensure readings are different from A0 pin)</p>");
}

//  Function that reads the incoming HTTP request.
void readRequest(EthernetClient client) {

    // Boolean variable to store if the request is POST (sending states of buttons).
    httpResponse = "";

    char c = client.read();

    // Iterate through all the strings until the newline appears (in the case of a GET request) or until the line with all the checkbox statuses appears (in the case of a POST request).
    while (c != '\n') {
	httpResponse += c;
	c = client.read();
    }

    if (httpResponse.indexOf("?heatrequest") >= 0) {
	status[0] = !status[0];
    }
    if (httpResponse.indexOf("?coolrequest") >= 0) {
	status[1] = !status[1];
    }
    if (httpResponse.indexOf("?powerOff") >= 0) {
	status[2] = !status[2];
    }
    if (httpResponse.indexOf("?waterOff") >= 0) {
	status[3] = !status[3];
    }
}
