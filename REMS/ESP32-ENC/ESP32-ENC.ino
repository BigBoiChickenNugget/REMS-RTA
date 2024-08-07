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

// Booleans to store if power and water are on or off
bool powerOn = true;
bool waterOn = true;

// Global temperature variable
float temperature = 25;

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

			// Call the ClientResponse function
			ClientResponse(client);


			// Read the incoming request
			ReadRequest(client);

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

	client.println("<script>");

	// Javascript function to get the value of the temperature via POST.
	client.println("function getTemperature() {");
	client.println("var temperature = document.getElementById('temperature').value;");
	client.println("var xhr = new XMLHttpRequest();");
	client.println("xhr.open('POST', '/', true);");
	client.println("xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');");
	client.println("xhr.send('temperature=' + temperature);");
	client.println("}");

	// Javascript function to get the value of poweroff POST. Also refreshes the page.
	client.println("function powerOff() {");
	client.println("var xhr = new XMLHttpRequest();");
	client.println("xhr.open('POST', '/', true);");
	client.println("xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');");
	client.println("xhr.send('poweroff=1');");
	client.println("location.reload();");
	client.println("}");

	// Javascript function to get the value of wateroff POST.
	client.println("function waterOff() {");
	client.println("var xhr = new XMLHttpRequest();");
	client.println("xhr.open('POST', '/', true);");
	client.println("xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');");
	client.println("xhr.send('wateroff=1');");
	client.println("location.reload();");
	client.println("}");

	client.println("</script>");
	client.println("</head>");

	// HTML body
	client.println("<body>");

	// Header of the webpage
	client.println("<h1>REMS3 (ESP32)</h1>");

	// Number input for the temperature. Default is 25 and max is 30 and min is 20. This is a box input that has a range of number values. Not a slider. Calls the getTemperature function when the value is changed.
	client.println("<div style='position: relative; top: 10%'>");
	client.println("<h4>Temperature Control</h4>");
	client.println("<input type='number' id='temperature' value='25' max='30' min='20' oninput='getTemperature()'>");
	client.println("</div>");

	// Button for power off. Calls the getPowerOff function when clicked.
	client.println("<div style='position: relative; top: 20%'>");
	client.println("<h4>Power Control</h4>");

	// If the power is on, display the power off button. If the power is off, display the power on button.
	if (powerOn) {
		client.println("<button onclick='powerOff()'>Power Off</button>");
	}
	else {
		client.println("<button onclick='powerOff()'>Power On</button>");
	}
	client.println("</div>");

	// Button for water off. Calls the getWaterOff function when clicked.
	client.println("<div style='position: relative; top: 30%'>");
	client.println("<h4>Water Control</h4>");

	// If the water is on, display the water off button. If the water is off, display the water on button.
	if (waterOn) {
		client.println("<button onclick='waterOff()'>Water Off</button>");
	}
	else {
		client.println("<button onclick='waterOff()'>Water On</button>");
	}
	client.println("</div>");

	// Close the webpage
	client.println("</body>");
	client.println("</html>");
}

// Function to handle the incoming requests from the client
void ReadRequest(EthernetClient client) {

	// Read the first line of the request
	String request = client.readStringUntil('\r');
	Serial.println(request);

	// If the request is a POST request
	if (request.indexOf("POST") != -1) {

		while (true) {

			// Read the rest of the request
			request = client.readStringUntil('\r');
			Serial.println(request);

			// If the request is for the temperature
			if (request.indexOf("temperature") != -1) {

				// Get the temperature value
				temperature = request.substring(request.indexOf("temperature=") + 12).toFloat();
				Serial.println("Temperature: " + String(temperature));
				break;
			}

			// If the request is for power off
			if (request.indexOf("poweroff") != -1) {

				// If the power is on, turn it off. If the power is off, turn it on.
				if (powerOn) {
					powerOn = false;
				}
				else {
					powerOn = true;
				}
				break;
			}

			// If the request is for water off
			if (request.indexOf("wateroff") != -1) {

				// If the water is on, turn it off. If the water is off, turn it on.
				if (waterOn) {
					waterOn = false;
				}
				else {
					waterOn = true;
				}
				break;
			}
		}
	}
}
