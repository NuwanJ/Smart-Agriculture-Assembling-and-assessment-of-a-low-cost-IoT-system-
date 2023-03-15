
// #define DEV_RUN
#define PROD_RUN

#include <Wire.h>

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

// #define ENABLE_OTA_UPLOAD
// #define ENABLE_DEEP_SLEEP

#ifdef ENABLE_OTA_UPLOAD
// -------------------------------------------------
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Remote OTA
long contentLength = 0;
bool isValidContentType = false;

#ifdef DEV_RUN

String host = "example.com";
int port = 80;
String bin = "/fw/controller/v1/firmware.bin";

#else

String host = "128.0.0.1";
int port = 80;
String bin = "/fw/controller/v1/firmware.bin";

#endif

#endif
// -------------------------------------------------

// #include "DHT.h"
// #include "DHT_U.h"

// #define DHT_PIN 23
// DHT sensor(DHT_PIN, DHT22);

// #define API_END_POINT "http://example.com/api/v1/control/"
#define STATION_ID "1000"
#define SLEEP_DURATION 10

#ifdef DEV_RUN
#define MQTT_SERVER "192.168.1.1"
#else
#define MQTT_SERVER "10.40.1.1"
#endif

#define MQTT_PORT 1883
#define MQTT_CLIENT "Controller_"
#define MQTT_USERNAME "username"
#define MQTT_PASSWORD "password"

// IO Pins ---------------------------------------------------------------------

unsigned int deviceId = 0; // Main Controller
enum control_state
{
    ON,
    OFF,
    UP,
    DOWN
};

#define CURTAIN_UP_TIME 120000
#define CURTAIN_DOWN_TIME 120000

#define OUTPUT_COUNT 8
#define INPUT_COUNT 6
#define SECURE_INPUT_COUNT 2
#define INDICATOR_COUNT 4

const uint8_t pin_output[OUTPUT_COUNT] = {19, 18, 13, 12, 14, 27, 26, 25};
const uint8_t pin_input[INPUT_COUNT] = {32, 35, 34, 33, 39, 36};
const uint8_t pin_sec_input[SECURE_INPUT_COUNT] = {17, 5};
const uint8_t pin_indicator[INDICATOR_COUNT] = {2, 15, 4, 16};

#define CURTAIN_UP_LIMIT_SW pin_sec_input[1]
#define CURTAIN_DOWN_LIMIT_SW pin_sec_input[0]

char input_state[7];

// -- MQTT Settings ------------------------------------------------------------
#include "src/PubSubClient.h"
WiFiClient espClient;
long lastMsg = 0;
char msg[50];
int value = 0;

bool initialMsgCurtain = true;

// For further implement
#define CONTROLLER_ID 1000
#define CONTROLLER_ID_STR "1000"

// Publish topics
#define TOPIC_ERROR "v1/controller/error"
#define TOPIC_REPORT "v1/controller/upload"
#define TOPIC_LOG "v1/controller/log"

// Subscribe topics
#define TOPIC_FAN "v1/controller/" CONTROLLER_ID_STR "/blower"
#define TOPIC_MIST "v1/controller/" CONTROLLER_ID_STR "/mist"
#define TOPIC_WATER "v1/controller/" CONTROLLER_ID_STR "/water"
#define TOPIC_CURTAIN "v1/controller/" CONTROLLER_ID_STR "/curtain"
#define TOPIC_MONITOR "v1/controller/" CONTROLLER_ID_STR "/monitor"
#define TOPIC_READ "v1/sensor/read"

#define TOPIC_OTA "v1/controller/" CONTROLLER_ID_STR "/ota"
#define TOPIC_MSG_IN "v1/controller/" CONTROLLER_ID_STR

PubSubClient client(espClient);
WiFiClient net;

uint8_t curtainMutex = 0;
uint8_t curtainState = UP;
float humidity = 0, temparature = 0;
uint8_t isUpdate = 0;
char tempString[256];

// -----------------------------------------------------------------------------
#ifdef ENABLE_DEEP_SLEEP
#include "esp_sleep.h"
#endif

// -- WiFi Settings ------------------------------------------------------------

#define WIFI_NETWORK_1

// List of available WiFi Networks
#if defined(WIFI_NETWORK_1) // Network 1 --------------
#define WIFI_SSID ""
#define WIFI_PASS ""

#elif defined(WIFI_NETWORK_2) // Network 2 --------------
#define WIFI_SSID ""
#define WIFI_PASS ""

#endif
