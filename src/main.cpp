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
    /*
    float distance = sensor.measure_distance();
    Serial.print("Distansen er: ");
    if (distance == -1) {
        Serial.println("Error");
    } else {
        Serial.print(distance);
        Serial.println("cm");
    }
    delay(1000);
    */
    
    //Use of the drive function which takes as arguements the speed
    //and optional duration.  A negative speed will cause it to go
    //backwards.  Speed can be from -255 to 255.  Also use of the 
    //brake function which takes no arguements.
    motor1.drive(255,1000);
    motor1.drive(-255,1000);
    motor1.brake();
    delay(1000);
    
    //Use of the drive function which takes as arguements the speed
    //and optional duration.  A negative speed will cause it to go
    //backwards.  Speed can be from -255 to 255.  Also use of the 
    //brake function which takes no arguements.
    motor2.drive(255,1000);
    motor2.drive(-255,1000);
    motor2.brake();
    delay(1000);
    
    //Use of the forward function, which takes as arguements two motors
    //and optionally a speed.  If a negative number is used for speed
    //it will go backwards
    forward(motor1, motor2, 150);
    delay(1000);
    
    //Use of the back function, which takes as arguments two motors 
    //and optionally a speed.  Either a positive number or a negative
    //number for speed will cause it to go backwards
    back(motor1, motor2, -150);
    delay(1000);
    
    //Use of the brake function which takes as arguments two motors.
    //Note that functions do not stop motors on their own.
    brake(motor1, motor2);
    delay(1000);
    
    //Use of the left and right functions which take as arguements two
    //motors and a speed.  This function turns both motors to move in 
    //the appropriate direction.  For turning a single motor use drive.
    left(motor1, motor2, 100);
    delay(1000);
    right(motor1, motor2, 100);
    delay(1000);
    
    //Use of brake again.
    brake(motor1, motor2);
    delay(1000);
    
}