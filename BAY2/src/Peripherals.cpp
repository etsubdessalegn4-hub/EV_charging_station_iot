#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"

DHT dht(DHT_PIN, DHT_TYPE);

bool plugin_flag_once = 1;
bool plugout_flag_once = 1;

float mapFloat(float x, float inMin, float inMax, float outMin, float outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

float recentAvgCurrent(void) {
    float sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += current;
    }
    return sum / 5;
}

void sample_sensor(void)
{
    int raw_current = analogRead(CURRENT_PIN);
    int raw_voltage = analogRead(VOLTAGE_PIN);

    voltage = mapFloat(raw_voltage, 0, 4095, 0, 250);
    if (bayStatus == "CHARGING") {
        current = mapFloat(raw_current, 0, 4095, 0, 32);
    } else {
        current = 0;
    }
    temperature = dht.readTemperature();
    power = voltage * current;
}

void plug_status(void)
{
    bool pluginReading = digitalRead(BTN_PLUGIN);          // renamed
    if (pluginReading == LOW && plugin_flag_once)
    {
        plugin_flag_once = 0;
        if (bayStatus == "FREE")
        {
            bayStatus = "CHARGING";
            sessionStartMs = millis(); 
            Serial.print(BAY_ID); Serial.println(" plugin detected, Bay is CHARGING");
            digitalWrite(RELAY_PIN, HIGH);

        }
    }
    if (pluginReading == HIGH)
    {
        plugin_flag_once = 1;
    }

    bool plugoutReading = digitalRead(BTN_PLUGOUT);        
    if (plugoutReading == LOW && plugout_flag_once)
    {
        plugout_flag_once = 0;
        if (bayStatus == "CHARGING")
        {
            bayStatus = "FREE";
            Serial.print(BAY_ID); Serial.println(" plugout detected, Bay is FREE");
            digitalWrite(RELAY_PIN, LOW);
        } 
    }
    if (plugoutReading == HIGH)
    {
        plugout_flag_once = 1;
    }
}

void update_led_status(void)
{
    if (bayStatus == "CHARGING")
    {
        digitalWrite(LED_GREEN, LOW);      // renamed
        digitalWrite(LED_YELLOW, HIGH);    // renamed
    }
    else
    {
        digitalWrite(LED_GREEN, HIGH);     // renamed
        digitalWrite(LED_YELLOW, LOW);     // renamed
    }
}

