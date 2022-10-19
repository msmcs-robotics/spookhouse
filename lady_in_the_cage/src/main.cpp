#include <Arduino.h>
#include <Ultrasonic.h>

struct {
    int ut1 = 2;
    int ue1 = 3;

    int relay1 = 4;
    int relay2 = 5;

    int led1 = 13;
} pins;

struct {
    int min_shake_delay = 250; // alternating between relays
    int max_shake_delay = 1000;

    int min_shake_duration = 1000; // how long to shake
    int max_shake_duration = 5000; // how long to shake

    int min_num_shakes = 1;
    int max_num_shakes = 5;

    int min_distance = 30; // minimum distance to sensor
} info;

Ultrasonic us1(pins.ut1, pins.ue1);

int get_num_shakes() {
    return random(info.min_num_shakes, info.max_num_shakes);
}

int get_alternating_shake_delay() {
    return random(info.min_shake_delay, info.max_shake_delay);
}

int get_betwen_shake_delay() {
    return random(info.min_shake_duration, info.max_shake_duration);
}

void will_shake() {
    int num_blinks = 5;
    int blink_delay = 250;

    for (int i = 0; i < num_blinks; i++) {
        digitalWrite(pins.led1, HIGH);
        delay(blink_delay);
        digitalWrite(pins.led1, LOW);
        delay(blink_delay);
    }
}

void shake(int reps) {
    for (int i = 0; i < reps; i++) {
        digitalWrite(pins.relay1, HIGH);
        delay(get_alternating_shake_delay());
        digitalWrite(pins.relay2, HIGH);

        delay(get_betwen_shake_delay());

        digitalWrite(pins.relay1, LOW);
        delay(get_alternating_shake_delay());
        digitalWrite(pins.relay2, LOW);

        delay(get_betwen_shake_delay());
    }
}

void setup() {
    pinMode(pins.relay1, OUTPUT);
    pinMode(pins.relay2, OUTPUT);
    pinMode(pins.led1, OUTPUT);

    digitalWrite(pins.relay1, LOW);
    digitalWrite(pins.relay2, LOW);
    digitalWrite(pins.led1, LOW);
}

void loop() {
    int distance = us1.Ranging(CM);

    if (distance < info.min_distance) {
        will_shake();
        shake(get_num_shakes());
    }
}