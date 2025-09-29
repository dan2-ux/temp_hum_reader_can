#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

const int LED_PIN = 7;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ)) {
    Serial.println("CAN BUS init Failed");
    delay(100);
  }
  Serial.println("CAN BUS init OK!");
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    long unsigned int rxId;
    unsigned char len;
    unsigned char rxBuf[8];
    CAN.readMsgBuf(&rxId, &len, rxBuf);

    if (rxId == 0x200 && len == 4) {
      int tempInt = (rxBuf[0] << 8) | rxBuf[1];
      int humInt  = (rxBuf[2] << 8) | rxBuf[3];

      float temperature = tempInt / 10.0;
      float humidity    = humInt / 10.0;

      Serial.print("Received -> Temp: ");
      Serial.print(temperature);
      Serial.print(" °C, Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");

      // Threshold check
      if (temperature > 40.0 && humidity > 70.0) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("⚠️ Threshold exceeded! LED ON");
      } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("Conditions normal. LED OFF");
      }
    }
  }
}
