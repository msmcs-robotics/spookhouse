#include <Arduino.h>
#include <Ultrasonic.h>

struct {

    int us1e = 5;
    int us1t = 6;

    int pn_1 = 9; // Right
    int pn_2 = 10; // Left

    int status_pin = 13;

} pins;

struct {

    int BAUD = 9600;

    int min_dist = 45;
    int measure_delay = 250; // miliseconds


    int status_blinks = 3; // blink led to notify of activation
    int status_delay = 250; // miliseconds

    int pneumatic_cylinder_travel_time = 3000; // miliseconds

    int max_delay_between_right_left = 100; // deciseconds 
    int min_delay_between_right_left = 25;

    int max_delay_between_shakes = 100; // deciseconds
    int min_delay_between_shakes = 50;

} info;

Ultrasonic us1(pins.us1t, pins.us1e);

float rand_delay_between_right_left() {
    int rand_int = random(info.min_delay_between_right_left, info.max_delay_between_right_left);
    return rand_int * 10.0;
}

float rand_delay_between_shakes() {
    int rand_int = random(info.min_delay_between_shakes, info.max_delay_between_shakes);
    return rand_int * 10.0;
}

void right_high() {

    Serial.println("Right...");
    digitalWrite(pins.pn_1, HIGH);
    delay(rand_delay_between_right_left());
    digitalWrite(pins.pn_2, LOW);
    delay(info.pneumatic_cylinder_travel_time);

}

void left_high() {

    Serial.println("Left...");
    digitalWrite(pins.pn_1, LOW);
    delay(rand_delay_between_right_left());
    digitalWrite(pins.pn_2, HIGH);
    delay(info.pneumatic_cylinder_travel_time);

}

void off() {

    Serial.println("Turning OFF...");
    digitalWrite(pins.pn_1, LOW);
    digitalWrite(pins.pn_2, LOW);
    
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

    pinMode(pins.pn_1, OUTPUT);
    pinMode(pins.pn_2, OUTPUT);

    pinMode(pins.status_pin, OUTPUT);

    off();
};

void loop() {

    float dist = us1.Ranging(CM);
    //Serial.print("Distance: ");
    //Serial.println(dist);

    if (dist <= info.min_dist) {
        
        status_blink();
        
        while (dist <= info.min_dist) {
            right_high();
            delay(rand_delay_between_shakes());
            left_high();
            delay(rand_delay_between_shakes());
            dist = us1.Ranging(CM);
            
            if (dist > info.min_dist) {
                off();
                break;
            }

        }

    }

    delay(info.measure_delay);
};