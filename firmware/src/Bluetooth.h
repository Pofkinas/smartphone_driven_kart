#include <Arduino.h>

#define BLUETOOTH_BUFFER_SIZE 32
#define BLUETOOTH_DELIMITER '\n'

class Bluetooth {
    private:
        char bluetooth_receive_buffer[BLUETOOTH_BUFFER_SIZE];

    public:
        Bluetooth() {
            bluetooth_receive_buffer[0] = '\0';
        }

    boolean Bluetooth_Receive_Message(char *message) { 
        uint8_t index = 0;
        char read_symbol;

        while (Serial3.available() > 0) {
            read_symbol = Serial3.read();

            Serial.print(read_symbol);

            delay(5);

            if (read_symbol == BLUETOOTH_DELIMITER) {             
                bluetooth_receive_buffer[index] = '\0';
                strcpy(message, bluetooth_receive_buffer);

                Serial.println(message);
                
                return true;
            }

            if (read_symbol == '\n' || read_symbol == '\r') {
                continue;
            }
            
            bluetooth_receive_buffer[index] = read_symbol;
            index++;
        }

        return false;
    }
};
