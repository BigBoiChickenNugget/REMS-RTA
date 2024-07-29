#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 34

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
	Serial.begin(9600);
	sensors.begin();
}

void loop() {
	// Send the command to get temperatures
	sensors.requestTemperatures(); 

	//print the temperature in Celsius
	Serial.print("Temperature: ");
	Serial.print(sensors.getTempCByIndex(0));
	Serial.print((char)176);//shows degrees character
	Serial.print("C  |  ");

	Serial.print("Temperature: ");
	Serial.print(sensors.getTempCByIndex(1));
	Serial.print((char)176);//shows degrees character
	Serial.println("C");
	delay(500);
}
