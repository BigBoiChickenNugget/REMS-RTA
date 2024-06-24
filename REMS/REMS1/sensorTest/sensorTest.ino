// Sound sensors (not sure what microphone is yet)
#define VIBRATION1 29
#define VIBRATION2 27
#define VIBRATION3 25
#define MICROPHONE 23

// Motion sensors
#define MOTION1 36
#define MOTION2 34
#define MOTION3 32
#define MOTION4 30

// DHT temperature sensors
#define DHT22_1 28
#define DHT22_2 26
#define DHT11_1 24
#define DHT11_2 22

// DHT Sensor setup
#include <DHT.h>
DHT dht1(DHT22_1, DHT22);
DHT dht2(DHT22_2, DHT22);
DHT dht3(DHT11_1, DHT11);
DHT dht4(DHT11_2, DHT11);

// LM35DZ temperature sensors
#define LM35DZ_1 A13
#define LM35DZ_2 A14
#define LM35DZ_3 A15

// DS18B20 temperature sensors
#include <OneWire.h>
#include <DallasTemperature.h>
#define DS18B20_1 37
#define DS18B20_2 39
#define DS18B20_3 41

// DS18B20 setup
OneWire oneWire(DS18B20_1);
DallasTemperature sensor1(&oneWire);

OneWire oneWire(DS18B20_2);
DallasTemperature sensor2(&oneWire);

OneWire oneWire(DS18B20_3);
DallasTemperature sensor3(&oneWire);


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
    //readDHT();
    //readLM35DZ();
    //readDS18B20();
    delay(1000);
}

void readVibration() {
    int vibration1 = digitalRead(VIBRATION1);
    int vibration2 = digitalRead(VIBRATION2);
    int vibration3 = digitalRead(VIBRATION3);

    Serial.print("Vibration 1: ");
    Serial.println(vibration1);
    Serial.print("Vibration 2: ");
    Serial.println(vibration2);
    Serial.print("Vibration 3: ");
    Serial.println(vibration3);
}

void readMotion() {
    int motion1 = digitalRead(MOTION1);
    int motion2 = digitalRead(MOTION2);
    int motion3 = digitalRead(MOTION3);
    int motion4 = digitalRead(MOTION4);

    Serial.print("Motion 1: ");
    Serial.println(motion1);
    Serial.print("Motion 2: ");
    Serial.println(motion2);
    Serial.print("Motion 3: ");
    Serial.println(motion3);
    Serial.print("Motion 4: ");
    Serial.println(motion4);
}

void readDHT() {
    dht1.readTemperature();
    dht2.readTemperature();
    dht3.readTemperature();
    dht4.readTemperature();

    Serial.print("DHT22-1: ");
    Serial.println(dht1.readTemperature());
    Serial.print("DHT22_2: ");
    Serial.println(dht2.readTemperature());
    Serial.print("DHT11_1: ");
    Serial.println(dht3.readTemperature());
    Serial.print("DHT11_2: ");
    Serial.println(dht4.readTemperature());
}

void readLM35DZ() {
    int temp = analogRead(LM35DZ_1);
    int realTemp = temp * 4.88;
    realTemp = realTemp / 10;
    Serial.print("LM35DZ-1: ");
    Serial.println(realTemp);
}

void readDS18B20() {
    sensor1.requestTemperatures();
    sensor2.requestTemperatures();
    sensor3.requestTemperatures();

    Serial.print("DS18B20-1: ");
    Serial.println(sensor1.getTempCByIndex(0));
    Serial.print("DS18B20-2: ");
    Serial.println(sensor2.getTempCByIndex(0));
    Serial.print("DS18B20-3: ");
    Serial.println(sensor3.getTempCByIndex(0));
}
