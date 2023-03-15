
void beginWiFi()
{

#ifdef DEV_RUN
  // DHCP
#else
  // if PROD_RUN
  connectWithStaticIP();
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("");

  int startTime = millis();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    blinkLED(PIN_LED_R, 1);

    if ((millis() - startTime) > 20 * 1000)
    {
      // allow 20sec, if not connected, reset
      errorReport(ERROR_WIFI_CONNECTION_FAILED);
      blinkLED(PIN_LED_B, 4);
      ESP.restart();
    }
  }
}

void connectWithStaticIP()
{
  IPAddress local_IP(10, 40, 1, (deviceId - DEVICE_ID_BASE));
  IPAddress gateway(10, 40, 1, 254);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(10, 40, 1, 1);

  if (!WiFi.config(local_IP, gateway, subnet, dns))
  {
    Serial.println("Error in configuration...");
  }

  Serial.println("");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
}
/*
  int postData() {

  if (WiFi.status() == WL_CONNECTED) {
  HTTPClient http;

  http.begin(API_END_POINT);
  http.addHeader("Content-Type", "application/json");

  // Add post data
  sprintf(tempString, "{\"temp\": {\"0\":\"%.2f\",\"1\":\"%.2f\"},\"humidity\": {\"0\":\"%.2f\",\"1\":\"%.2f\"},\"light\":\"%.3f\",\"soil\":\"%.3f\"}",
  temp[0], temp[1], humidity[0], humidity[1], lightIntensity, soilMoisture);
  //Serial.println(tempString);

  int httpResponseCode = http.POST(tempString);

  if (httpResponseCode > 0) {
  String response = http.getString();
  Serial.println(httpResponseCode);   //Print return code
  Serial.println(response);           //Print request answer

  } else {
  Serial.printf("Error on sending GET: %d \n", httpResponseCode);
  blinkLED(PIN_LED_R, 1);
  }

  http.end();

  if(httpResponseCode != 200){
  ESP.restart();
  }

  return httpResponseCode;
  }
  else {
  Serial.println("Error in WiFi connection");
  blinkLED(PIN_LED_B, 4);
  ESP.restart();
  return 0;
  }

  }
*/
