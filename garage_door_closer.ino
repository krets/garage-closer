int led = 11;
int button = 10;
int door = 9;
int opener = 8;

int buttonState = 0;
int doorState = 0;


void setup(){
  pinMode(opener,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(button,INPUT);
  pinMode(door,INPUT);
  digitalWrite(button,HIGH);
  digitalWrite(door,HIGH);
}

void pingButton(int pause){
  int timer=2; //4ms will make it take 1 second to fade out.
  for(int brightness = 255; brightness>=0; brightness--){
    analogWrite(led,brightness);
    delay(timer);
  }
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

void loop(){
  buttonState = digitalRead(button);
  doorState = digitalRead(door);
  
  if(buttonState == LOW){
    delay(5);
    buttonState = digitalRead(button);
    if(buttonState == LOW && doorState == LOW){
      for(int i=28; i>=0; i--){
        int pause = (i/7*60);
        pingButton(pause);
      }
      triggerOpener();
    }else{
      blinkError(3);
    }
  }
}
