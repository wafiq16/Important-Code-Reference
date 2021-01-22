int value = 0;
int variableResistor = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(2000000);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A7,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  if(Serial.available()>0)
  {
    variableResistor = analogRead(A7);
    Serial.println(variableResistor);
//    Serial.write(variableResistor);
    delay(50);
    value=double(Serial.read());
    if(value == 1){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//      delay(1000);                       // wait for a second
    }
    else if(value == 0){
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//      delay(1000);                       // wait for a second
    }
  }
}
