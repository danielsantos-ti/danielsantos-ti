/*
Project: Edge Access Controller (Demo Version)
Description:
ESP32 firmware demonstrating integration with a REST API
to process access events and trigger physical relays.

⚠ This is a sanitized demo version.
All sensitive data and internal infrastructure details were removed.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ===============================
// VERSION CONTROL
// ===============================
const char* firmwareVersion = "v1.0.0-demo";
const char* firmwareBuild = "20260219";
const char* firmwareAuthor = "Daniel Santos";

// ===============================
// NETWORK CONFIGURATION (DEMO)
// ===============================
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Replace with your API host
const char* api_host = "https://YOUR_API_HOST";

String session = "";

// ===============================
// RELAY CONFIGURATION
// ===============================
const int relay1 = 19;
const int relay2 = 20;

unsigned long lastQueryTime = 0;
const unsigned long queryInterval = 500;

unsigned long relayStartTime = 0;
const unsigned long relayActiveTime = 3000;

bool relayActive = false;
long lastProcessedEventId = 0;

// ===============================
// WIFI MANAGEMENT
// ===============================

void ensureWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500);
      attempts++;
    }
  }
}

// ===============================
// SESSION HANDLING
// ===============================

bool isSessionInvalid(String response) {
  if (response.indexOf("Invalid session") != -1) {
    session = "";
    delay(300);
    return true;
  }
  return false;
}

bool handleHttpError(int httpCode) {
  if (httpCode < 0) {
    ensureWiFi();
    session = "";
    delay(300);
    return true;
  }
  return false;
}

void login() {
  ensureWiFi();

  HTTPClient http;
  http.begin(String(api_host) + "/login");
  http.addHeader("Content-Type", "application/json");

  String payload =
    "{\"login\":\"YOUR_USER\",\"password\":\"YOUR_PASSWORD\",\"device_id\":1}";

  int httpCode = http.POST(payload);

  if (handleHttpError(httpCode)) {
    http.end();
    return;
  }

  if (httpCode == 200) {
    String response = http.getString();
    if (!isSessionInvalid(response)) {
      DynamicJsonDocument doc(512);
      if (!deserializeJson(doc, response)) {
        session = doc["session"].as<String>();
      }
    }
  }

  http.end();
}

// ===============================
// EVENT QUERY (OPTIMIZED)
// ===============================

bool getLatestEvent(int &user_id, long &event_id) {
  ensureWiFi();
  if (session == "") login();

  HTTPClient http;
  http.begin(String(api_host) + "/events?session=" + session);
  http.addHeader("Content-Type", "application/json");

  String payload =
    "{"
      "\"object\":\"access_logs\","
      "\"where\":[{"
        "\"field\":\"id\","
        "\"operator\":\">\","
        "\"value\":" + String(lastProcessedEventId) +
      "}],"
      "\"order\":[\"id\",\"descending\"],"
      "\"limit\":1"
    "}";

  int httpCode = http.POST(payload);

  if (handleHttpError(httpCode)) {
    http.end();
    return false;
  }

  if (httpCode != 200) {
    http.end();
    return false;
  }

  String response = http.getString();

  if (isSessionInvalid(response)) {
    http.end();
    return false;
  }

  DynamicJsonDocument doc(4096);
  if (deserializeJson(doc, response)) {
    http.end();
    return false;
  }

  JsonArray logs = doc["access_logs"].as<JsonArray>();
  if (logs.size() == 0) {
    http.end();
    return false;
  }

  JsonObject e = logs[0];

  event_id = e["id"] | -1;
  user_id = e["user_id"] | -1;

  http.end();
  return true;
}

// ===============================
// RELAY CONTROL LOGIC
// ===============================

void triggerRelay() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  relayActive = true;
  relayStartTime = millis();
}

// ===============================
// SETUP
// ===============================

void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);

  WiFi.begin(ssid, password);
  login();
}

// ===============================
// MAIN LOOP
// ===============================

void loop() {
  ensureWiFi();

  unsigned long now = millis();

  if (now - lastQueryTime > queryInterval) {
    lastQueryTime = now;

    int user_id = -1;
    long event_id = -1;

    if (getLatestEvent(user_id, event_id)) {
      if (event_id > lastProcessedEventId) {
        lastProcessedEventId = event_id;
        triggerRelay();
      }
    }
  }

  if (relayActive && (millis() - relayStartTime > relayActiveTime)) {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    relayActive = false;
  }
}
