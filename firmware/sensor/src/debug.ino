
#ifdef ENABLE_DEBUG

void successReport(int code){

   if(code==SUCCESS_MQTT_PUBLISH){
      blinkLED(PIN_LED_B, 1);
   }else if(code==SUCCESS_MQTT_MSG_IN){
      blinkLED(PIN_LED_G, 1);
   }else if (code==SUCCESS_OTA_REMOTE_STARTED){
      blinkLED(PIN_LED_G, 2);
   }else if(code==SUCCESS_MQTT_LOG){
      blinkLED(PIN_LED_G, 3);
   }else{
      blinkLED(PIN_LED_G, 4);
   }

}

void errorReport(int errorCode){

   if(errorCode > ERROR_SENSOR){
      // 400-499

      if(errorCode == ERROR_SENSOR_BH1750_INIT_FAILED){
         blinkLED(PIN_LED_R, 4);
      } else if(errorCode == ERROR_SENSOR_BH1750_ERROR_CONDITION){
         blinkLED(PIN_LED_R, 5);
      } else if(errorCode == ERROR_SENSOR_BH1750_ERROR_MTREG_1){
         blinkLED(PIN_LED_R, 5);
      } else if(errorCode == ERROR_SENSOR_BH1750_ERROR_MTREG_2){
         blinkLED(PIN_LED_R, 5);
      } else if(errorCode == ERROR_SENSOR_BH1750_ERROR_MTREG_3){
         blinkLED(PIN_LED_R, 5);
      } else if(errorCode == ERROR_SENSOR_DHT_0_READ_FAIL){
         blinkLED(PIN_LED_R, 1);
      } else if(errorCode == ERROR_SENSOR_DHT_1_READ_FAIL){
         blinkLED(PIN_LED_R, 2);
      } else if(errorCode == ERROR_SENSOR_DHT_2_READ_FAIL){
         blinkLED(PIN_LED_R, 3);
      } else {

      }

   }else if(errorCode > ERROR_OTA){
      // 300-399

      if(errorCode == ERROR_OTA_WIFI_FAILED){
         blinkLED(PIN_LED_G,PIN_LED_B, 1);
      } else if(errorCode == ERROR_OTA_CLIENT_TIMEOUT){
         blinkLED(PIN_LED_G,PIN_LED_B, 2);
      } else if(errorCode == ERROR_OTA_REMOTE_UNSUCCESS){
         blinkLED(PIN_LED_G,PIN_LED_B, 3);
      } else if(errorCode == ERROR_OTA_NO_ENOUGH_SPACE){
         blinkLED(PIN_LED_G,PIN_LED_B, 4);
      } else if(errorCode == ERROR_OTA_NO_CONTENT){
         blinkLED(PIN_LED_G,PIN_LED_B, 5);
      } else if(errorCode == ERROR_OTA_LOCAL_FAILED){
         blinkLED(PIN_LED_G,PIN_LED_B, 6);
      } else {

      }

   }else if(errorCode > ERROR_MQTT){
      // 200-299

      if(errorCode == ERROR_MQTT_PUBLISH_FAILED){
         blinkLED(PIN_LED_R,PIN_LED_B, 1);
      } else if(errorCode == ERROR_MQTT_LOG_FAILED){
         blinkLED(PIN_LED_R,PIN_LED_B, 2);
      } else if(errorCode == ERROR_MQTT_RECONNECT_FAILED){
         blinkLED(PIN_LED_R,PIN_LED_B, 3);
      } else {

      }

   }else if(errorCode > ERROR_WIFI){
      // 100-199

      if(errorCode == ERROR_WIFI_CONNECTION_FAILED){
         blinkLED(PIN_LED_R, 4);
      }else{

      }
   }else if(errorCode > ERROR_OTHER){
      // 000-099

      if(errorCode == ERROR_OTHER){
         blinkLED(PIN_LED_R, 5);
      }
   }
   delay(1500);
}



void blinkLED(int pin, int count) {
   for (int i = 0; i < count; i++) {
      digitalWrite(pin, HIGH);
      delay(500);
      digitalWrite(pin, LOW);
      delay(500);
   }
}

void blinkLED(int pin1,int pin2, int count) {
   for (int i = 0; i < count; i++) {
      digitalWrite(pin1, HIGH);digitalWrite(pin2, HIGH);
      delay(500);
      digitalWrite(pin1, LOW);digitalWrite(pin2, LOW);
      delay(500);
   }
}


#else

void errorReport(int errorCode){}
void blinkLED(int pin, int count) {}
void blinkLED(int pin1,int pin2, int count) {}

#endif
