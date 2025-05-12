#include <Arduino.h>

#define MOTOR_PIN 66
#define MOTOR_DIRECTION_PIN 22

#define DEFAULT_DIRECTION 0
#define DEFAULT_MODE 0

#define SLOW_MODE_MULTIPLIER 0.5
#define MAX_SPEED 180

class Motor_Control{
    private:
        uint8_t motor_mode = DEFAULT_MODE;
        uint8_t motor_direction = DEFAULT_DIRECTION;
    public:

    Motor_Control() {
        pinMode(MOTOR_DIRECTION_PIN, OUTPUT);
    }

    void Set_Speed(uint8_t speed, uint8_t direction){
        int normalized_speed = Calculate_Motor_Speed(speed);
        
        Serial.print("Motor mode: ");
        Serial.print(motor_mode);
        Serial.print("; Motor speed: ");
        Serial.print(normalized_speed);
        Serial.print("; Direction: ");
        Serial.println(direction);

        motor_direction = direction;

        digitalWrite(MOTOR_DIRECTION_PIN, direction);
        analogWrite(MOTOR_PIN, normalized_speed);
    }

    int Calculate_Motor_Speed(int percentage) {
        if (motor_mode == 1) {
            percentage = percentage * SLOW_MODE_MULTIPLIER;
        }

        if (percentage <= 2) return 0; 
            if (percentage >= 100) return MAX_SPEED;
                int speed = 100 + (percentage * (MAX_SPEED - 91)) / 100;
                return speed;
    }

    void Set_Mode(uint8_t mode) {
        motor_mode = mode;
    }

    uint8_t Get_Direction() {
        return motor_direction;
    }
};
