#include <HCSR04.h>

int ledPin = 13; //Relay Pin
int base_delay = 1000;
int base_delay2 = 3000; //Leave relay on

int us1T = 5; //Trigger Pn 
int us1E = 6; //Echo Pin

int min_range = 10.00;

HCSR04 us1(us1T, us1E); //initialisation class HCSR04 (trig pin , echo pin)

void setup() { 
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
    if (us1.dist() <= min_range && us1.dist() != 0.00) {
      digitalWrite(ledPin, HIGH);
      delay(base_delay2);
      digitalWrite(ledPin, LOW);
      delay(base_delay);
    }
    Serial.println(us1.dist());
}
