/*
Data de criação: 11/09/2025
Última atualização: 18/02/2026
Nome do projeto: Sistema de Controle de Acesso PGT 120

Descrição geral:
Firmware desenvolvido para integração direta entre o ESP32 e o ControlID IDFace,
permitindo o acionamento automático do circuito do PGT 120 com base nos eventos
de acesso registrados no dispositivo.

Funcionamento:
- Conecta ao ControlID via API Web (load_objects.fcgi).
- Realiza login e mantém a sessão ativa automaticamente.
- Consulta apenas o último evento de acesso utilizando filtros WHERE, ORDER e LIMIT,
  garantindo alta performance e baixo consumo de memória.
- Identifica eventos do tipo 7 (acesso liberado) e extrai o user_id correspondente.
- Consulta os grupos do usuário para determinar quais relés devem ser acionados:
    • Grupo 3 → Relé 1 (Departamento 1)
    • Grupo 2 → Relé 2 (Departamento 2)
- Aciona o(s) relé(s) correspondente(s) por 5 segundos.
- Evita acionamentos duplicados armazenando o último event_id processado.
- Mantém reconexão automática de Wi-Fi e sessão da API.

Equipe responsável:
Daniel Santos – Engenheiro de Software  
Iago Nóbrega – Assistente de TI  
Marco Antonio – Técnico em Eletrônica  
Mateus Rodrigues – Técnico em Eletrônica  

Objetivo:
Garantir o controle de acesso seguro, rápido e confiável para o sistema PGT 120,
acionando o hardware somente quando um colaborador autorizado é reconhecido
pelo IDFace.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ===============================
// CONTROLE DE VERSÃO
// ===============================
const char* firmwareVersion = "v1.0.0-demo";
const char* firmwareBuild = "20260219";
const char* firmwareAuthor = "Daniel Santos";

// ===============================
// CONFIGURAÇÕES DE REDE
// ===============================
const char* ssid = "wifi_ssid";
const char* password = "senha_wifi";

// api_host para testes locais
const char* api_host = "https://HOST_IP";

String session = "";

// ===============================
// CONTROLE DE RELÉS
// ===============================
const int rele1 = 19;
const int rele2 = 20;

unsigned long lastQueryTime = 0;
const unsigned long queryInterval = 500;

unsigned long relayStartTime = 0;
const unsigned long relayActiveTime = 3000;

bool relayActive = false;
long lastProcessedEventId = 0;

// ===============================
// GERENCIAMENTO DE SESSÃO E CONEXÃO
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
// MANIPULAÇÃO DE SESSÃO E LOGIN
// ===============================

bool isSessionInvalid(String response) {
  if (response.indexOf("Sessão inválida") != -1) {
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
    "{\"login\":\"usuario\",\"password\":\"senha\",\"device_id\":1}";

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
// QUERY PARA O ÚLTIMO EVENTO DE ACESSO
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
// CONTROLE DE RELÉS
// ===============================

void triggerRelay() {
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);

  relayActive = true;
  relayStartTime = millis();
}

// ===============================
// SETUP
// ===============================

void setup() {
  Serial.begin(115200);

  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);

  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);

  WiFi.begin(ssid, password);
  login();
}

// ===============================
// LOOP PRINCIPAL
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
    digitalWrite(rele1, LOW);
    digitalWrite(rele2, LOW);
    relayActive = false;
  }
}
