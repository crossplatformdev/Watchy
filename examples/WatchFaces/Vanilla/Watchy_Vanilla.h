#ifndef WATCHY_VANILLA_H
#define WATCHY_VANILLA_H

#include <Watchy.h>

#include "DSEG7Classic_Regular12pt7b.h"
#include "FreeMono12pt7b.h"

const int DEFAULT_LINE_SPACING = 2;
const int DEFAULT_TIMEZONE_SPACING = 5;
const int DEFAULT_DEGREE_SYMBOL_SPACING = 4;
const float BATTERY_VOLTAGE_MIN = 3.48;
const float BATTERY_VOLTAGE_MAX = 3.91;
const String TIME_CALLIBRATION_STRING = "88:888";
const String OTHER_CALLIBRATION_STRING = "X1Il^qpyi";

struct Position {
    int16_t x1, y1;
    uint16_t w, h;
};

class WatchyVanilla : public Watchy {
    using Watchy::Watchy;

    public:
        void drawWatchFace();

    private:
        void initialize();
        void drawTime();
        void drawDate();
        void drawConnectivity();
        void drawSteps();
        void drawWeather();
        void drawBattery();
        Position getNextLinePositionTime();
        Position getNextLinePositionOther();
        String getAdjustedTime(int, int);
        Position getNextLinePositionHelper(const GFXfont *, String);
        int lineY;
        Position time;
        Position other;
};

#endif