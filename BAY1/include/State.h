#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

// --- Core sensor/bay state ---
extern String bayStatus;
extern float voltage, current, power, energyWh, temperature;

// --- Edge AI state ---
extern unsigned long sessionStartMs;
extern float predictedArrivalProb;
extern int predictedDurationMin;
extern int lastHourOfDay;

// --- Optimization state ---
extern String loadDecision;
extern int throttleLevel;
extern bool overloadActive;
extern float predictionThreshold;
extern int peakTariffStartHr;
extern int peakTariffEndHr;
extern float overloadCurrentA;
extern float maxStationLoadW;
extern bool manualOverrideActive;

#endif