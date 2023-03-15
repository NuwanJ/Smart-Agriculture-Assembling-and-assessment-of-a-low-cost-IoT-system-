#include "define.h"

int readCount;

void setup()
{

   beginGPIO();
   Serial.begin(115200);
   Serial.println(CONTROLLER_ID);

   blinkLED(pin_indicator[0], 1);

   beginWiFi();
   beginOTA();
   beginMQTT();
   // beginSensors();

   mqttLog(1, "Control station started.");
   updateInputs();
}

void loop()
{

   if (!client.connected())
   {
      // safeShutdown();
      reconnect();
   }
   client.loop();

#ifdef ENABLE_OTA_UPLOAD
   ArduinoOTA.handle();
#endif
}
