// Pins at which the lamp and fan lie.
#define HEAT 8
#define COOL 5

// Pins for smoke and water.
#define SMOKE 6
#define WATERON 2
#define POWER 12
#define WATERLEAK 10

// Start the serial monitor and configure 
	digitalWrite(HEAT, LOW);
	digitalWrite(COOL, LOW);
	digitalWrite(HEAT, LOW);
}

void loop() {

	// If the serial monitor has incoming input...
	if (Serial.available()) {

		// Read the serial monitor and store it as a char.
		char command = char(Serial.read());

		// 'A' means lamp on.
		if (command == 'A') {
			digitalWrite(HEAT, HIGH);
			Serial.println("HEAT");
		}

		// 'B' means lamp off.
		if (command == 'B') {
			digitalWrite(HEAT, LOW);
			Serial.println("NO HEAT");
		}

		// 'C' means fan on.
		if (command == 'C') {
			digitalWrite(COOL, HIGH);
			Serial.println("COOL");
		}

		// 'D' means fan off.
		if (command == 'D') {
			digitalWrite(COOL, LOW);
			Serial.println("NO COOL");
		}
	}
}
