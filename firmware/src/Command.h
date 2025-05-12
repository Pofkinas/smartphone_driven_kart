#include <Arduino.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include "Motor_Control.h"
#include "Servo_Control.h"

#define UART_BUFFER_SIZE 32
#define UART_DELIMITER '\n'
#define UART_SPLIT_TOKEN ";"

class Command {
    private:
      Motor_Control motor;
      Servo_Control servo;
      char uart_receive_buffer[UART_BUFFER_SIZE];
    
    public:
      Command() {
        uart_receive_buffer[0] = '\0'; 
        
        motor = Motor_Control();
        servo = Servo_Control();

        motor.Set_Mode(DEFAULT_MODE);
      }

      void Reset() {
        motor.Set_Speed(0, DEFAULT_DIRECTION);
        servo.Set_Angle(SERVO_DEFAULT_POSITION);
      }

      boolean Uart_Receive_Message(char *message) {
        uint8_t index = 0;
        char read_symbol;
        
        while (Serial.available() > 0) {
          read_symbol = Serial.read();
          delay(2);

          if (read_symbol == UART_DELIMITER) {
            uart_receive_buffer[index] = '\0';
            index = 0;

            strcpy(message, uart_receive_buffer);
            
            return true;
          }
            uart_receive_buffer[index] = read_symbol;
            index++;
          }

        return false;
      }

      boolean Reset_Buffer(char *buffer, size_t size) {
        memset(buffer, '\0', size);

        return true;
      }

      boolean Parse_Message(char *message) {
        char* token = strtok(message, UART_SPLIT_TOKEN);
        servo.Set_Angle(atoi(token));
        
        char* motor_speed = strtok(NULL, UART_SPLIT_TOKEN);

        char* motor_direction = strtok(NULL, UART_SPLIT_TOKEN);

        char* motor_mode = strtok(NULL, UART_SPLIT_TOKEN);

        char* motor_stop = strtok(NULL, UART_SPLIT_TOKEN);

        if (atoi(motor_stop) == 1) {
          motor.Set_Speed(0, atoi(motor_direction));

          Serial.println("Motor stopped");
          
          return true;
        }

        if (motor.Get_Direction() != atoi(motor_direction)) {
          motor.Set_Mode(atoi(motor_mode));
          motor.Set_Speed(0, atoi(motor_direction));

          delay(1000);

          motor.Set_Speed(atoi(motor_speed), atoi(motor_direction));

          return true;
        }

        motor.Set_Mode(atoi(motor_mode));
        motor.Set_Speed(atoi(motor_speed), atoi(motor_direction));

        return true;
      }
};
