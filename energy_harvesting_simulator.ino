// Initialize ChainableLED component
#include <ChainableLED.h>
#define NUM_LEDS  3
ChainableLED leds(7, 8, NUM_LEDS);
const int buttonPin = 2;


// define the variable
int Value;
int lightValue;
unsigned long sendStartMillis;
unsigned long buttonStartMillis;
unsigned long currentMillis;
const unsigned long sendPeriod = 8000;
const unsigned long buttonPeriod = 1000;
int buttonState = 0;
int printState = 0;


void setup() {
  leds.init();
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  sendStartMillis = millis();
  buttonStartMillis = millis();
}



void loop() {
  Value = analogRead(A0);
  //  Serial.println(Value);
  buttonState = digitalRead(buttonPin);

  // Map the Value to 1,2 and 3
  if (Value >= 700)
    lightValue = 3;
  else if (Value < 700 && Value >= 300)
    lightValue = 2;
  else if (Value < 300)
    lightValue = 1;

  currentMillis = millis();
  sendEnergy();   // Switch Case to control the light as well as the signal sending
  if (buttonState == HIGH && printState != 1 && currentMillis - buttonStartMillis >= buttonPeriod) {
    Serial.println ("<4>");
    printState = 1;
    buttonStartMillis = millis();
  } else if (buttonState == LOW) {
    printState = 0;
  }
  // Send the signal for every 8s
  //  delay(8000);
}

void sendEnergy()
{
  if (currentMillis - sendStartMillis >= sendPeriod) {
    switch (lightValue) {
      case 1:
        for (int i = 0; i < NUM_LEDS; i++)
        {
          if (i < lightValue)
            leds.setColorRGB(i, 255, 0, 0);
          else
            leds.setColorRGB(i, 0, 0, 0);
        }
        Serial.println("<1>");
        break;
      case 2:
        for (int i = 0; i < NUM_LEDS; i++)
        {
          if (i < lightValue)
            leds.setColorRGB(i, 255, 255, 0);
          else
            leds.setColorRGB(i, 0, 0, 0);
        }
        Serial.println("<2>");
        break;
      case 3:
        for (int i = 0; i < NUM_LEDS; i++)
        {
          if (i <= lightValue)
            leds.setColorRGB(i, 0, 0, 255);
          else
            leds.setColorRGB(i, 0, 0, 0);
        }
        Serial.println("<3>");
        break;
    }

    sendStartMillis = millis();
  }
}

//void buttonEnergy()
//{
//    if (currentMillis - buttonStartMillis >= buttonPeriod) {
//
//    }
//}
