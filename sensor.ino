#include <mcp_can.h>
#include <SPI.h>
#include "DHT.h"

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

#define DHTPIN 2       // DHT data pin connected to D2
#define DHTTYPE DHT11  // or DHT22
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ)) {
    Serial.println("CAN BUS init Failed");
    delay(100);
  }
  Serial.println("CAN BUS init OK!");
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  if (millis() - lastSend > 2000) {  // send every 2s
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Convert to int (x10 for 1 decimal precision)
    int tempInt = (int)(temperature * 10);
    int humInt  = (int)(humidity * 10);

    byte data[4] = {
      (tempInt >> 8) & 0xFF, tempInt & 0xFF,
      (humInt >> 8) & 0xFF, humInt & 0xFF
    };

    CAN.sendMsgBuf(0x200, 0, 4, data);

    Serial.print("Sent -> Temp: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    lastSend = millis();
  }
}
