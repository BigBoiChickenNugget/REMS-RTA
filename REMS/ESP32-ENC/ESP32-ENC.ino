// Libraries for Ethernet connection.
#include <SPI.h>
#include <EthernetENC.h>

// Mac address of Arduino REMS board.
byte mac[] = {
    0x2A, 0xF3, 0xB1, 0x08, 0x55, 0x4E
};

// IP address for the webpage.
IPAddress ip(192, 168, 3, 167);

EthernetServer server(80);

// String that'll store the response from the webpage.
String httpResponse;

// Array to store status of buttons. Order is heat, cool, power, water.
boolean status[] = {false, false, false, false};

void setup() {

    // Begin serial monitor.
    Serial.begin(921600);

    // Start webserver.
    Ethernet.begin(mac, ip);
    server.begin();
}

void loop() {
    Serial.println("HELLO");


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
    client.println("Refresh: 5");
    client.println();

    // Begin HTML
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    // Code for the head portion of the webpage
    client.println("<head>");
    client.println("<title>REMS ESP32 ENC</title>");

    client.println("</head>");

    // Start body portion of site. Header that has site label.
    client.println("<body>");
    client.println("<h1>ESP32 ENC</h1>");
    client.println("<h4>192.168.3.166</h4>");

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

