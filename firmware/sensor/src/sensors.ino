
void beginLightSensor()
{
  // CONTINUOUS_HIGH_RES_MODE   > Measurement at 1 lux resolution. Measurement time is approx 120ms.
  // CONTINUOUS_HIGH_RES_MODE_2 > Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
  // CONTINUOUS_LOW_RES_MODE    > Measurement at 4 lux resolution. Measurement time is approx 16ms.
  // ONE_TIME_HIGH_RES_MODE     > Measurement at 1 lux resolution. Measurement time is approx 120ms.
  // ONE_TIME_HIGH_RES_MODE_2   > Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
  // ONE_TIME_LOW_RES_MODE      > Measurement at 4 lux resolution. Measurement time is approx 16ms.

  if (lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE_2))
  {
    Serial.println(F("BH1750 \t: begin"));
  }
  else
  {
    Serial.println(F("BH1750 \t: Error initialising"));
    errorReport(ERROR_SENSOR_BH1750_INIT_FAILED);
  }
}

void beginDHTSensors()
{
  temp_0.begin();
  temp_1.begin();
  temp_2.begin();
}

// ===========================================================================================

// Read from  BH1750 Module (via I2C bus)
void readLight()
{
  float lux = lightMeter.readLightLevel();

  if (lux < 0)
  {
    Serial.println(F("Lights\t Error condition detected"));
    errorReport(ERROR_SENSOR_BH1750_ERROR_CONDITION);
  }
  else
  {
    if (lux > 40000.0)
    {
      // reduce measurement time - needed in direct sun light
      if (lightMeter.setMTreg(32))
      {
        // Serial.println(F("Setting MTReg to low value for high light environment"));
      }
      else
      {
        Serial.println(F("Lights\t Error setting MTReg to default value for normal light environment"));
        errorReport(ERROR_SENSOR_BH1750_ERROR_MTREG_1);
      }
    }
    else
    {
      if (lux > 10.0)
      {
        // typical light environment
        if (lightMeter.setMTreg(69))
        {
          // Serial.println(F("Setting MTReg to default value for normal light environment"));
        }
        else
        {
          Serial.println(F("Lights\t Error setting MTReg to default value for normal light environment"));
          errorReport(ERROR_SENSOR_BH1750_ERROR_MTREG_2);
        }
      }
      else
      {
        if (lux <= 10.0)
        {
          // very low light environment
          if (lightMeter.setMTreg(138))
          {
            // Serial.println(F("Setting MTReg to high value for low light environment"));
          }
          else
          {
            Serial.println(F("Lights\t Error setting MTReg to default value for normal light environment"));
            errorReport(ERROR_SENSOR_BH1750_ERROR_MTREG_3);
          }
        }
      }
    }
  }
  lightIntensity = lightMeter.readLightLevel();
  Serial.printf("Lights\t Lux: %.3f\n", lightIntensity);
  delay(500);
}

// Read from DHT22 sensor (via Digital Data Bus)
void readDHT0()
{
  humidity[0] = temp_0.readHumidity();
  temp[0] = temp_0.readTemperature();

  if (isnan(humidity[0]) || isnan(temp[0]))
  {
    Serial.println(F("0_DHT22\t Failed to read from the sensor!"));
    errorReport(ERROR_SENSOR_DHT_0_READ_FAIL);

    humidity[0] = -273;
    temp[0] = -273;

    // blinkLED(PIN_LED_R, 1);
  }
  else
  {
    blinkLED(PIN_LED_B, 1);
    float hic = temp_0.computeHeatIndex(temp[0], humidity[0], false);
    Serial.printf("0_DHT22\t Temperature: %.2f°C Humidity: %.2f Heat index: %.2f \n", temp[0], humidity[0], hic);
  }
}

// Read from DHT11 sensor (via Digital Data Bus)
void readDHT1()
{

  temp[1] = temp_1.readTemperature();
  humidity[1] = temp_1.readHumidity();

  if (isnan(humidity[1]) || isnan(temp[1]))
  {
    Serial.println(F("1_DHT11\t Failed to read from the sensor!"));
    errorReport(ERROR_SENSOR_DHT_1_READ_FAIL);

    humidity[1] = -273;
    temp[1] = -273;

    return;
  }
  float hic = temp_1.computeHeatIndex(temp[1], humidity[1], false);
  Serial.printf("1_DHT11\t Temperature: %.2f°C Humidity: %.2f Heat index: %.2f \n", temp[1], humidity[1], hic);
}

// Read from DHT11 sensor (via Digital Data Bus)
void readDHT2()
{
  humidity[2] = temp_2.readHumidity();
  temp[2] = temp_2.readTemperature();

  if (isnan(humidity[2]) || isnan(temp[2]))
  {
    Serial.println(F("2_DHT11\t Failed to read from the sensor!"));
    errorReport(ERROR_SENSOR_DHT_2_READ_FAIL);

    humidity[2] = -273;
    temp[2] = -273;

    // blinkLED(PIN_LED_R, 1);
  }
  else
  {
    blinkLED(PIN_LED_B, 1);
    float hic = temp_2.computeHeatIndex(temp[2], humidity[2], false);
    Serial.printf("2_DHT11\t Temperature: %.2f°C Humidity: %.2f Heat index: %.2f \n", temp[2], humidity[2], hic);
  }
}

// Read from soil moisture sensor (via ADC Read)
void readSoilMoisture()
{
  long rawValue = 0;

  for (int i = 0; i < SOIL_MOISTURE_SAMPLES; i++)
  {
    rawValue += analogRead(PIN_SOIL_MOISTURE);
    delay(SAMPLE_DELAY);
  }

  // TODO: Need to calibrate and update following formula
  soilMoisture = (rawValue / (4096.0 * SOIL_MOISTURE_SAMPLES));

  Serial.printf("Soil\t Moisture: %.3f\n", soilMoisture);
  delay(500);
}
