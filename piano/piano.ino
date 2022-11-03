#include <Tone32.h>

// set pin numbers
const int touchPin = 15; 
#define BUZZER_PIN 16
#define BUZZER_CHANNEL 0


// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // initialize the LED pin as an output:
}

void loop(){
  if (touchValue = touchRead(15)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_C4, 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
}

  if (touchValue = touchRead(2)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_D4 , 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
 }

   if (touchValue = touchRead(32)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_E4 , 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
 }

   if (touchValue = touchRead(33)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_F4 , 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
 }

   if (touchValue = touchRead(27)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_G4 , 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
  }
 }

   if (touchValue = touchRead(14)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_A4 , 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    Serial.println("paro");
  }
 }

   if (touchValue = touchRead(12)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_B4 , 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    Serial.println("paro");
  }
 }

   if (touchValue = touchRead(13)){
  if(touchValue < threshold){
    tone(BUZZER_PIN, NOTE_C5 , 100, BUZZER_CHANNEL);
  }
  else{
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
    Serial.println("paro");
  }
 }

}
