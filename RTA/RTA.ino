#define HEAT 8
#define HEATREQUEST 3

#define COOLREQUEST 4
#define COOL 5

#define NOISE 11
#define SMOKE 6
#define WATER 7

void setup() {
	Serial.begin(115200);
	pinMode(HEAT, OUTPUT);
	pinMode(HEATREQUEST, INPUT_PULLUP);

	pinMode(COOL, OUTPUT);
	pinMode(COOLREQUEST, INPUT_PULLUP);

	pinMode(NOISE, OUTPUT);
	pinMode(SMOKE, OUTPUT);
	pinMode(WATER, OUTPUT);
}

void loop() {
	Serial.print(digitalRead(COOLREQUEST));
	Serial.print(" ");
	Serial.println(digitalRead(HEATREQUEST));
	//if (digitalRead(HEATREQUEST)) digitalWrite(HEAT, LOW);
	//else if (!digitalRead(HEATREQUEST)) digitalWrite(HEAT, HIGH);

	Serial.println("HHHHHHH");

	digitalWrite(HEAT, HIGH);
	digitalWrite(COOL, HIGH);
	digitalWrite(NOISE, HIGH);
	digitalWrite(SMOKE, HIGH);
	digitalWrite(WATER, HIGH);
	delay(1000);
}
