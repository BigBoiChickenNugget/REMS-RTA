// Sound sensors (not sure what microphone is yet)
#define VIBRATION1 29 // Living room
#define VIBRATION2 27 // Kitchen
#define VIBRATION3 25 // Laundry
#define MICROPHONE 23 // EQ

// Motion sensors
#define MOTION1 36 // Living room
#define MOTION2 34 // Kitchen
#define MOTION3 32 // Laundry
#define MOTION4 30 // EQ

// DHT temperature sensors
#define DHT22_1 28 // Living room
#define DHT11_1 26 // Kitchen
#define DHT11_2 24 // Laundry
#define DHT11_3 22 // EQ

// DHT Sensor setup
#include <DHT.h>
DHT dht1(DHT22_1, DHT22);
DHT dht2(DHT11_1, DHT11);
DHT dht3(DHT11_2, DHT11);
DHT dht4(DHT11_3, DHT11);

void setup() {

    Serial.begin(9600);
    pinMode(VIBRATION1, INPUT);
    pinMode(VIBRATION2, INPUT);
    pinMode(VIBRATION3, INPUT);

    //pinMode(MICROPHONE, INPUT); Not sure what microphone is yet

    pinMode(MOTION1, INPUT);
    pinMode(MOTION2, INPUT);
    pinMode(MOTION3, INPUT);
    pinMode(MOTION4, INPUT);

    pinMode(DHT22_1, INPUT);
    pinMode(DHT22_2, INPUT);
    pinMode(DHT11_1, INPUT);
    pinMode(DHT11_2, INPUT);
    dht1.begin();
    dht2.begin();
    dht3.begin();
    dht4.begin();
}

void loop() {
    //readVibration();
    //readMotion();
    //readDHT();
    delay(1000);
}

void readVibration() {
    int vibration1 = digitalRead(VIBRATION1);
    int vibration2 = digitalRead(VIBRATION2);
    int vibration3 = digitalRead(VIBRATION3);

    Serial.print("Vibration Living: ");
    Serial.println(vibration1);
    Serial.print("Vibration Kitchen: ");
    Serial.println(vibration2);
    Serial.print("Vibration Laundry: ");
    Serial.println(vibration3);
}

void readMotion() {
    int motion1 = digitalRead(MOTION1);
    int motion2 = digitalRead(MOTION2);
    int motion3 = digitalRead(MOTION3);
    int motion4 = digitalRead(MOTION4);

    Serial.print("Motion Living: ");
    Serial.println(motion1);
    Serial.print("Motion Kitchen: ");
    Serial.println(motion2);
    Serial.print("Motion Laundry: ");
    Serial.println(motion3);
    Serial.print("Motion EQ: ");
    Serial.println(motion4);
}

void readDHT() {
    dht1.readTemperature();
    dht2.readTemperature();
    dht3.readTemperature();
    dht4.readTemperature();

    Serial.print("DHT22 Living: ");
    Serial.println(dht1.readTemperature());
    Serial.print("DHT11 Kitchen: ");
    Serial.println(dht2.readTemperature());
    Serial.print("DHT11 Laundry: ");
    Serial.println(dht3.readTemperature());
    Serial.print("DHT11 EQ: ");
    Serial.println(dht4.readTemperature());
}
