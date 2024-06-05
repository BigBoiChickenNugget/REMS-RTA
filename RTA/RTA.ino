#define HEAT 8
#define COOL 5

void setup() {
	Serial.begin(9600);
	pinMode(HEAT, OUTPUT);
	pinMode(COOL, OUTPUT);
}

void loop() {
	if (Serial.available()) {
		char command = char(Serial.read());
		if (command == 'A') {
			digitalWrite(HEAT, LOW);
		}
		if (command == 'B') {
			digitalWrite(HEAT, HIGH);
		}
		if (command == 'C') {
			digitalWrite(COOL, LOW);
		}
		if (command == 'D') {
			digitalWrite(COOL, HIGH);
		}

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
