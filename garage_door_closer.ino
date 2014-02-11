#include <avr/sleep.h>

const int speaker = 0;
const int led     = 1;
const int button  = 2;
const int door    = 3;
const int opener  = 4;
const int beepTone = 3700;

int buttonState = 0;
int doorState  = 0;

void setup(){
  pinMode(speaker,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(opener,OUTPUT);
  pinMode(button,INPUT);
  pinMode(door,INPUT);
  digitalWrite(button,HIGH); 
  digitalWrite(door,HIGH);
}

void pingButton(int pause){
  digitalWrite(led,HIGH);
  for(int i=0;i<1;i++){
    tone(speaker,beepTone);
    delay(150);
    noTone(speaker);
    delay(30);
  }
  delay(330);
  digitalWrite(led,LOW);
  delay(pause);
}

void blinkError(int errorCount){
  for(int i=0; i<errorCount; i++){
      digitalWrite(led,HIGH);
      delay(150);
      digitalWrite(led,LOW);
      delay(75);
  }
}
void triggerOpener(){
  digitalWrite(opener,HIGH);
  delay(400);
  digitalWrite(opener,LOW);
}
void dummyWake(){
}

void loop(){
  buttonState = digitalRead(button);
  doorState = digitalRead(door);
  
  if(buttonState == LOW){
    delay(5);
    buttonState = digitalRead(button);
    doorState = digitalRead(door);
    if(buttonState == LOW && doorState == LOW){
      for(int i=28; i>=0; i--){
        int pause = (i/7*60);
        pingButton(pause);
      }
      triggerOpener();
      play_rtttl(song);
    }else{
      blinkError(3);
    }
  }
  attachInterrupt(0, dummyWake, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  ADCSRA &= ~(1 << ADEN);// Disable all peripheral power
  sleep_mode(); 
  sleep_disable();// first thing after waking from sleep is disable sleep.
}
