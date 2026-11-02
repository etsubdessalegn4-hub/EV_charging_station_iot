# Edge AI-Based EV Charging Station

An IoT capstone project that simulates a three-bay EV charging station. Each bay runs on an ESP32 (simulated in [Wokwi](https://wokwi.com/)), reads its own sensors, and reports to a [ThingsBoard](https://thingsboard.cloud/) cloud dashboard.

> **Status: work in progress.** The project is being added to this repository in stages. See the roadmap below.

## What the system does

1. **Sense**: voltage, current, temperature and plug-in/plug-out status for each bay.
2. **Predict**: an on-device model estimates arrival probability and charging duration.
3. **Decide**: local logic picks a load decision (allow, standby, throttle) and drives status LEDs.
4. **Publish**: telemetry goes to ThingsBoard over MQTT every 5 seconds, with remote relay/throttle control and overload alarms.

## Hardware (simulated)

| Part | Pin | Purpose |
|------|-----|---------|
| Potentiometer | 34 | Simulated voltage sensor |
| Potentiometer | 35 | Simulated current sensor |
| DHT22 | 15 | Temperature |
| Relay | 26 | Switches the charger |
| Push button | 32 | Plug in |
| Push button | 33 | Plug out |
| LED green / yellow / red | 18 / 19 / 21 | Free / charging / alarm |

## Repository layout

```
BAY1/
  include/    headers (pins, shared state, sensor functions)
  src/        firmware source
  test/       Wokwi circuit (diagram.json, wokwi.toml)
  platformio.ini
```

BAY2 and BAY3 use the same firmware with a different device token and bay ID.

## Setup

1. Install [VS Code](https://code.visualstudio.com/) with the **PlatformIO** and **Wokwi** extensions.
2. In `BAY1/src/`, copy `config.example.cpp` to `config.cpp`.
3. Create a device in ThingsBoard and paste its access token into `config.cpp` in place of `YOUR_THINGSBOARD_DEVICE_TOKEN`.
4. Never commit `config.cpp`. It is listed in `.gitignore`.

## Roadmap

- [x] Day 1: hardware simulation, pins, shared state, sensor reading
- [x] Day 2: Wi-Fi, MQTT telemetry, shared attributes
- [ ] Day 3: edge AI prediction and load optimization
- [ ] Day 4: remote control over RPC
- [ ] Day 5: BAY2 and BAY3
- [ ] Day 6: dashboards, alarms, presentation and documentation
