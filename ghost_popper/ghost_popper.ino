// This is the psuedocode

/*

 - define the pin number for each relay
 - define a range for the min amnount of time between a pop, and the max amount of time
 - define a range for the min amount of time that the ghost is popping, and the max amount of time
 - select a random number in the first range, and assign it to a variable
 - select a random number in the second range, and assign it to a variable
 
 - loop the following:
 - delay turning on the relay for the value of the first variable
 - delay keeping the relay on for the value of the second variable
 
*/

struct {
  int led_pin = 13;

  int relay_pin1 = 6;
  int relay_pin2 = 7;
  int relay_pin3 = 8;
} pins;


struct {
  int min_btw_pop = 3;
  int max_btw_pop = 10;

  int min_len_pop = 2;
  int max_len_pop = 5;
} info;

int rand_btw_pop() {
  int rand_value = random(info.min_btw_pop, info.max_btw_pop);
  return rand_value;
};

int rand_len_pop() {
  int rand_value = random(info.min_len_pop, info.max_len_pop);
  return rand_value;
};


void blink(int num_blinks){
  for (int i = 0; i < num_blinks; i++) {
    digitalWrite(pins.led_pin, HIGH);
    delay(200);
    digitalWrite(pins.led_pin, LOW);
    delay(200);
  }
}

void setup() {
   pinMode(pins.led_pin, OUTPUT);
   
   pinMode(pins.relay_pin1, OUTPUT);
   pinMode(pins.relay_pin2, OUTPUT);
   pinMode(pins.relay_pin3, OUTPUT);
   delay(5000);
}

void loop() {
  int btw_pop = rand_btw_pop() * 1000;
  int len_pop = rand_len_pop() * 100;

  blink(1);
  digitalWrite(pins.relay_pin1, HIGH);
  delay(len_pop);
  digitalWrite(pins.relay_pin1, LOW);
  delay(btw_pop);

  btw_pop = rand_btw_pop() * 1000;
  len_pop = rand_len_pop() * 100;

  blink(2);
  digitalWrite(pins.relay_pin2, HIGH);
  delay(len_pop);
  digitalWrite(pins.relay_pin2, LOW);
  delay(btw_pop);

  btw_pop = rand_btw_pop() * 1000;
  len_pop = rand_len_pop() * 100;

  blink(3);
  digitalWrite(pins.relay_pin3, HIGH);
  delay(len_pop);
  digitalWrite(pins.relay_pin3, LOW);
  delay(btw_pop);
}
