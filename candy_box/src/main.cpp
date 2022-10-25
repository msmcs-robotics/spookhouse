#include <Arduino.h>
#include <Ultrasonic.h>

struct {
    int us1e = 7;
    int us1t = 6;

    int taser = 13;
    int annode = 10;
} pins;

struct {
    int BAUD = 9600;

    int min_dist = 15;

    int taser_delay = 3;

    int loop_delay = 250;

} info;



// Sensor Objects

Ultrasonic us1(pins.us1t, pins.us1e);

//Trigger Taser

// Control Stepper Motor


void setup() {
    Serial.begin(info.BAUD);

    pinMode(pins.taser, OUTPUT);
    digitalWrite(pins.taser, LOW);
    pinMode(pins.annode, OUTPUT);
    digitalWrite(pins.annode, HIGH);
};

void loop() {
    float dist = us1.Ranging(CM);
    Serial.print("distance: ");
    Serial.println(dist);

    if (dist <= info.min_dist) {
        digitalWrite(pins.taser, HIGH);
        delay(info.taser_delay * 1000);
        digitalWrite(pins.taser, LOW);
    };
    delay(info.loop_delay);
};