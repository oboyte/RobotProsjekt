#include <Arduino.h>

#include "hc-sr04.h"

using Pin = unsigned char; // Unsigned 8-bit integer, kan large fra 0-255 i verdi.

namespace UltraS_Pins {
    constexpr Pin trigger = 16;
    constexpr Pin echo = 17;
}

namespace Motor_Pins {
    constexpr Pin A_IN1 = 34;
    constexpr Pin A_IN2 = 35;
    constexpr Pin B_IN1 = 32;
    constexpr Pin B_IN2 = 33;

    constexpr Pin PWM_A = 12;   // Speed control for channel A
    constexpr Pin PWM_B = 13;   // -------- || ------------- B
}

Ultrasound sensor(UltraS_Pins::trigger, UltraS_Pins::echo);

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