#include "sensors.h"

using namespace sensors;

const int on_off_switch = A0;
int state = 0;

const int rly1 = 10;
const int rly2 = 11;
const int rly3 = 12;
const int rly4 = 13;

bool is_on = false;

const int checkpin = 7;
int valve;
//int checkpin2 = 4;
int heat;
int prev_heat = 1;
int heat_state = 1;

int hot_dur = 3000;
int cold_dur = 6000;

int temp_offset = 5;
int target_temp = 40;
int actual_target_temp = target_temp - temp_offset;

void energize(int pin, bool state){
  digitalWrite(pin, !state);
  }

void setup() {
  Serial.begin(9600);
  
//  ads_init();
  sensors_init();
//  pinMode(on_off_switch, INPUT);
  pinMode(rly1, OUTPUT);
  pinMode(rly2, OUTPUT);
  pinMode(rly3, OUTPUT);
  pinMode(rly4, OUTPUT);

  pinMode(checkpin, INPUT);
//  pinMode(checkpin2, INPUT);

  energize(rly1, LOW);
  energize(rly2, LOW);
  energize(rly3, LOW);
  energize(rly4, LOW);
  state = digitalRead(on_off_switch);
}

int n_cycle = 0;

void loop() {
  state = analogRead(on_off_switch);
  float current_temp;
  current_temp = get_temp();
  Serial.print("Temp: ");
  Serial.print(current_temp);
  Serial.println(" degC");
  delay(200);
  if (state < 200){
    Serial.print("State: ");
    Serial.println("HDH OFF");  
    energize(rly1, LOW);
    energize(rly2, LOW);
    energize(rly3, LOW);
    energize(rly4, LOW);
    }
  
  else if (state > 300){
    Serial.print("State: ");
    Serial.println("HDH ON");
    Serial.println("=====");
    Serial.print("Cycle: ");
    Serial.println(n_cycle);

    energize(rly4, HIGH);
    Serial.print("HEATING: ");
    Serial.print(hot_dur/1000);
    Serial.println(" s");
    delay(hot_dur);
    
    energize(rly4, LOW);
    Serial.print("PASSIVE COOLING");
    Serial.print(cold_dur/1000);
    Serial.println(" s");
    delay(cold_dur);
    
    n_cycle = n_cycle + 1;
    
    if (n_cycle > 3){
      hot_dur = 2000;
      cold_dur = 5000;
      }
    if (n_cycle > 15){
      hot_dur = 1500;
      cold_dur = 6000;
      }
    if (n_cycle > 50){
      hot_dur = 1000;
      cold_dur = 6000;
      }

    if (n_cycle > 100){
      hot_dur = 1000;
      cold_dur = 7000;
      }
  }
  
  
}
