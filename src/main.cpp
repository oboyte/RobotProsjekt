#include <Arduino.h>

#include "hc-sr04.h"
#include "SparkFun_TB6612.h"

using Pin = unsigned char; // Unsigned 8-bit integer, kan large fra 0-255 i verdi.

namespace UltraS_Pins {
    constexpr Pin trigger = 16;
    constexpr Pin echo = 17;
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

void loop() {
    if (sensor.measure_distance() > 20) {
        forward(motor1, motor2);
    }
    
}