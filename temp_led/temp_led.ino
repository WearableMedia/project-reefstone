#include <Adafruit_CircuitPlayground.h>
#include "Interval.h"
Interval ledTimer;
Interval tempTimer;

float tempC, tempF;
float threshold = 25.6;

int brightness = 0;
int speed = 1;

bool toggle = true;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 20 * i,    20 * i,    20 * i);
  }
  tempTimer.setInterval(checkTemp, 1000);
  ledTimer.setInterval(fade, 100);

}

void loop() {
  tempTimer.check();
  ledTimer.check();
  if (tempC < threshold) {
    toggle = true;
  } else {
    toggle = false;
  }

  if (CircuitPlayground.slideSwitch()) {
    //sensor demo mode
    if (CircuitPlayground.leftButton()) {
      threshold = tempC+1;
    }
  } else {
    //animation loop mode
    if (CircuitPlayground.rightButton()) {
      toggle = true;
    }else{
      toggle = false;
    }
  }



}

void fade() {
  if (toggle == true) {
    brightness += speed;
    if (brightness >= 10 || brightness <= 0) {
      speed = -1 * speed;
    }
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 20 * brightness,    20 * brightness,    20 * brightness);
    }
  } else {
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 0,   0,    0);
    }
  }

}

void checkTemp() {
  tempC = CircuitPlayground.temperature();
  tempF = CircuitPlayground.temperatureF();

  Serial.print("tempC: ");
  Serial.print(tempC);
  Serial.print("  tempF: ");
  Serial.println(tempF);

}

