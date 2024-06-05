#define HEAT 8
#define COOL 5

void setup() {
	Serial.begin(9600);
	pinMode(HEAT, OUTPUT);
	pinMode(COOL, OUTPUT);
}

void loop() {
	switch(Serial.readline().trim()) {
		case "HEATON":
			digitalWrite(HEAT, LOW);
		case "HEATOFF":
			digitalWrite(HEAT, HIGH);
		case "COOLON":
			digitalWrite(COOL, LOW);
		case "COOLOFF":
			digitalWrite(COOL, HIGH);
	}
}
