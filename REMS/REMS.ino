#include <SPI.h>
#include <Ethernet.h>
//#include <WebSocketServer.h>

// For temperature
#include <OneWire.h>
#include <DallasTemperature.h>

#define HEATREQUEST 31
#define COOLREQUEST 35

#define SOUNDSENSOR1 23
#define SOUNDSENSOR2 25
#define SOUNDSENSOR3 27
#define SOUNDSENSOR4 23

#define MOTIONSENSOR1 30
#define MOTIONSENSOR2 32
#define MOTIONSENSOR3 34
#define MOTIONSENSOR4 36

#define SMOKEALARM 43

#define POWERSHUTOFF 21

#define WATERSHUTOFF 33


// Temperature setup
#define ONE_WIRE_BUS_1 37
#define ONE_WIRE_BUS_2 39
#define ONE_WIRE_BUS_3 41

OneWire onewire_1(ONE_WIRE_BUS_1);
OneWire onewire_2(ONE_WIRE_BUS_2);
OneWire onewire_3(ONE_WIRE_BUS_3);

DallasTemperature sensor_1(&onewire_1);
DallasTemperature sensor_2(&onewire_2);
DallasTemperature sensor_3(&onewire_3);

byte mac[] = {
    0x2C, 0xF7, 0xF1, 0x08, 0x33, 0x4E
};

IPAddress ip(192, 168, 3, 160);

EthernetServer server(80);
//WebSocketServer wsServer(8080);

String httpResponse;

void setup() {

    Serial.begin(9600);

    Ethernet.begin(mac, ip);
    server.begin();
    //wsServer.begin();

    //Serial.print("server is at ");
    //Serial.println(Ethernet.localIP());

    pinMode(HEATREQUEST, OUTPUT);
    pinMode(COOLREQUEST, OUTPUT);

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
    digitalWrite(POWERSHUTOFF, LOW);

    sensor_1.begin();
    sensor_2.begin();
    sensor_3.begin();
}

void readRequest(EthernetClient client) {

    boolean post = false;
    httpResponse = "";
    String line = client.readStringUntil('\r');

    if (line.indexOf("POST") != -1) {
	post = true;
    }

    while (client.connected()) {
	String line = client.readStringUntil('\r');
	httpResponse += line;

	if (line == "\n" && !post) break;
	if (line.indexOf("heatrequest") != -1 && post) break;
    }
}


void loop() {

    //wsServer.listen();

    // listen for incoming clients
    EthernetClient client = server.available();

    if (client) {
	//Serial.println("new client");

	if (client.available()) {
	    readRequest(client);
	    //Serial.println(httpResponse);
	    //Serial.println();

	    ClientResponse(client);
	    httpResponse = "";
	    //Serial.println("client disconnected");
	    delay(1);
	    client.stop();
	}
    }
}

void ClientResponse(EthernetClient client) {
    // Send http request start
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    // Begin HTML
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    // Code for the head portion of the webpage
    client.println("<head>");
    client.println("<title>REMS CONTROL CENTRE</title>");

    // Javascript portion
    client.println("<script>");
    client.println("function DoStuff() {");
    client.println("  var xhr = new XMLHttpRequest();");
    client.println("  xhr.open('POST', '/', true);");
    client.println("  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');");
    client.println("  var heatState = document.getElementById('heatState').checked ? 1 : 0;");
    client.println("  var coolState = document.getElementById('coolState').checked ? 1 : 0;");
    client.println("  var powerOff = document.getElementById('powerOff').checked ? 1 : 0;");
    client.println("  xhr.send('heatrequest=' + heatState + '&coolrequest=' + coolState + '&powerOff=' + powerOff);");
    client.println("}");
    client.println("</script>");
    client.println("</head>");

    client.println("<body>");
    client.println("<h1>REMS Control Centre</h1>");

    client.println("<label for='heatState'>Heat Request</label>");
    client.println("<input type='checkbox' id='heatState'>");

    client.println("<label for='coolState'>Cool Request</label>");
    client.println("<input type='checkbox' id='coolState'>");

    client.println("<label for='powerOff'>Power Off</label>");
    client.println("<input type='checkbox' id='powerOff'>");

    client.println("<button onclick='DoStuff()'><h4>Do Stuff</h4></button>");
    client.println("</body>");

    client.println("</html>");


    // HEAT LOGIC
    if (searchResponse(httpResponse, "heatrequest")) {
	digitalWrite(HEATREQUEST, LOW);
	Serial.println("  HEAT ON  ");
    }
    else {
	digitalWrite(HEATREQUEST, HIGH);
	Serial.println("  HEAT OFF  ");
    }


    // COOL LOGIC
    if (searchResponse(httpResponse, "coolrequest")) {
	digitalWrite(COOLREQUEST, LOW);
	Serial.println("  COOL ON  ");
    }
    else {
	digitalWrite(COOLREQUEST, HIGH);
	Serial.println("  COOL OFF  ");
    }

    // POWER SHUT OFF LOGIC
    if (searchResponse(httpResponse, "powerOff")) {
	digitalWrite(POWERSHUTOFF, LOW);
    }	    
    else digitalWrite(POWERSHUTOFF, HIGH);

    // SMOKE ALARM LOGIC
    if (digitalRead(SMOKEALARM)) {
	client.println("<p>Smoke Alarm received from REMS006</p>");
    }
}

// Searches the http response and checks what the state is of the current item I'm looking for.
boolean searchResponse(String data, String key) {
    int index = data.indexOf(key + "=") + key.length() + 1;
    return data.charAt(index) == '1';
}

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
