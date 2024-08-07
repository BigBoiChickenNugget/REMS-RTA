// Libraries for Ethernet ENC connection for ESP32.
#include <SPI.h>
#include <EthernetENC.h>

// MAC address for the Ethernet shield
byte mac[] = {
	0x2A, 0xF3, 0xB1, 0x08, 0x55, 0x4E
};

// Local IP for the ESP32
IPAddress ip(192, 168, 3, 167);

// Ethernet server
EthernetServer server(80);

// String to store the response from the client
String httpResponse;

// Setup
void setup() {
	// Begin serial monitor
	Serial.begin(921600);

	// Start web server
	Ethernet.begin(mac, ip);
	server.begin();
}

void loop() {
	// Listen for incoming clients
	EthernetClient client = server.available();

	// If a client is connected
	if (client) {
		
		// If client is available
		if (client.available()) {

			// Close the connection
			delay(1);
			client.stop();
		}
	}
}


// Function to display teh webpage and send the outgoing requests to the client
void ClientResponse(EthernetClient client) {
	// Send a standard HTTP response header
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println("Connection: close");
	client.println();

	// Start the HTML
	client.println("<!DOCTYPE html>");

	// HTML header
	client.println("<html>");
	client.println("<head>");
	client.println("<title>ESP32 Web Server</title>");

	// Javascript function to get the value of the temperature via POST.
	client.println("<script>");
	client.println("function getTemperature() {");
	client.println("var temperature = document.getElementById('temperature').value;");
	client.println("var xhr = new XMLHttpRequest();");
	client.println("xhr.open('POST', '/', true);");
	client.println("xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');");
	client.println("xhr.send('temperature=' + temperature);");
	client.println("}");
	client.println("</script>");
	client.println("</head>");

	// HTML body
	client.println("<body>");

	// Header of the webpage
	client.println("<h1>REMS3 (ESP32)</h1>");

	// Close the webpage
	client.println("</body>");
	client.println("</html>");
}
