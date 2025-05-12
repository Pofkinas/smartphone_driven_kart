#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 3

#define SERVO_DEFAULT_POSITION 90
#define MAX_ANGLE 155
#define MIN_ANGLE 35

class Servo_Control {
    private:
        Servo myServo;
        int servo_angle = 0;
    public:

    Servo_Control() {
        myServo.attach(SERVO_PIN);
        myServo.write(SERVO_DEFAULT_POSITION);
    }

    int Get_Angle(){
        return servo_angle;
    }

    void Set_Angle(int servo_angle2){
        Serial.print("Servo angle: ");
        Serial.println(servo_angle2);

        servo_angle = constrain(servo_angle2, MIN_ANGLE, MAX_ANGLE);

        myServo.write(servo_angle);

        delay(15);
    }
};