
#define DEV_RUN
// #define PROD_RUN

// This indicates the current firmware version, should be increase if firmawre version is updated
#define FIRMWARE_VERSION "v1"

#define ENABLE_DEBUG
#define ENABLE_OTA_UPLOAD
#define ENABLE_DEEP_SLEEP

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include "DHT.h"
#include "DHT_U.h"

#include <Wire.h>
#include <BH1750.h>

#ifdef ENABLE_OTA_UPLOAD
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Remote OTA
long contentLength = 0;
bool isValidContentType = false;

#ifdef DEV_RUN

String host = "example.com";
int port = 80;
String bin = "/fw/sensor/v1/firmware.bin";

#else
// PROD_RUN

String host = "10.40.1.1";
int port = 80;
String bin = "/fw/sensor/v1/firmware.bin";

#endif

#endif

#ifdef ENABLE_DEEP_SLEEP
#include "esp_sleep.h"
#endif
#define SLEEP_DURATION 10

// -- EEPROM Settings ----------------------------------------------------------

#include "EEPROM.h"
#define EEPROM_SIZE 10
#define EEPROM_ADDR_ID 0
#define EEPROM_ADDR_KEY 1

// -- MQTT Settings ------------------------------------------------------------

#include "src/PubSubClient.h"
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

#ifdef DEV_RUN
#define MQTT_SERVER "192.168.1.1"
#else
// if PROD_RUN
#define MQTT_SERVER "10.40.1.1"
#endif

#define MQTT_PORT 1883
#define MQTT_CLIENT "Sensor_"
#define MQTT_USERNAME "username"
#define MQTT_PASSWORD "password"

// MQTT Topics
#define TOPIC_PUBLISH "v1/sensor/upload"
#define TOPIC_MSG "v1/sensor/msg"
#define TOPIC_LOG "v1/sensor/log"
#define TOPIC_OTA "v1/sensor/" FIRMWARE_VERSION "/ota"
#define TOPIC_READ "v1/sensor/read"
char TOPIC_OTA_DEVICE[22];

// -----------------------------------------------------------------------------

#define DEVICE_ID_BASE 10000
unsigned int deviceId = 0;

#define PIN_DHT_0 25 // DHT22
#define PIN_DHT_1 26 // DHT11
#define PIN_DHT_2 27 // DHT11
#define PIN_DHT_3 -1 // Not using

#define PIN_SOIL_MOISTURE 32

#define PIN_LED_G 2
#define PIN_LED_R 4
#define PIN_LED_B 15

#define RESTART_READING_COUNT 20
#define SENSOR_UPLOAD_INTERVAL 5000

#define SOIL_MOISTURE_SAMPLES 10
#define LIGHT_SAMPLES 10
#define SAMPLE_DELAY 30

BH1750 lightMeter(0x23);
DHT temp_0(PIN_DHT_0, DHT22);
DHT temp_1(PIN_DHT_1, DHT11);
DHT temp_2(PIN_DHT_2, DHT11);

WiFiMulti wifiMulti;

char tempString[256];
float temp[3];
float humidity[3];
float soilMoisture = 0.0;
float lightIntensity = 0;

// -----------------------------------------------------------------------------
#define WIFI_NETWORK_1

// List of available WiFi Networks
#if defined(WIFI_NETWORK_1) // Network 1 --------------
#define WIFI_SSID ""
#define WIFI_PASS ""

#elif defined(WIFI_NETWORK_2) // Network 2 --------------
#define WIFI_SSID ""
#define WIFI_PASS ""

#endif

// Debug Codes -----------------------------------------------------------------

#ifdef ENABLE_DEBUG

#define SUCCESS_MQTT_PUBLISH 100
#define SUCCESS_MQTT_MSG_IN 101
#define SUCCESS_OTA_REMOTE_STARTED 102
#define SUCCESS_MQTT_LOG 103
#define SUCCESS_MQTT_CONNECTED 104
#define SUCCESS_DEVICE_BEGIN 105

#define ERROR_OTHER 0

#define ERROR_WIFI 100
#define ERROR_WIFI_CONNECTION_FAILED 100

#define ERROR_MQTT 200
#define ERROR_MQTT_PUBLISH_FAILED 201
#define ERROR_MQTT_LOG_FAILED 202
#define ERROR_MQTT_RECONNECT_FAILED 203

#define ERROR_OTA 300
#define ERROR_OTA_WIFI_FAILED 301
#define ERROR_OTA_CLIENT_TIMEOUT 302
#define ERROR_OTA_REMOTE_UNSUCCESS 303
#define ERROR_OTA_NO_ENOUGH_SPACE 304
#define ERROR_OTA_NO_CONTENT 305
#define ERROR_OTA_LOCAL_FAILED 306

#define ERROR_SENSOR 400
#define ERROR_SENSOR_BH1750_INIT_FAILED 401
#define ERROR_SENSOR_BH1750_ERROR_CONDITION 402
#define ERROR_SENSOR_BH1750_ERROR_MTREG_1 403
#define ERROR_SENSOR_BH1750_ERROR_MTREG_2 404
#define ERROR_SENSOR_BH1750_ERROR_MTREG_3 405
#define ERROR_SENSOR_DHT_0_READ_FAIL 406
#define ERROR_SENSOR_DHT_1_READ_FAIL 407
#define ERROR_SENSOR_DHT_2_READ_FAIL 408

#endif
// -----------------------------------------------------------------------------
