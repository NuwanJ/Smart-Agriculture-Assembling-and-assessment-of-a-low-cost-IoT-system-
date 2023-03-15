
void blower(uint8_t state) {
   if (state == ON) {
      digitalWrite(pin_output[2], HIGH);
      Serial.println("Blower\t: ON");
   } else {

      digitalWrite(pin_output[2], LOW);
      Serial.println("Blower\t: OFF");
   }
}
void mist(uint8_t state) {
   if (state == ON) {
      digitalWrite(pin_output[5], LOW);        // change this to 5,6,7
      Serial.println("Mist\t: ON");
   } else {
      digitalWrite(pin_output[5], HIGH);
      Serial.println("Mist\t: OFF");
   }
}

void water(uint8_t state) {
   if (state == ON) {
      digitalWrite(pin_output[4], LOW);
      Serial.println("Water\t: ON");
   } else {
      digitalWrite(pin_output[4], HIGH);
      Serial.println("Water\t: OFF");
   }
}

void curtain(uint8_t state) {

   if (state == UP && curtainState == DOWN) {
      curtainUp();
   } else if (state == DOWN && curtainState == UP) {
      curtainDown();
   } else {
      Serial.println("Curtain\t: Undefined status !!!");
   }
}

void curtainUp() {

   if(curtainMutex) return;
   curtainMutex = 1;

   long initTime = millis();
   long acceptTime = CURTAIN_UP_TIME * 1.5;   // Even switch isn't triggered, stop the motors at that much of time

   if (digitalRead(CURTAIN_UP_LIMIT_SW) == 1) {
      // Already up
      Serial.println("Curtain\t: already UP");
      curtainState = UP;
      return;
   }

   digitalWrite(pin_output[0], HIGH);
   digitalWrite(pin_output[1], LOW);
   Serial.println("Curtain\t: moving UP");

   while ((digitalRead(CURTAIN_UP_LIMIT_SW) == 0) && ((millis() - initTime) < acceptTime)) {
      delay(100);
      client.loop(); // Check for new MQTT message while loop
   }

   digitalWrite(pin_output[0], LOW);
   digitalWrite(pin_output[1], LOW);

   curtainState = UP;
   curtainMutex = 0;
   Serial.println("Curtain\t: UP");
}

void curtainDown() {

   if(curtainMutex) return;
   curtainMutex = 1;

   long initTime = millis();
   long acceptTime = CURTAIN_DOWN_TIME;   // Even switch isn't triggered, stop the motors at that much of time


   if (digitalRead(CURTAIN_DOWN_LIMIT_SW) == 1) {
      // Already up
      Serial.println("Curtain\t: Already DOWN");
      curtainState = DOWN;
      return;
   }

   digitalWrite(pin_output[0], LOW);
   digitalWrite(pin_output[1], HIGH);

   Serial.println("Curtain\t: moving DOWN");

   while ((digitalRead(CURTAIN_DOWN_LIMIT_SW) == 0) && ((millis() - initTime) < acceptTime)) {
      delay(100);
      client.loop();  // Check for new MQTT message while loop
   }

   digitalWrite(pin_output[0], LOW);
   digitalWrite(pin_output[1], LOW);

   curtainState = DOWN;
   curtainMutex = 0;
   Serial.println("Curtain\t: DOWN");
}

void curtainOff() {
   digitalWrite(pin_output[0], LOW);
   digitalWrite(pin_output[1], LOW);
}

void safeShutdown() {
   blower(OFF);
   mist(OFF);
   water(OFF);
   curtainOff();
}




/*
void monitorA(uint8_t state) {
if (state == ON) {
digitalWrite(pin_output[5], LOW);
Serial.println("MonitorA\t: ON");
} else {
digitalWrite(pin_output[5], HIGH);
Serial.println("MonitorA\t: OFF");
}
}

void monitorB(uint8_t state) {
if (state == ON) {
digitalWrite(pin_output[6], LOW);
Serial.println("MonitorB\t: ON");
} else {
digitalWrite(pin_output[6], HIGH);
Serial.println("MonitorB\t: OFF");
}
}

void monitorC(uint8_t state) {
if (state == ON) {
digitalWrite(pin_output[7], LOW);
Serial.println("MonitorC\t: ON");
} else {
digitalWrite(pin_output[7], HIGH);
Serial.println("MonitorC\t: OFF");
}
}
*/
