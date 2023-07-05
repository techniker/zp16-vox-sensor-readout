#include <Arduino.h>

void setup() {
  Serial.begin(9600); // Initialize the serial communication at the desired baud rate
  Serial1.begin(9600, SERIAL_8N1, 26, 32); //Comms to VOX Sensor
}

void loop() {

  Serial.print("LOOP");
  
  if (Serial1.available()) {
    unsigned char serialData[9];

    // Read the incoming serial data into the buffer
    for (int i = 0; i < 9; i++) {
      serialData[i] = Serial1.read();
    }

    // Calculate the checksum
    int checksum = -((serialData[0] + serialData[1] + serialData[2] + serialData[3] + serialData[4] + serialData[5] + serialData[6] + serialData[7]) & 0xFF) + 1;

    // Check if the calculated checksum matches the received checksum
    if (checksum == serialData[8]) {
      // Calculate the gas concentration
      unsigned int gasConcentration = (serialData[2] << 8) + serialData[3];

      // Calculate the full scale gas concentration
      unsigned int fullScale = (serialData[6] << 8) + serialData[7];

      // Display the values if the checksum is valid
      printf("Start Byte: 0x%02X\n", serialData[0]);
      printf("Comm: 0x%02X\n", serialData[1]);
      printf("High byte of gas concentration: 0x%02X\n", serialData[2]);
      printf("Low byte of gas concentration: 0x%02X\n", serialData[3]);
      printf("Decimal point: 0x%02X\n", serialData[4]);
      printf("Reserved: 0x%02X\n", serialData[5]);
      printf("High byte of full scale: 0x%02X\n", serialData[6]);
      printf("Low byte of full scale: 0x%02X\n", serialData[7]);
      printf("Checksum: 0x%02X\n", serialData[8]);
      printf("Gas Concentration: %u MG/M3\n", gasConcentration);
      printf("Full Scale Gas Concentration: %u MG/M3\n", fullScale);
    }
    else {
      // Invalid checksum, display an error message or take appropriate action
      printf("Invalid checksum!\n");
    }
  }
}
