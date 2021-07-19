int button = 0;
byte startcode = 97; //to tell the computer to play song (arbitrary value)
byte stopcode = 23 ; // to tell the computer to stop song (arbitrary value)

const int sensor_pin = A0; // the mic is connected to A0 analog pin
const int threshold = 320; // threshold value for sound
const int ledarray[] = {
  2,3,4,5,6,7,8,9,10,11}; // 10 led bar
const int ledcount = 10; // number of LEDs
const int waiting_pin = 12 ;
const long wait_time = 5000.0; //how long after trigger to wait before playing music 
const long cancel_time = 4000.0; // waiting time before trigger

int sensor_value = 0; // variable to store the value read from the sensor pin
int led_level = 0; 
boolean waiting = 0;
boolean playing = 0;
long wait_start; // when trigger initiated waiting
long wait_duration; // how long we have been waiting
long cancel_start; // time of last trigger
long cancel_duration; 

void setup() {
  for(int i=0; i<ledcount; i++)
  {
    pinMode(ledarray[i], OUTPUT);
  }
  pinMode(waiting_pin, OUTPUT);
  Serial.begin(9600);       // for using the serial port at 9600 baud rate
}

void loop() {
  sensor_value = analogRead(sensor_pin);    
  Serial.println(sensor_value); // printing to serial monitor
  
  led_level = map(sensor_value, 200, threshold, 0, ledcount); // map the result to a range from 0 to the number of LEDs

  for (int i = 0; i < ledcount; i++) {
    if (i < led_level) {
      digitalWrite(ledarray[i], HIGH);
    } 
    else {
      digitalWrite(ledarray[i], LOW); 
    }
  }
  
  // if over the threshhold
  if (led_level == ledcount) {
    cancel_start = millis();
    if (!waiting) {
      waiting = 1;
      digitalWrite(waiting_pin, HIGH);
      wait_start = millis();
    }
  }
  
  if (waiting) {
    cancel_duration = millis() - cancel_start;
    wait_duration = millis() - wait_start;
    if (cancel_duration > cancel_time) {
      waiting = 0;
      digitalWrite(waiting_pin, LOW);
    }
    else if (wait_duration > wait_time) { //Now we will play music
      waiting = 0;
      digitalWrite(waiting_pin, LOW);
      digitalWrite(ledarray[9], HIGH);
      playing = 1;
      button = 1;
      if (digitalRead(button)){
        Serial.write(startcode);
        delay(15000); //play music for 15 secs
        Serial.write(stopcode);      
      }
      digitalWrite(ledarray[9], LOW);
    }
  }
}
