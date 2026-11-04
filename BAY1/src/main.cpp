#include <Arduino.h>
#include <WiFi.h>
#include "State.h"
#include "config.h"
#include "Peripherals.h"
#include "network.h"
#include "telemetry.h"
#include "edge_ai.h"
#include "optimization.h"
#include "attributes.h"

unsigned long now;
unsigned long last_print;

void setup()
{
    Serial.begin(115200);
    dht.begin();

    pinMode(BTN_PLUGIN, INPUT_PULLUP);
    pinMode(BTN_PLUGOUT, INPUT_PULLUP);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    connectWiFi();
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    mqtt.setBufferSize(512);        // room for attribute payloads
    mqtt.setCallback(mqttCallback); // routes incoming messages

    connectMQTT();   // also subscribes and requests shared attributes
}

void loop()
{
    mqtt.loop();   // must run every iteration to receive incoming messages
    plug_status();

    now = millis();
    if ((now - last_print) > 5000)
    {
        last_print = now;
        sample_sensor();
        runEdgeAIInference();   // arrival probability + predicted duration
        if (!manualOverrideActive) {   // a human RPC command takes priority over the AI decision
            runOptimization();         // load decision and throttle level
        }
        publishTelemetry();
    }

    applyRelayDutyCycle();   // reflects whichever throttleLevel is active
    updateLeds();
}
