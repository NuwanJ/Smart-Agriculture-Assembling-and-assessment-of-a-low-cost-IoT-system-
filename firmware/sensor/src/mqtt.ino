

void beginMQTT() {

   client.setServer(MQTT_SERVER, MQTT_PORT);
   client.connect(MQTT_CLIENT + deviceId, MQTT_USERNAME, MQTT_PASSWORD);
   client.setCallback(callback);

   if (!client.connected()) reconnect();
   else subscribe();
}

void mqttPublish(unsigned int seqId) {

   sprintf(tempString, "{\"id\":\"%d\",\"s\":\"%d\",\"t\":{\"0\":\"%.2f\",\"1\":\"%.2f\",\"2\":\"%.2f\"},\"h\": {\"0\":\"%.2f\",\"1\":\"%.2f\",\"2\":\"%.2f\"},\"l\":\"%.3f\"}",
   deviceId, seqId, temp[0], temp[1], temp[2], humidity[0], humidity[1], humidity[2], lightIntensity);

   int resp = client.publish(TOPIC_PUBLISH, tempString, true);
   Serial.printf("Publish: %d \n\t%s\n", resp, tempString);

   if (resp == 1) successReport(SUCCESS_MQTT_PUBLISH);
   else errorReport(ERROR_MQTT_PUBLISH_FAILED);

}

void subscribe() {
   client.subscribe(TOPIC_MSG);  // Shared message channel
   client.subscribe(TOPIC_OTA);
   client.subscribe(TOPIC_READ);

   sprintf(TOPIC_OTA_DEVICE, "v1/sensor/ota/%d", deviceId);
   client.subscribe(TOPIC_OTA_DEVICE);
}

void callback(char* topic, byte* message, unsigned int length) {
   char msg[length + 1];
   msg[length] = '\0';

   for (int i = 0; i < length; i++) {
      msg[i] =  (char)message[i];
   }
   Serial.printf("\n>> topic: %s msg:%s\n", topic, msg);

   if (String(topic).equals(TOPIC_READ)) {
      // Do a sensor reading and update
      unsigned int seqNo, sleepDuration;

      if (2 == sscanf(msg, "%d %d",  &seqNo, &sleepDuration)) {
         // A valid request
         printf("%d %d\n", seqNo, sleepDuration);
         updateCycle(seqNo);

         if (sleepDuration != 0) { // duration in seconds
            //Serial.printf("Going to sleep about %d seconds", (sleepDuration-20));
            esp_deep_sleep(1000000LL * (sleepDuration - 20));
         }
      } else {
         printf("Invalid > %s\n", msg);
      }
   } else if (String(topic).equals(TOPIC_MSG)) {
      successReport(SUCCESS_MQTT_MSG_IN);

      if (String(msg).equals("RESTART")) {
         ESP.restart();
      }

   } else if (String(topic).equals(TOPIC_OTA)) {
      Serial.printf("\n>> topic: %s msg:%s\n", topic, msg);

      //if(String(msg).equals(FIRMWARE_VERSION)){  // Only update if the firmware version is different from current
      mqttLog(8, "Remote OTA process started");
      successReport(SUCCESS_OTA_REMOTE_STARTED);
      remoteOTA();
      //}

   } else if (String(topic).equals(TOPIC_OTA_DEVICE)) {
      mqttLog(8, "Remote OTA process started");
      successReport(SUCCESS_OTA_REMOTE_STARTED);
      remoteOTA();
   }
}

void mqttLog(uint8_t priority, String message) {

   sprintf(tempString, "{\"id\":\"%d\",\"p\":\"%d\",\"msg\":\"%s\"}", deviceId, priority, message.c_str());
   int resp = client.publish(TOPIC_LOG, tempString, true);
   Serial.print("mqtt log:\n\t");
   Serial.println(tempString);

   if (resp == 1) successReport(SUCCESS_MQTT_LOG);
   else errorReport(ERROR_MQTT_LOG_FAILED);

}

void reconnect() {
   digitalWrite(PIN_LED_R, HIGH);
   digitalWrite(PIN_LED_G, HIGH);
   uint8_t reconnectCount = 0;

   while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");

      if(reconnectCount>100){  // 25 seconds
         delay(2000);
         ESP.restart();
      }
      // Attempt to connect
      if (client.connect(MQTT_CLIENT + deviceId, MQTT_USERNAME, MQTT_PASSWORD)) {
         Serial.println("connected");
         subscribe();

      } else {
         Serial.print("failed, rc=");
         Serial.print(client.state());
         Serial.println(" try again");
         delay(250);
      }
   }
   digitalWrite(PIN_LED_R, LOW);
   digitalWrite(PIN_LED_G, LOW);
}
