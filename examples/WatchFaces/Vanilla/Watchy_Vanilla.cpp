#include "Watchy_Vanilla.h"

void WatchyVanilla::drawWatchFace() {
    initialize();
    drawBattery();
    drawConnectivity();
    drawTime();
    drawDate();
    drawSteps();
    drawWeather();
}

void WatchyVanilla::drawTime() {
    uint16_t i;

    int16_t relTzHour[] = {0, 3, 12};
    int16_t relTzMin[] = {0, 0, 30};
    String tzName[] = {"PST", "EST", "IST"};

    String adjustedTime;

    lineY += DEFAULT_LINE_SPACING;

    for(i = 0; i < NUM_TZ; i++) {
        adjustedTime = getAdjustedTime(relTzHour[i], relTzMin[i]);
        display.setFont(&DSEG7Classic_Regular12pt7b);
        lineY += time.h;
        display.setCursor(0, lineY);
        display.print(adjustedTime);
        display.setFont(&FreeMono12pt7b);
        display.setCursor(time.w + DEFAULT_TIMEZONE_SPACING, lineY);
        display.print(tzName[i]);
        lineY += DEFAULT_LINE_SPACING;
    }
}

String WatchyVanilla::getAdjustedTime(int16_t hourOffset, int16_t minuteOffset) {
    int16_t displayMinute = (currentTime.Minute + minuteOffset) % 60;
    int16_t displayHour = (currentTime.Hour + hourOffset) % 24 + (currentTime.Minute + minuteOffset >= 60 ? 1 : 0);
    if (displayHour == 24) {
        displayHour = 0;
    }

    String timeStr("");
    if (displayHour < 10) {
        timeStr.concat("0");
    }
    timeStr.concat(displayHour);

    timeStr.concat(":");

    if (displayMinute < 10) {
        timeStr.concat("0");
    }
    timeStr.concat(displayMinute);

    return timeStr;
}

void WatchyVanilla::drawDate() {
    display.setFont(&FreeMono12pt7b);
    lineY += other.h;
    display.setCursor(0, lineY);
    display.print(dayShortStr(currentTime.Wday));
    display.print(" ");
    display.print(currentTime.Year + 1970);
    display.print("-");
    if (currentTime.Month < 10) {
        display.print("0");
    }
    display.print(currentTime.Month);
    display.print("-");
    if (currentTime.Day < 10) {
        display.print("0");
    }
    display.println(currentTime.Day);
    lineY += DEFAULT_LINE_SPACING;
}

void WatchyVanilla::drawSteps() {
    if (currentTime.Hour == 0 && currentTime.Minute == 0) {
        sensor.resetStepCounter();
    }

    display.setFont(&FreeMono12pt7b);
    lineY += other.h;

    uint32_t stepCount = sensor.getCounter();
    display.setCursor(0, lineY);
    display.print("Steps: ");
    display.println(stepCount);

    lineY += DEFAULT_LINE_SPACING;
}

void WatchyVanilla::drawBattery() {
    display.setFont(&FreeMono12pt7b);
    lineY += other.h;

    float V = getBatteryVoltage();
    uint16_t batP = (int)((V - BATTERY_VOLTAGE_MIN) / (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN) * 100);

    display.setFont(&FreeMono12pt7b);
    display.setCursor(0, lineY);
    display.print("Battery:  ");
    if (batP < 100) {
        display.print(" ");
    }
    display.print(batP);
    display.println("%");

    lineY += DEFAULT_LINE_SPACING;
}

void WatchyVanilla::drawConnectivity() {
    display.setFont(&FreeMono12pt7b);
    lineY += other.h;

    display.setFont(&FreeMono12pt7b);
    display.setCursor(0, lineY);
    display.print("Wifi: ");
    display.print(WIFI_CONFIGURED ? "Y" : "N");

    display.print(" BLE: ");
    display.println(BLE_CONFIGURED ? "Y" : "N");

    lineY += DEFAULT_LINE_SPACING;
}

void WatchyVanilla::drawWeather() {
    int16_t x1, y1;
    uint16_t w, h;
    weatherData currentWeather = getWeatherData();
    int8_t temperature = currentWeather.temperature;
    int16_t weatherConditionCode = currentWeather.weatherConditionCode;

    display.setFont(&FreeMono12pt7b);
    lineY += other.h;

    display.setCursor(0, lineY);
    display.print(temperature);

    display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
    display.print(" F");

    display.print(" ");
    String weatherIcon("");
    // https://openweathermap.org/weather-conditions
    if (weatherConditionCode > 801) {
        // Cloudy
        weatherIcon = "CLOUDY";
    }
    else if (weatherConditionCode == 801) {
        // Few Clouds
        weatherIcon = "L CLOUD";
    }
    else if (weatherConditionCode == 800) {
        // Clear
        weatherIcon = "CLEAR";
    }
    else if (weatherConditionCode >= 700) {
        // Atmosphere
        weatherIcon = "ATMO";
    }
    else if (weatherConditionCode >= 600) {
        // Snow
        weatherIcon = "SNOW";
    }
    else if (weatherConditionCode >= 500) {
        // Rain
        weatherIcon = "RAIN";
    }
    else if (weatherConditionCode >= 300) {
        // Drizzle
        weatherIcon = "L RAIN";
    }
    else if (weatherConditionCode >= 200) {
        // Thunderstorm
        weatherIcon = "STORM";
    }
    display.println(weatherIcon);

    display.setCursor(w + DEFAULT_DEGREE_SYMBOL_SPACING, lineY - h / 2);
    display.print("o");
}

Position WatchyVanilla::getNextLinePositionTime() {
    return getNextLinePositionHelper(&DSEG7Classic_Regular12pt7b, TIME_CALLIBRATION_STRING);
}

Position WatchyVanilla::getNextLinePositionOther() {
    return getNextLinePositionHelper(&FreeMono12pt7b, OTHER_CALLIBRATION_STRING);
}

Position WatchyVanilla::getNextLinePositionHelper(const GFXfont *font, String callibration) {
    int16_t x1, y1;
    uint16_t w, h;

    display.setFont(font);
    display.getTextBounds(callibration, 0, 0, &x1, &y1, &w, &h);

    Position pos;
    pos.x1 = x1;
    pos.y1 = y1;
    pos.w = w;
    pos.h = h;

    return pos;
}

void WatchyVanilla::initialize() {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    lineY = 0;
    time = getNextLinePositionTime();
    other = getNextLinePositionOther();
}