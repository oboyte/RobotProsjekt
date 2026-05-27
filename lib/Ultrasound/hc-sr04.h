#pragma once
#include "Arduino.h"

// 8-bit unsigned integer (Lagrer tall fra 0 til 255, 1 byte i størrelse)
using Pin = unsigned char;

class Ultrasound {
    Pin trigger_pin { };
    Pin echo_pin { };
    unsigned int duration { };
    float distance { };

    void send_start_pulse() {
        digitalWrite(trigger_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger_pin, LOW);
    }
    
    int get_distanse() {
        duration = pulseIn(echo_pin, HIGH);
        
        // Timeout, out of range
        if(duration>=38000) return -1;
        else {
            return duration/58;
        }
    }
public:
    Ultrasound(Pin TRIGGER_PIN, Pin ECHO_PIN) 
    : trigger_pin { TRIGGER_PIN }, echo_pin { ECHO_PIN } {
        pinMode(trigger_pin, OUTPUT);
        digitalWrite(trigger_pin, LOW);

        delayMicroseconds(2);

        pinMode(echo_pin, INPUT);
        delay(6000);
    }

    float measure_distance() {
        send_start_pulse();
        distance = get_distanse();

        return distance;
    }
};