
#ifdef ENABLE_OTA_UPLOAD

void beginOTA() {
   Serial.println("Booting with OTA support");
   WiFi.mode(WIFI_STA);
   WiFi.begin(WIFI_SSID, WIFI_PASS);

   while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println(">> error: WiFi Connection Failed! Rebooting...");
      ESP.restart();
   }

   // Port defaults to 3232
   // ArduinoOTA.setPort(3232);

   // Hostname defaults to esp3232-[MAC]
   //ArduinoOTA.setHostname("Controller");

   // No authentication by default
   ArduinoOTA.setPassword("agri951");

   // Password can be set with it's md5 value as well
   // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
   // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

   ArduinoOTA
   .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) type = "sketch";
      else type = "filesystem"; // U_SPIFFS

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
   })
   .onEnd([]() {
      Serial.println("\nEnd");
   })
   .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
   })
   .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
   });

   ArduinoOTA.begin();

   Serial.print(">> OTA: on ");
   Serial.println(WiFi.localIP());
}


String getHeaderValue(String header, String headerName) {
   return header.substring(strlen(headerName.c_str()));
}

void remoteOTA() {

   Serial.println("Connecting to: " + String(host));
   // Connect to S3
   if (espClient.connect(host.c_str(), port)) {
      Serial.println("Fetching Bin: " + String(bin));

      espClient.print(String("GET ") + bin + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Cache-Control: no-cache\r\n" + "Connection: close\r\n\r\n");

      // Check what is being sent
      //Serial.print(String("GET ") + bin + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +  "Cache-Control: no-cache\r\n" "Connection: close\r\n\r\n");

      unsigned long timeout = millis();
      while (espClient.available() == 0) {
         if (millis() - timeout > 5000) {
            Serial.println("Client Timeout !");
            espClient.stop();
            mqttLog(8, "Remote OTA: Client Timeout !");
            blinkLED(pin_indicator[3], 4);
            return;
         }
      }

      while (espClient.available()) {
         // read line till /n
         String line = espClient.readStringUntil('\n');
         line.trim();

         if (!line.length()) {
            break; // and get the OTA started
         }
         if (line.startsWith("HTTP/1.1")) {
            if (line.indexOf("200") < 0) {
               Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
               blinkLED(pin_indicator[3], 4);
               break;
            }
         }

         // Start with content length
         if (line.startsWith("Content-Length: ")) {
            contentLength = atol((getHeaderValue(line, "Content-Length: ")).c_str());
            Serial.println("Got " + String(contentLength) + " bytes from server");
         }

         // Next, the content type
         if (line.startsWith("Content-Type: ")) {
            String contentType = getHeaderValue(line, "Content-Type: ");
            Serial.println("Got " + contentType + " payload.");
            if (contentType == "application/octet-stream") {
               isValidContentType = true;
            }
         }
      }
   } else {
      // Connect to remote host failed
      Serial.println("Connection to " + String(host) + " failed. Please check your setup");
      // retry??
      // remoteOTA()
      mqttLog(8, "Remote OTA: Connection failed !");
      blinkLED(pin_indicator[3], 4);
   }

   Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

   // check contentLength and content type
   if (contentLength && isValidContentType) {
      // Check if there is enough to OTA Update
      bool canBegin = Update.begin(contentLength);

      // If yes, begin
      if (canBegin) {
         Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
         size_t written = Update.writeStream(espClient);

         if (written == contentLength) {
            Serial.println("Written : " + String(written) + " successfully");
         } else {
            Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?" );
            // retry??
            // remoteOTA()

            mqttLog(8, "Remote OTA: Unsuccessfull !");
            blinkLED(pin_indicator[3], 4);
            ESP.restart();
         }

         if (Update.end()) {
            Serial.println("OTA done!");
            if (Update.isFinished()) {
               Serial.println("Update successfully completed. Rebooting.");
               ESP.restart();
            } else {
               Serial.println("Update not finished? Something went wrong!");
            }
         } else {
            Serial.println("Error Occurred. Error #: " + String(Update.getError()));
         }
      } else {
         // not enough space to begin OTA; Understand the partitions and space availability
         Serial.println("Not enough space to begin OTA");
         espClient.flush();

         mqttLog(8, "Remote OTA: Space not enough !");
         blinkLED(pin_indicator[3], 4);
         ESP.restart();
      }
   } else {
      Serial.println("There was no content in the response");
      espClient.flush();
      mqttLog(8, "Remote OTA: No content in the response !");
      blinkLED(pin_indicator[3], 4);
      ESP.restart();

   }
}

#else
void beginOTA() {
   Serial.println(">> info: OTA (not enabled)");
}
void remoteOTA() {
   Serial.println(">> info: remote OTA (not enabled)");
}
#endif
