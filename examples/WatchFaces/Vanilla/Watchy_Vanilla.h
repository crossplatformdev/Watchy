#ifndef WATCHY_VANILLA_H
#define WATCHY_VANILLA_H

#include <Watchy.h>

#include "DSEG7Classic_Regular12pt7b.h"
#include "FreeMono12pt7b.h"

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
        String getAdjustedTime(int, int);
        int lineY;
};

#endif