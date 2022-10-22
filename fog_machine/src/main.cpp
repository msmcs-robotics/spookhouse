#include <Arduino.h>
#include <Ultrasonic.h>

struct {

    int us1e = 5;
    int us1t = 6;

    int s1_1 = 9;
    int s1_2 = 10;

    int status_pin = 13;

} pins;

struct {

    int BAUD = 9600;
    int min_dist = 30;
    int status_blinks = 3; // blink led to notify of activation
    int status_delay = 250; // not seconds

    int to_seconds = 1000;
    int to_minutes = 60000;

    int measure_delay = 250; // not seconds

    int solenoid_travel_time = 3; // normalized to seconds

    /* 
    You don't want the fog machine going off everytime someone walks by
    You also don't want a boring party

    if someone walks by, turn on fog
    hard wait at least (fixed_fog_delay) minutes
    if nobody walks by after (fixed_fog_delay), then there is no reason to turn on more fog
    else turn on more fog

    * there is no else statement, the main loop simply restarts and waits for someone to get close to the sensor

    */

    int fixed_fog_delay = 10; // is normalized to minutes
    int fog_on_delay = 5; // how long to pump fog, normalized to seconds

} info;

Ultrasonic us1(pins.us1t, pins.us1e);

void fog_high() {

    Serial.println("Turning Fog ON...");
    digitalWrite(pins.s1_1, HIGH);
    digitalWrite(pins.s1_2, HIGH);
    delay(info.solenoid_travel_time);
    delay(info.fog_on_delay);

}

void fog_on() {

    Serial.println("Turning Fog ON...");
    digitalWrite(pins.s1_1, HIGH);
    digitalWrite(pins.s1_2, LOW);
    delay(info.solenoid_travel_time);
    delay(info.fog_on_delay);

}

void fog_off() {

    Serial.println("Turning Fog OFF...");
    digitalWrite(pins.s1_1, LOW);
    digitalWrite(pins.s1_2, HIGH);
    delay(info.solenoid_travel_time * info.to_seconds);

}

void solenoid_off() {

    digitalWrite(pins.s1_1, LOW);
    digitalWrite(pins.s1_2, LOW);

}

void status_blink() {
    for (int i=0; i<=info.status_blinks; i++) {
        digitalWrite(pins.status_pin, HIGH);
        delay(info.status_delay);
        digitalWrite(pins.status_pin, LOW);
        delay(info.status_delay);
    };
}

void setup() {

    Serial.begin(info.BAUD);

    pinMode(pins.s1_1, OUTPUT);
    pinMode(pins.s1_2, OUTPUT);

    pinMode(pins.status_pin, OUTPUT);

    solenoid_off();
};

void loop() {

    float dist = us1.Ranging(CM);
    Serial.print("distance: ");
    Serial.println(dist);

    if (dist <= info.min_dist) {
        status_blink();
        fog_high();
        fog_on();
        fog_off();
        solenoid_off();
        //delay(info.fixed_fog_delay * info.to_minutes);
    };

    delay(info.measure_delay);
};