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
            client.println("<title>REMS ESP32 ENC</title>");

            client.println("</head>");

            // Start body portion of site. Header that has site label.
            client.println("<body>");
            client.println("<h1>REMS006 ESP ENC SWITCH</h1>");
            client.println("<h4>192.168.3.167</h4>");

        delay(1);
            client.stop();
        }
    }
}
