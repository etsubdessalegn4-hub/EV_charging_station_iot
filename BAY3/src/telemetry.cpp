#include <ArduinoJson.h>
#include "telemetry.h"
#include "network.h"
#include "State.h"
#include "config.h"

void publishTelemetry() {
  if (!mqtt.connected()) return;

  StaticJsonDocument<450> doc;   // bumped size slightly for the extra fields
  doc["bayId"] = BAY_ID;
  doc["voltage"] = round(voltage * 10) / 10.0;
  doc["current"] = round(current * 10) / 10.0;
  doc["power"] = round(power * 10) / 10.0;
  doc["temperature"] = round(temperature * 10) / 10.0;
  doc["bayStatus"] = bayStatus;

  doc["predictedArrivalProb"] = round(predictedArrivalProb * 100) / 100.0;
  doc["predictedDurationMin"] = predictedDurationMin;

  doc["loadDecision"] = loadDecision;
  doc["throttleLevel"] = throttleLevel;
  doc["overloadActive"] = overloadActive;

  char buffer[450];
  serializeJson(doc, buffer);

  mqtt.publish("v1/devices/me/telemetry", buffer);
  Serial.print("[MQTT >>] ");
  Serial.println(buffer);
}