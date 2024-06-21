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

// Mac address of Arduino REMS board.
byte mac[] = {
    0x2C, 0xF7, 0xF1, 0x08, 0x33, 0x4E
};

// IP address for the webpage.
IPAddress ip(192, 168, 3, 160);

EthernetServer server(80);

// String that'll store the response from the webpage.
String httpResponse;
boolean changed = 0;

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
    client.println("<title>REMS CONTROL CENTRE 1</title>");

    client.println("</head>");

    // Start body portion of site. Header that has site label.
    client.println("<body>");
    client.println("<h1>REMS006 1</h1>");
    client.println("<h4>192.168.3.160</h4>");

    String heat, cool, power, water;
    for (int i = 0; i < 4; i++) {
	if (!status[i]) {
	    if (i == 0) heat = "HEAT ON";
	    if (i == 1) cool = "COOL ON";
	    if (i == 2) power = "POWER OFF";
	    if (i == 3) water = "WATER OFF";
	}
	else if (status[i]) {
	    if (i == 0) heat = "HEAT OFF";
	    if (i == 1) cool = "COOL OFF";
	    if (i == 2) power = "POWER ON";
	    if (i == 3) water = "WATER ON";
	}
    }

    client.println("<a href='/?heatrequest'><button>" + heat + "</button></a>");
    client.println("<a href='/?coolrequest'><button>" + cool + "</button></a>");
    client.println("<a href='/?powerOff'><button>" + power + "</button></a>");
    client.println("<a href='/?waterOff'><button>" + water + "</button></a>");


    // End body and HTML.
    if (status[0]) {
	digitalWrite(HEATREQUEST, LOW);
	Serial.println("HEAT ON");
    }

    else {
	digitalWrite(HEATREQUEST, HIGH);
	Serial.println("HEAT OFF");
    }

    if (status[1]) {
	digitalWrite(COOLREQUEST, LOW);
	Serial.println("COOL ON");
    }

    else {
	digitalWrite(COOLREQUEST, HIGH);
	Serial.println("COOL OFF");
    }

    if (status[2]) {
	digitalWrite(POWERSHUTOFF, LOW);
	client.println("POWER OFF");
    }

    else {
	digitalWrite(POWERSHUTOFF, HIGH);
    }

    if (status[3]) {
	digitalWrite(WATERSHUTOFF, LOW);
	client.println("WATER OFF");
    }

    else {
	digitalWrite(WATERSHUTOFF, HIGH);
    }

    // Temperature sensor readings.
    tmp1 = sensor_1.requestTemperatures();
    tmp2 = sensor_2.requestTemperatures();
    tmp3 = sensor_3.requestTemperatures();

    // Create temperature sensors small header but position it below the rest
    client.println("<h4 style='position: relative; top: 5%;'>Temperature Sensors</h4>");
    client.println("<p style='position: relative; top: 1%;'>Temperature Sensor 1: " + String(sensor_1.getTempCByIndex(0)) + " C</p>");
    client.println("<p style='position: relative; top: 1%;'>Temperature Sensor 2: " + String(sensor_2.getTempCByIndex(0)) + " C</p>");
    client.println("<p style='position: relative; top: 1%;'>Temperature Sensor 3: " + String(sensor_3.getTempCByIndex(0)) + " C</p>");


    client.println("</body></html>");
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
