// Pins at which the lamp and fan lie.
#define HEAT 8
#define COOL 5

// Pins for smoke and water.
#define SMOKE 6
#define WATERON 2
#define POWER 12
#define WATERLEAK 10

// Start the serial monitor and configure the pins.
void setup() {
	Serial.begin(9600);
	pinMode(HEAT, OUTPUT);
	pinMode(COOL, OUTPUT);
	pinMode(SMOKE, OUTPUT);
	pinMode(WATERLEAK, OUTPUT);

	pinMode(WATERON, INPUT);
	pinMode(POWER, INPUT);


	// Keep them off by default. The pin pushes low voltage and the relay flips it around so they turn on when the program starts.
	digitalWrite(HEAT, HIGH);
	digitalWrite(COOL, HIGH);
	digitalWrite(HEAT, HIGH);
}

void loop() {

	// If the serial monitor has incoming input...
	if (Serial.available()) {

		// Read the serial monitor and store it as a char.
		char command = char(Serial.read());

		// 'A' means lamp on.
		if (command == 'A') {
			digitalWrite(HEAT, LOW);
			Serial.println("HEAT");
		}

		// 'B' means lamp off.
		if (command == 'B') {
			digitalWrite(HEAT, HIGH);
			Serial.println("NO HEAT");
		}

		// 'C' means fan on.
		if (command == 'C') {
			digitalWrite(COOL, LOW);
			Serial.println("COOL");
		}

		// 'D' means fan off.
		if (command == 'D') {
			digitalWrite(COOL, HIGH);
			Serial.println("NO COOL");
		}
	}
}
