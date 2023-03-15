

void beginMQTT() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.connect(MQTT_CLIENT + deviceId, MQTT_USERNAME, MQTT_PASSWORD);
    client.setCallback(callback);

    Serial.println("MQTT begins");
    if (!client.connected()) {
        reconnect();
    }
    subscribe();
}

void callback(char* topic, byte* message, unsigned int length) {
    char msg[length + 1];
    msg[length] = '\0';

    blinkLED(pin_indicator[1], 2);

    for (int i = 0; i < length; i++) {
        msg[i] =  (char)message[i];
    }

    Serial.printf("\n>> topic: %s msg:%s\n", topic, msg);

    if(String(topic).equals(TOPIC_READ)){
        int seqNo, sleepDuration;

        if (2 == sscanf(msg, "%d %d",  &seqNo, &sleepDuration)) {
            sprintf(tempString, "{\"id\":\"%d\",\"seq\":\"%d\"}", CONTROLLER_ID, seqNo);
            int resp = client.publish(TOPIC_REPORT, tempString, true);
            Serial.printf("mqtt read:\t %d > resp:%d\n", seqNo, resp);
        }

        //if (resp == 1) blinkLED(pin_indicator[3], 1);
        //else blinkLED(pin_indicator[3], 2);

    }else if (String(topic).equals(TOPIC_FAN)) {
        if (msg[0] == '1') blower(ON);
        else blower(OFF);

    } else if (String(topic).equals(TOPIC_MIST)) {
        if (msg[0] == '1') mist(ON);
        else mist(OFF);

    } else if (String(topic).equals(TOPIC_WATER)) {
        if (msg[0] == '1') water(ON);
        else water(OFF);

    } else if (String(topic).equals(TOPIC_CURTAIN)) {

        if (initialMsgCurtain) {         // ignore the first message (retained messages)
            initialMsgCurtain = false;
            return;
        }
        if (msg[0] == '1') curtain(UP);
        else if (msg[0] == '2') curtain(DOWN);
        else curtain(OFF);

    } else if (String(topic).equals(TOPIC_MONITOR)) {
        // Nothing for now

    } else if (String(topic).equals(TOPIC_OTA)) {
        mqttLog(8, "Remote OTA process started");
        blinkLED(pin_indicator[1], 2);
        remoteOTA();

    } else if (String(topic).equals(TOPIC_MSG_IN)) {
        Serial.printf("\n>> topic: %s msg:%s\n", topic, msg);

        if (String(msg).equals("RESTART")) {
            ESP.restart();

        } else if (String(msg).equals("INPUTS")) {
            sprintf(msg, "Inputs: %s", input_state);
            mqttLog(2, msg);
        }
    }

}

void subscribe() {
    client.subscribe(TOPIC_FAN);
    client.subscribe(TOPIC_MIST);
    client.subscribe(TOPIC_WATER);
    client.subscribe(TOPIC_CURTAIN);
    client.subscribe(TOPIC_MONITOR);
    client.subscribe(TOPIC_OTA);
    client.subscribe(TOPIC_MSG_IN);
}

void mqttLog(uint8_t priority, String message) {

    sprintf(tempString, "{\"id\":\"%d\",\"p\":\"%d\",\"msg\":\"%s\"}", CONTROLLER_ID, priority, message.c_str());
    int resp = client.publish(TOPIC_LOG, tempString, true);

    Serial.printf("mqtt log:\t (%d) %s\n", resp, tempString);

    if (resp == 1) blinkLED(pin_indicator[3], 1);
    else blinkLED(pin_indicator[3], 2);

}

void reconnect() {
    digitalWrite(pin_indicator[2], HIGH);     // Turn on the LED 3
    uint8_t reconnectCount = 0;

    while (!client.connected()) {
        if(reconnectCount>100){  // 25 seconds
            ESP.restart();

        }else if(reconnectCount>40){  // 10 seconds
            safeShutdown();
        }
        Serial.print("Attempting MQTT connection...");

        if (client.connect(MQTT_CLIENT, MQTT_USERNAME, MQTT_PASSWORD)) {
            Serial.println("connected");
            subscribe();
        } else {
            reconnectCount++;
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 3 seconds");
            delay(250);
        }
    }

    digitalWrite(pin_indicator[2], LOW);     // Turn off the LED 3
}
