int buttonPin = 4; // GPIO 4 (D2) for ESP8266 https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

void setup() {
   // Define pin #12 as input and activate the internal pull-up resistor
   pinMode(buttonPin, INPUT_PULLUP);
   // Define pin #13 as output, for the LED
   pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

void loop(){
   // Read the value of the input. It can either be 1 or 0
   int buttonValue = digitalRead(buttonPin);
   if (buttonValue == LOW){
      // If button pushed, turn LED on
      digitalWrite(LED_BUILTIN,HIGH);
   } else {
      // Otherwise, turn the LED off
      digitalWrite(LED_BUILTIN, LOW);
   }
/*
   digitalWrite(LED_BUILTIN, LOW);
   delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);*/

}