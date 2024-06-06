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
	    httpResponse = "";

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

    // Javascript portion. Props to chatgpt because I don't know anything about JavaScript.
    client.println("<script>");

    // Create a function tentatively called "DoStuff".
    client.println("function DoStuff() {");

    // Creates a variable to store the HTTP request that we're going to send.
    client.println("  var xhr = new XMLHttpRequest();");

    // Sends a post request and redirects to '/' (which is just the homepage).
    client.println("  xhr.open('POST', '/', true);");
    client.println("  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');");

    // Variables to store what the user wants to do with heat, cooling, and power (keep them on or off).
    client.println("  var heatState = document.getElementById('heatState').checked ? 1 : 0;");
    client.println("  var coolState = document.getElementById('coolState').checked ? 1 : 0;");
    client.println("  var powerOff = document.getElementById('powerOff').checked ? 1 : 0;");
    client.println("  var waterOff = document.getElementById('powerOff').checked ? 1 : 0;");

    // Send all the user requests back to the Arduino.
    client.println("  xhr.send('heatrequest=' + heatState + '&coolrequest=' + coolState + '&powerOff=' + powerOff + '&waterOff=' + waterOff);");
    client.println("}");
    client.println("</script>");
    client.println("</head>");

    // Start body portion of site. Header that has site label.
    client.println("<body>");
    client.println("<h1>REMS006 1</h1>");
    client.println("<h4>192.168.3.160</h4>");

    // Create a checkbox for the heating.
    client.println("<label for='heatState'>Heat Request</label>");
    client.println("<input type='checkbox' id='heatState'>");

    // Create a checkbox for the cooling.
    client.println("<label for='coolState'>Cool Request</label>");
    client.println("<input type='checkbox' id='coolState'>");

    // Create a checkbox for the power (doesn't work will implement eventually).
    client.println("<label for='powerOff'>Power Off</label>");
    client.println("<input type='checkbox' id='powerOff'>");

    // Create a checkbox for the water shutoff (doesn't work will be implemented eventually).
    client.println("<label for='waterOff'>Water Off</label>");
    client.println("<input type='checkbox' id='waterOff'>");

    // Button that submits the state of the checkboxes and calls the JavaScript function to send the state of the buttons to the Arduino.
    client.println("<button onclick='DoStuff()'><h4>Do Stuff</h4></button>");


    // If the user wants the heating on, print that request to the Serial monitor.
    if (searchResponse(httpResponse, "heatrequest")) {
	digitalWrite(HEATREQUEST, LOW);
	Serial.println("  HEAT ON  ");
    }

    // If the user doesn't want the heating on, print that to the serial monitor.
    else {
	digitalWrite(HEATREQUEST, HIGH);
	Serial.println("  HEAT OFF  ");
    }

    // Same as heating but cooling instead.
    if (searchResponse(httpResponse, "coolrequest")) {
	digitalWrite(COOLREQUEST, LOW);
	Serial.println("  COOL ON  ");
    }
    else {
	digitalWrite(COOLREQUEST, HIGH);
	Serial.println("  COOL OFF  ");
    }

    // To shutoff power and displays message on page.
    if (searchResponse(httpResponse, "powerOff")) {
	digitalWrite(POWERSHUTOFF, LOW);
	client.println("<p>Power shutoff from rems006</p>");
    }	    
    else digitalWrite(POWERSHUTOFF, HIGH);

    // To shutoff water and displays message on page.
    if (searchResponse(httpResponse, "waterOff")) {
	digitalWrite(WATERSHUTOFF, LOW);
	client.println("<p>Water shutoff from rems006</p>");
    }	    
    else digitalWrite(WATERSHUTOFF, HIGH);

    // SMOKE ALARM LOGIC
    // Doesn't work yet.
    if (digitalRead(SMOKEALARM)) {
	client.println("<p>Smoke Alarm received from REMS006</p>");
    }

    // End html
    client.println("</body>");
    client.println("</html>");
}

// Searches the http response and checks what the state is of the current item I'm looking for.
boolean searchResponse(String data, String key) {
    int index = data.indexOf(key + "=") + key.length() + 1;
    return data.charAt(index) == '1';
}

//  Function that reads the incoming HTTP request.
void readRequest(EthernetClient client) {

    // Boolean variable to store if the request is POST (sending states of buttons).
    boolean post = false;
    httpResponse = "";

    // Read the string until the carnage return.
    String line = client.readStringUntil('\r');

    // Set POST to true if it is.
    if (line.indexOf("POST") != -1) {
	post = true;
    }

    // Iterate through all the strings until the newline appears (in the case of a GET request) or until the line with all the checkbox statuses appears (in the case of a POST request).
    while (client.connected()) {
	String line = client.readStringUntil('\r');
	httpResponse += line;

	if (line == "\n" && !post) break;
	if (line.indexOf("heatrequest") != -1 && post) break;
    }
}



// Old version in which I was using GET requests instead of POST. Holds sentimental value since I spent so long figuring it out so I'm hesitant to delete :( (but will do so eventually).
/*
void ClientResponse(EthernetClient client) {
    // HTTP sent
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");

    // Page refresh every 5 seconds
    client.println("Refresh: 60");
    client.println();

    // Begin HTML
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    client.println("<head>");
    client.println("<title>REMS CONTROL PAGE</title>");
    
    // Javascript
    /*
    client.println("<script>");
    client.println("function HeatSensorValues() {");
    client.println("	var xhttp = new XMLHttpRequest();");
    client.println("	    if (this.readyState == 4 && this.status == 200) {");
    client.println("		document.getElementById('heat1').innerHTML = this.responseText;");
    client.println("	}");
    client.println("}");
    client.print("
    client.println("</script>");

    client.println("</head>");
    client.println("<body>");

    // Temperature Section
    client.println("<div style='position: relative;'>");

    // HEAT request section.
    client.println("<a href='/?heatrequest''><button><h3>Send Heat Request</h3></button></a>");

    // Checks for GET request in the HTTP response and sends a high heat request signal to the RTA.
    if (httpResponse.indexOf("?heatrequest") >= 0) {
	digitalWrite(HEATREQUEST, LOW);
	Serial.println("HEAAAT");
    }
    else digitalWrite(HEATREQUEST, HIGH);

    // COOL request section.
    client.println("<a href='/?coolrequest''><button><h3>Send Cool Request</h3></button></a>");

    // Same thing as HEAT request but cool.
    if (httpResponse.indexOf("?coolrequest") > 0) {
	digitalWrite(COOLREQUEST, LOW);
	Serial.println("COOOOOL");
    }
    else digitalWrite(COOLREQUEST, HIGH);

    // To stop both HEAT and COOL requests.
    client.println("<a href='/?stoprequests''><button><h3>Stop Requests</h3></button></a>");

    // Turns off the heat and cooling signals to the RTA.
    if (httpResponse.indexOf("?stoprequests") >= 0) {
	digitalWrite(COOLREQUEST, HIGH);
	digitalWrite(HEATREQUEST, HIGH);
	Serial.println("STTOOOOOPP");
    }

    // If either HEAT or COOLING is on, show the temperature from the pins.
    if (httpResponse.indexOf("?coolrequest") >= 0|| httpResponse.indexOf("?heatrequest") >= 0) {
	sensor_1.requestTemperatures();
	client.println(sensor_1.getTempCByIndex(0));

	sensor_2.requestTemperatures();
	client.println(sensor_2.getTempCByIndex(0));

	sensor_3.requestTemperatures();
	client.println(sensor_3.getTempCByIndex(0));
    }
    client.println("</div>");

    // Begin smoke alarm section.
    client.println("<div style='position: relative; top: 20px'>");

    // If D43 is HIGH, show that smoke alarm is on on W5500.
    if (digitalRead(SMOKEALARM)) client.println("Smoke Alarm Received from REMS006");
    client.println("</div>");

    // Begin power shut off section.
    client.println("<div style='position: relative; top: 2px'>");
    client.println("<a href='/?powershutoff''><button><h2>Power Shut Off</h2></button></a>");

    // If power shut off request, make the powershut off pin high and write "power shut off" on W5500.
    if (httpResponse.indexOf("?powershutoff") >= 0) {
	digitalWrite(POWERSHUTOFF, LOW);
	client.println("Power shut off to REMS006");
    }
    else digitalWrite(POWERSHUTOFF, HIGH);
    client.println("</div>");

    // Water shut off section.
    client.println("<div style='position: relative; top: 20px'>");
    client.println("<a href='/?watershutoff''><button><h2>Water Shut Off</h2></button></a>");

    if (httpResponse.indexOf("?watershutoff") >= 0) {
	digitalWrite(WATERSHUTOFF, LOW);
	client.println("Water shut off to REMS006");
    }
    else digitalWrite(WATERSHUTOFF, HIGH);
    client.println("<div style='position: relative; top: 20px'>");

    // Temporarily display the readings from the sound sensors.
    client.println("<div style='position: relative; top: 50px'>");
    if (digitalRead(SOUNDSENSOR1)) client.println("SOUND DETECTED (23)");
	else client.println("NO SOUND (23)");
    if (digitalRead(SOUNDSENSOR2)) client.println("SOUND DETECTED (25)");
	else client.println("NO SOUND (25)");
    if (digitalRead(SOUNDSENSOR3)) client.println("SOUND DETECTED (27)");
	else client.println("NO SOUND (27)");
    if (digitalRead(SOUNDSENSOR4)) client.println("SOUND DETECTED (29)");
	else client.println("NO SOUND (29)");
    client.println("</div>");

    // Temporarily display the readings from the motion sensors.
    client.println("<div style='position: relative; top: 50px'>");
    if (digitalRead(MOTIONSENSOR1)) client.println("MOTION DETECTED (30)");
	else client.println("NO MOTION (30)");
    if (digitalRead(MOTIONSENSOR2)) client.println("MOTION DETECTED (32)");
	else client.println("NO MOTION (32)");
    if (digitalRead(MOTIONSENSOR3)) client.println("MOTION DETECTED (34)");
	else client.println("NO MOTION (34)");
    if (digitalRead(MOTIONSENSOR4)) client.println("MOTION DETECTED (36)");
	else client.println("NO MOTION (36)");
    client.println("</div>");

    client.println("</body></html>");
}

float getTemp(int pin) {
    OneWire oneWire(pin);

    DallasTemperature sensors(&oneWire);

    sensors.begin();

    sensors.requestTemperatures();

    return sensors.getTempCByIndex(0);
}
*/
