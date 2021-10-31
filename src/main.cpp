//Library import
#include <Arduino.h>
#include <SoftwareSerial.h>

//Private variable definiton
SoftwareSerial bluetooth_communication(8, 9);
SoftwareSerial slave_1_communication(2, 3);
SoftwareSerial slave_2_communication(4, 5);

String command, slave_1_command, slave_2_command, pwm1, pwm2, dir1, dir2;
char slave_1_command_array[7], slave_2_command_array[7];

//Private function prototypes
boolean isValid(String command);
void communication_init(void);

void setup()
{
  communication_init();
}

void loop()
{
  command = bluetooth_communication.readStringUntil('F');

  if (isValid(command))
  {
    pwm1 = command.substring(2, 5);
    pwm2 = command.substring(7, 10);
    dir1 = command.substring(1, 2);
    dir2 = command.substring(6, 7);

    slave_1_command = "S" + dir1 + pwm1 + "CF";
    slave_2_command = "S" + dir2 + pwm2 + "CF";

    Serial.println(slave_1_command);
    Serial.println(slave_2_command);

    slave_1_command.toCharArray(slave_1_command_array, 7);
    slave_2_command.toCharArray(slave_2_command_array, 7);

    slave_1_communication.write(slave_1_command_array);
    slave_2_communication.write(slave_2_command_array);

  }
}

// Explicit functions

//Necessary initialization commands for serial communication
void communication_init(void)
{
  Serial.begin(9600);
  slave_1_communication.begin(9600);
  slave_2_communication.begin(9600);
  bluetooth_communication.begin(9600);
}

//This function checks if the received data is valid or not
boolean isValid(String command)
{
  return ((command.charAt(0) == 'S') && (command.length() == 11) && (command.charAt(10) == 'C'));
}