#include "Arduino.h"
#include "Webserver.h"

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
    client.println("  var waterOff = document.getElementById('waterOff').checked ? 1 : 0;");

    // Send all the user requests back to the Arduino.
    client.println("  xhr.send('heatrequest=' + heatState + '&coolrequest=' + coolState + '&powerOff=' + powerOff + '&waterOff=' + waterOff);");

    client.println("  if (powerOff == 1) {");
    client.println("    document.getElementById('powerOff').innerHTML = 'Power Off';");
    client.println("  }");
    client.println("  if (waterOff == 1) {");
    client.println("    document.getElementById('waterOff').innerHTML = 'Water Off';");
    client.println("  }");
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
}

void RTACommand(EthernetClient client) {
     
    client.println("TEST TEST TEST TEST");
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
    client.println("<div style='position: relative; top: 10px;'>");
    if (searchResponse(httpResponse, "powerOff")) {
	digitalWrite(POWERSHUTOFF, LOW);
	Serial.println("POWER OFF");
	client.println("<p>Power shutoff from rems006</p>");
    }	    
    else digitalWrite(POWERSHUTOFF, HIGH);

    // To shutoff water and displays message on page.
    if (searchResponse(httpResponse, "waterOff")) {
	digitalWrite(WATERSHUTOFF, LOW);
	Serial.println("WATER OFF");
	client.println("<p>Water shutoff from rems006</p>");
    }	    
    else digitalWrite(WATERSHUTOFF, HIGH);

    // SMOKE ALARM LOGIC
    // Doesn't work yet.
    if (digitalRead(SMOKEALARM)) {
	client.println("<p>Smoke Alarm received from REMS006</p>");
    }
    client.println("</div>");
}

void searchResponse(String response, String key) {
    // If the response contains the key, return true.
    if (response.indexOf(key) != -1) {
	return true;
    }
    // Otherwise, return false.
    else {
	return false;
    }
}

boolean searchResponse(String response, String key) {
    // If the response contains the key, return true.
    if (response.indexOf(key) != -1) {
	return true;
    }
    // Otherwise, return false.
    else {
	return false;
    }
}

boolean searchResponse(String response, String key) {
    // If the response contains the key, return true.
    if (response.indexOf(key) != -1) {
	return true;
    }
    // Otherwise, return false.
    else {
	return false;
    }
}

boolean Webserver::searchResponse(String response, String key) {
    int index = data.indexOf(key + "=") + key.length() + 1;
    return data.charAt(index) == '1';
}

boolean Webserver::readReqeuest(EthernetClient client) {
    
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

	if (line == "\n" && !post) return false;
	if (line.indexOf("heatrequest") != -1 && post) return true;
    }
}

