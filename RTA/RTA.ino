// Pins at which the lamp and fan lie.
#define HEAT 8
#define COOL 5

// Start the serial monitor and configure the pins.
void setup() {
	Serial.begin(9600);
	pinMode(HEAT, OUTPUT);
	pinMode(COOL, OUTPUT);

	// Keep them off by default. The pin pushes low voltage and the relay flips it around so they turn on when the program starts.
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

		// Uhh ignore for this for now.
		/*switch(char(Serial.read())) {
			case 'A':
				digitalWrite(HEAT, LOW);
			case 'B':
				digitalWrite(HEAT, HIGH);
			case 'C':
				digitalWrite(COOL, LOW);
			case 'D':
				digitalWrite(COOL, HIGH);
		}*/
	}
}
