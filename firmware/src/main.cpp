#include <Arduino.h>
#include <cstring>
#include "Command.h"
#include "Bluetooth.h"

#define TIMEOUT 2000

Command g_command = Command();
Bluetooth g_bluetooth = Bluetooth();

long g_last_time = 0;

boolean g_reset = 0;

char g_uart_buffer[UART_BUFFER_SIZE];
char g_bluetooth_command[BLUETOOTH_BUFFER_SIZE];

void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);

    Serial.println("<Arduino is ready>");
    
    g_command.Reset();
}

void loop() {
    if (g_command.Uart_Receive_Message(g_uart_buffer) == true) {
      g_command.Parse_Message(g_uart_buffer);

      g_command.Reset_Buffer(g_uart_buffer, sizeof(g_uart_buffer));
    }

    if (g_bluetooth.Bluetooth_Receive_Message(g_bluetooth_command) == true) {
      g_last_time = millis();
      g_reset = 0;
      
      g_command.Parse_Message(g_bluetooth_command);

      g_command.Reset_Buffer(g_bluetooth_command, sizeof(g_uart_buffer));
    }

    if ((millis() - g_last_time > TIMEOUT) && g_reset == 0) {
      g_command.Reset();

      g_reset = 1;
    }
}
