#include <Arduino.h>

// Reference - https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino

struct {
  
    int red[2] = {3,9};
    int green[2] = {5,10};
    int blue[2] = {6,11};
    
} pins;

struct {
  
    int min_btw_breath = 3; //normalized to seconds
    int max_btw_breath = 5;

    int min_breath_len = 4; //still milliseconds
    int max_breath_len = 10;
    
} info;


void setup() { 
    Serial.begin(9600);
    for (int ii = 0;ii<sizeof(pins.red)/sizeof(int);ii++){
      pinMode(pins.red[ii],OUTPUT);
      digitalWrite(pins.red[ii], LOW);
    }
    for (int ii = 0;ii<sizeof(pins.green)/sizeof(int);ii++){
      pinMode(pins.green[ii],OUTPUT);
      digitalWrite(pins.green[ii], LOW);
    }
    for (int ii = 0;ii<sizeof(pins.blue)/sizeof(int);ii++){
      pinMode(pins.blue[ii],OUTPUT);
      digitalWrite(pins.blue[ii], LOW);
    }
}  

int get_breath_legth() {
  return random(info.min_breath_len, info.max_breath_len);
};

int get_btw_breath() {
  int temp_btw = random(info.min_btw_breath, info.max_btw_breath);
  return temp_btw * 1000;
};

void rgb(int color1[], int color2[], int mix1, int mix2) {
    
    float breathe_smoothe = 500;

    if (mix1 == 1 && mix2 == 0) {
      for (int ii=0;ii<breathe_smoothe;ii++){
        float pwm_val = 255.0*(1.0 -  abs((2.0*(ii/breathe_smoothe))-1.0));
        for (int pin = 0; pin <= sizeof(color1) - 1; pin++) {
          analogWrite(color1[pin],int(pwm_val));
        }
        delay(get_breath_legth());
        Serial.println(int(pwm_val));
      }  
      
    } else if (mix1 == 1 && mix2 == 1) {
      for (int ii=0;ii<breathe_smoothe;ii++){
        float pwm_val = 255.0*(1.0 -  abs((2.0*(ii/breathe_smoothe))-1.0));
        for (int pin = 0; pin <= sizeof(color1) - 1; pin++) {
          analogWrite(color1[pin],int(pwm_val));
          analogWrite(color2[pin],int(pwm_val));
        }
        delay(get_breath_legth());
        Serial.println(int(pwm_val));
      }
    };
    
}


void loop() { 
    int num_colors = 6;
    int color_pick = random(1,7);

    if (color_pick == 1) {
      rgb(pins.red, pins.blue, 1, 0);
      delay(get_btw_breath());  
    } else if (color_pick == 2) {
      rgb(pins.blue, pins.red, 1, 0);
      delay(get_btw_breath());
    } else if (color_pick == 3) {
      rgb(pins.green, pins.red, 1, 0);
      delay(get_btw_breath());
    } else if (color_pick == 4) {
      rgb(pins.red, pins.blue, 1, 1);
      delay(get_btw_breath());
    } else if (color_pick == 5) {
      rgb(pins.red, pins.green, 1, 1);
      delay(get_btw_breath());
    } else if (color_pick == 6) {
      rgb(pins.blue, pins.green, 1, 1);
      delay(get_btw_breath());
    }
    
}
