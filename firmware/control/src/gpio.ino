
void beginGPIO() {

   // Configure Output Pins
   for (int i = 0; i < OUTPUT_COUNT; i++) {
      pinMode(pin_output[i], OUTPUT);

      // This is due to different versions of SSRs
      if(i<4) digitalWrite(pin_output[i], LOW);
      else digitalWrite(pin_output[i], HIGH);
   }

   // Configure Input pins
   for (int i = 0; i < INPUT_COUNT; i++) {
      pinMode(pin_input[i], INPUT_PULLUP);
      input_state[i] = '0';
   }
   input_state[6] = '\0';

   // Configure opto-isolated input pins
   for (int i = 0; i < SECURE_INPUT_COUNT; i++) {
      pinMode(pin_sec_input[i], INPUT);
   }

   // Configure Indicator pins
   for (int i = 0; i < INDICATOR_COUNT; i++) {
      pinMode(pin_indicator[i], OUTPUT);
      digitalWrite(pin_indicator[i], LOW);
   }

   // Update the Curtain state, based on limit switches
   if (digitalRead(CURTAIN_UP_LIMIT_SW) == 1) {
      curtainState = UP;
   }else if (digitalRead(CURTAIN_DOWN_LIMIT_SW) == 1) {
      curtainState = DOWN;
   }else{
      curtainState = UP; // the default is up
   }

}

// Read the toggle switches and update

int updateInputs() {
   int inState[6] = {0, 0, 0, 0, 0, 0};

   // Taking 10 readings and consider the average
   for (int j = 0; j < 10; j++) {
      for (int i = 0; i < INPUT_COUNT; i++) {
         inState[i] += digitalRead(pin_input[i]);
      }
      delay(10);
   }

   for (int i = 0; i < INPUT_COUNT; i++) {
      input_state[i] = (inState[i] > 5) ? '0' : '1';
   }
   Serial.printf("inputs\t: %s\n", input_state);
   return 0;
}

void testIndicators() {
   for (int i = 0; i < INDICATOR_COUNT; i++) {
      blinkLED(pin_indicator[i], i + 1);
   }
}


void blinkLED(int pin, int count) {
   for (int i = 0; i < count; i++) {
      digitalWrite(pin, HIGH);
      delay(300);
      digitalWrite(pin, LOW);
      delay(300);
   }
}
