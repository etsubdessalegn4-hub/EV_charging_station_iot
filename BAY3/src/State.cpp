#include "State.h"

// --- Core sensor/bay state ---
String bayStatus = "FREE";
float voltage = 0.0, current = 0.0, power = 0.0, energyWh = 0.0, temperature = 0.0;

// --- Edge AI state ---
unsigned long sessionStartMs = 0;
float predictedArrivalProb = 0.0;
int predictedDurationMin = 0;
int lastHourOfDay = 12;

// --- Optimization state ---
String loadDecision = "ALLOW";
int throttleLevel = 100;          // note: she flagged this should arguably start at 0 (see caveat below)
bool overloadActive = false;
float predictionThreshold = 0.5;
int peakTariffStartHr = 18;
int peakTariffEndHr = 21;
float overloadCurrentA = 16.0;
float maxStationLoadW = 3000.0;
bool manualOverrideActive = false;