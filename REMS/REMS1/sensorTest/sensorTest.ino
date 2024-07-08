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
#define DHT22_2 26 // Kitchen
#define DHT11_1 24 // Laundry
#define DHT11_2 22 // EQ

// DHT Sensor setup
#include <DHT.h>
DHT dht1(DHT22_1, DHT22);
DHT dht2(DHT22_2, DHT22);
DHT dht3(DHT11_1, DHT11);
DHT dht4(DHT11_2, DHT22);

// LM35DZ temperature sensors
#define LM35DZ_1 A13 // Kitchen
#define LM35DZ_2 A14 // Laundry
#define LM35DZ_3 A15 // Batheroom

// DS18B20 temperature sensors
#include <OneWire.h>
#include <DallasTemperature.h>
#define DS18B20_1 37 // D37
#define DS18B20_2 39 // D39
#define DS18B20_3 41 // D41

// DS18B20 setup
OneWire oneWire1(DS18B20_1);
DallasTemperature sensor1(&oneWire1);

OneWire oneWire2(DS18B20_2);
DallasTemperature sensor2(&oneWire2);

OneWire oneWire3(DS18B20_3);
DallasTemperature sensor3(&oneWire3);


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

    pinMode(LM35DZ_1, INPUT);
    pinMode(LM35DZ_2, INPUT);
    pinMode(LM35DZ_3, INPUT);

    // DS18B20 sensors
    sensor1.begin();
    sensor2.begin();
    sensor3.begin();
}

void loop() {
    //readVibration();
    //readMotion();
    readDHT();
    readLM35DZ();
    readDS18B20();
    delay(1000);
}

void readVibration() {
    int vibration1 = digitalRead(VIBRATION1);
    int vibration2 = digitalRead(VIBRATION2);
    int vibration3 = digitalRead(VIBRATION3);

    Serial.print("Vibration D29: ");
    Serial.println(vibration1);

    Serial.print("Vibration D27: ");
    Serial.println(vibration2);

    Serial.print("Vibration D25: ");
    Serial.println(vibration3);
}

void readMotion() {
    int motion1 = digitalRead(MOTION1);
    int motion2 = digitalRead(MOTION2);
    int motion3 = digitalRead(MOTION3);
    int motion4 = digitalRead(MOTION4);

    Serial.print("Motion D36: ");
    Serial.println(motion1);

    Serial.print("Motion D34: ");
    Serial.println(motion2);

    Serial.print("Motion D32: ");
    Serial.println(motion3);

    Serial.print("Motion D30: ");
    Serial.println(motion4);
}

void readDHT() {
    dht1.readTemperature();
    dht2.readTemperature();
    dht3.readTemperature();
    dht4.readTemperature();

    Serial.print("DHT22 D28: ");
    Serial.println(dht1.readTemperature());
    Serial.print("DHT22 D26: ");
    Serial.println(dht2.readTemperature());
    Serial.print("DHT11 D24: ");
    Serial.println(dht3.readTemperature());
    Serial.print("DHT11 D22: ");
    Serial.println(dht4.readTemperature());

}

void readLM35DZ() {
    int temp1 = analogRead(LM35DZ_1);
    int realTemp1 = temp1 * 4.88;
    realTemp1 = realTemp1 / 10;

    int temp2 = analogRead(LM35DZ_2);
    int realTemp2 = temp2 * 4.88;
    realTemp2 = realTemp2 / 10;

    int temp3 = analogRead(LM35DZ_3);
    int realTemp3 = temp3 * 4.88;
    realTemp3 = realTemp3 / 10;

    Serial.print("LM35DZ A13: ");
    Serial.println(realTemp1);

    Serial.print("LM35DZ A14: ");
    Serial.println(realTemp2);

    Serial.print("LM35DZ A15: ");
    Serial.println(realTemp3);
}

void readDS18B20() {
    sensor1.requestTemperatures();
    sensor2.requestTemperatures();
    sensor3.requestTemperatures();

    Serial.print("DS18B20 D37: ");
    Serial.println(sensor1.getTempCByIndex(0));
    Serial.print("DS18B20 D39: ");
    Serial.println(sensor2.getTempCByIndex(0));
    Serial.print("DS18B20 D41: ");
    Serial.println(sensor3.getTempCByIndex(0));
}
