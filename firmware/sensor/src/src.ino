
#include "define.h"

int readCount;

void setup()
{
   Serial.begin(115200);

   beginGPIO();
   successReport(SUCCESS_DEVICE_BEGIN);

   beginEEPROM();

   // printf("\n\nWrite into EEPROM\n"); eepromWrite(EEPROM_ADDR_ID,39);

   printf("\nStarted the device\n\n");

   beginWiFi();

   beginDHTSensors();
   beginLightSensor();

   // beginOTA();
   beginMQTT();
}

// #define OLD_MODE

void loop()
{
   Serial.println("Reading...");
   if (!client.connected())
      reconnect();

   client.loop();
   delay(100);

#ifdef OLD_MODE
   if ((millis() - lastMsg) > SENSOR_UPLOAD_INTERVAL)
   {
      updateCycle(0);

      readCount++;
      if (readCount > RESTART_READING_COUNT)
      {
         // Restart the device after this count of readings for better stability
         ESP.restart();
      }
      lastMsg = millis();
   }
#endif

#ifdef ENABLE_OTA_UPLOAD
   ArduinoOTA.handle();
#endif

#ifdef ENABLE_DEEP_SLEEP
   esp_deep_sleep(1000000LL * SLEEP_DURATION);
#endif
}

void beginGPIO()
{
   pinMode(PIN_LED_G, OUTPUT);
   pinMode(PIN_LED_R, OUTPUT);
   pinMode(PIN_LED_B, OUTPUT);
}

void updateCycle(unsigned int seqNo)
{
   readDHT0();
   readDHT1();
   readDHT2();
   readLight();
   // readSoilMoisture();
   Serial.println();

   mqttPublish(seqNo);
}
