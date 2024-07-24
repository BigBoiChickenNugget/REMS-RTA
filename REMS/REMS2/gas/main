#define GAS1 A7
#define GAS2 A8


void setup() {
	Serial.begin(9600);
	pinMode(GAS1, INPUT);
	pinMode(GAS2, INPUT);
}

void loop() {
	Serial.print(analogRead(GAS1));
	Serial.print(" ");
	Serial.print(analogRead(GAS2));
	Serial.print(" ");
	Serial.print(analogRead(RANDOM));
	Serial.print(" ");
	Serial.print(analogRead(RANDOM2));
	Serial.print(" ");
	Serial.println(analogRead(RANDOM3));
	delay(1000);
}
