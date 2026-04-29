#include <Arduino.h>

#include "hc-sr04.h"

constexpr int trigger = 16;
constexpr int echo = 17;

Ultrasound sensor(trigger, echo);

void setup() {
    Serial.begin(9600);
}

void loop() {
    float distance = sensor.measure_distance();
    Serial.print("Distansen er: ");
    if (distance == -1) {
        Serial.println("Error");
    } else {
        Serial.print(distance);
        Serial.println("cm");
    }
    delay(1000);
}