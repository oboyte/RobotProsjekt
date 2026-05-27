#include <Arduino.h>
#include <cmath>

#include "hc-sr04.h"
#include "SparkFun_TB6612.h"

using Pin = unsigned char; // Unsigned 8-bit integer, kan large fra 0-255 i verdi.

constexpr float STOP_DISTANCE = 40;

namespace UltraS_Pins {
    constexpr Pin trigger = 18;
    constexpr Pin echo = 19;
}
namespace Motor_Pins {
    constexpr Pin A_IN1 = 27;
    constexpr Pin A_IN2 = 14;
    constexpr Pin B_IN1 = 32;
    constexpr Pin B_IN2 = 33;

    constexpr Pin STBY = 26;

    constexpr Pin PWM_A = 12;   // Speed control for channel A
    constexpr Pin PWM_B = 13;   // -------- || ------------- B

    // these constants are used to allow you to make your motor configuration 
    // line up with function names like forward.  Value can be 1 or -1
    constexpr int offsetA = 1;
    constexpr int offsetB = -1;
}
 //Motors
Motor motor1 = Motor(Motor_Pins::A_IN1, Motor_Pins::A_IN2, Motor_Pins::PWM_A, Motor_Pins::offsetA, Motor_Pins::STBY);
Motor motor2 = Motor(Motor_Pins::B_IN1, Motor_Pins::B_IN2, Motor_Pins::PWM_B, Motor_Pins::offsetB, Motor_Pins::STBY);

//Ultrasound sensor
Ultrasound sensor(UltraS_Pins::trigger, UltraS_Pins::echo);

void setup() {
    Serial.begin(9600);
}

constexpr float wheel_radius = 0.078/2;
constexpr float wheel_RPM { 25 };
constexpr float wheel_to_wheel_len = 0.12; 
constexpr float velocity = wheel_RPM * (2 * M_PI * wheel_radius)/60;
constexpr float time_to_rotate(float degree_radians) { return (degree_radians*wheel_to_wheel_len)/(2*velocity); }

void loop() {
    auto distance = sensor.measure_distance();
    Serial.print("Distansen er: ");
    Serial.println(distance);
    if (distance > STOP_DISTANCE || distance == -1.0) { // Sjekk om avstanden er > 20cm eller om avstanden har fått timeout (vanligvis > 3m)
        forward(motor1, motor2, 150);
    } 
    // Sjekk området rundt for nye kjøreretninger
    else {
        brake(motor1, motor2);
        delay(1000);
        // Snu til høyre for å sjekke om 
        right(motor1, motor2, 255);

        Serial.print("Rotasjonstid: ");
        Serial.println(time_to_rotate(M_PI/2));

        delay(time_to_rotate(M_PI/2) * 1000);
        brake(motor1, motor2);
        delay(1000);
        
        // Er det ledig forran? Ja, gå til neste loop, nei(else), snu -180 grader
        distance = sensor.measure_distance();
        if (distance > STOP_DISTANCE || distance == -1.0) {}
        else {
            left(motor1, motor2, 255);
            delay(time_to_rotate(M_PI) * 1000);
            brake(motor1, motor2);
            delay(1000);

            // Er det ledig forran? Ja, gå til neste loop, nei(else), kjøre tilbake mot orginal retning
            distance = sensor.measure_distance();
            if (sensor.measure_distance() > STOP_DISTANCE || distance == -1.0) {}
            else {
                left(motor1, motor2, 255);
                delay(time_to_rotate(M_PI/2) * 1000);
                brake(motor1, motor2);
            }
        }
    }
    delay(100);
}