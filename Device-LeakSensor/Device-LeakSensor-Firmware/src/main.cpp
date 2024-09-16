#include <Arduino.h>
#include <NodeControllerCore.h>

#define NODE_ID 0xA2            // 162
#define LEAK_MESSAGE_ID 0x0A00 // 2560
#define LEVEL_MESSAGE_ID 0x0A01  // 2561

#define debuging

#define LEAK_SENSOR_PIN A0
#define LEVEL_SWITCH_PIN 2



// Node controller core object
NodeControllerCore core;

// put function declarations here:

// Function to receive messages
void send_message(uint8_t nodeID, uint16_t messageID, uint64_t data)
{
  ifdef debuging
  Serial.print("Received message with ID: ");
  Serial.println(messageID, HEX);
  Serial.print("Data: ");
  for (int i = 0; i < len; i++)
  {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  endif
}

// Function to check the leak sensor
void chkLeakSensor()
{
  int sensorValue = analogRead(LEAK_SENSOR_PIN);
  Serial.println(sensorValue);
  if(sensorValue > 1000)
  {
    core.Send(NODE_ID, LEAK_MESSAGE_ID, 0);
    ifdef debuging
    Serial.println("Leak Detected");
    endif
  }
  else
  {
    core.Send(NODE_ID, LEAK_MESSAGE_ID, 1);
    ifdef debuging
    Serial.println("No Leak Detected");
    endif
  }
}

// Function to check the level switch
void chkLevelSwitch()
{
  int levelSwitchValue = digitalRead(LEVEL_SWITCH_PIN);
  if(levelSwitchValue == LOW)
  {
    core.Send(NODE_ID, LEVEL_MESSAGE_ID, 0);
    ifdef debuging
    Serial.println("Level Switch is triggered");
    endif
  }
  else
  {
    core.Send(NODE_ID, LEVEL_MESSAGE_ID, 1);
    ifdef debuging
    Serial.println("Level Switch is not triggered");
    endif
  }
}

void setup() 
{
  // put your setup code here, to run once:

  // Initialize serial communication
  Serial.begin(115200);
  
  pinMode(LEVEL_SWITCH_PIN, INPUT_PULLUP);
  pinMode(LEAK_SENSOR_PIN, INPUT);

    // Create the node controller core object
  core = NodeControllerCore();
  Serial.println("test");
  // Initialize the node controller core object
  if (core.Init(receive_message, NODE_ID))
  {
    Serial.println("Driver device initialized");
  }
  else
  {
    Serial.println("Failed to initialize driver");
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  

}

// put function definitions here:
