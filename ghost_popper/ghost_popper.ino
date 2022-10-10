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

int relay_pin1 = 6;
int relay_pin2 = 7;
int relay_pin3 = 8;

int min_btw_pop = 3;
int max_btw_pop = 10;

float min_len_pop = 0.5;
float max_len_pop = 2;

float rand_btw_pop() {
  float rand_value = random((min_btw_pop * 1000), (max_btw_pop * 1000));
  return rand_value;
};

float rand_len_pop() {
  float rand_value = random((min_len_pop * 1000), (max_len_pop * 1000));
  return rand_value;
};


void setup() {
  // put your setup code here, to run once:
   pinMode(relay_pin1, OUTPUT);
   pinMode(relay_pin2, OUTPUT);
   pinMode(relay_pin3, OUTPUT);
   delay(5000);
}

void loop() {

  float btw_pop = rand_btw_pop();
  float len_pop = rand_len_pop();
  int pick_pin = random(1, 4);

  
  if (pick_pin == 1) {
    digitalWrite(relay_pin1, HIGH);
    delay(len_pop);
    digitalWrite(relay_pin1, LOW);
    delay(btw_pop);
  } else if (pick_pin == 2) {
    digitalWrite(relay_pin2, HIGH);
    delay(len_pop);
    digitalWrite(relay_pin2, LOW);
    delay(btw_pop);
  } else if (pick_pin == 3) {
    digitalWrite(relay_pin3, HIGH);
    delay(len_pop);
    digitalWrite(relay_pin3, LOW);
    delay(btw_pop);
  };


}
