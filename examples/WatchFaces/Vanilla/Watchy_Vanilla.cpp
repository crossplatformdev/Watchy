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

    int relTzHour[] = {0, 3, 12};
    int relTzMin[] = {0, 0, 30};
    String tzName[] = {"PST", "EST", "IST"};

    String adjustedTime;
    int16_t x1, y1;
    uint16_t w, h;

    lineY += 2;

    display.setFont(&DSEG7Classic_Regular12pt7b);
    display.getTextBounds("88:888", 0, 0, &x1, &y1, &w, &h);

    for(i = 0; i < 3; i++) {
        adjustedTime = getAdjustedTime(relTzHour[i], relTzMin[i]);
        display.setFont(&DSEG7Classic_Regular12pt7b);
        lineY += h;
        display.setCursor(0, lineY);
        display.print(adjustedTime);
        display.setFont(&FreeMono12pt7b);
        display.setCursor(w + 5, lineY);
        display.print(tzName[i]);
        lineY += 2;
    }
}

String WatchyVanilla::getAdjustedTime(int hourOffset, int minuteOffset) {
    int displayMinute = (currentTime.Minute + minuteOffset) % 60;
    int displayHour = (currentTime.Hour + hourOffset) % 24 + (currentTime.Minute + minuteOffset >= 60 ? 1 : 0);

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
    int16_t x1, y1;
    uint16_t w, h;
    display.setFont(&FreeMono12pt7b);
    display.getTextBounds("X1Il^qpyi", 0, 0, &x1, &y1, &w, &h);
    lineY += h;
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
    lineY += 2;
}

void WatchyVanilla::drawSteps() {
    if (currentTime.Hour == 0 && currentTime.Minute == 0) {
        sensor.resetStepCounter();
    }

    int16_t x1, y1;
    uint16_t w, h;
    display.setFont(&FreeMono12pt7b);
    display.getTextBounds("X1Il^qpyi", 0, 0, &x1, &y1, &w, &h);
    lineY += h;

    uint32_t stepCount = sensor.getCounter();
    display.setCursor(0, lineY);
    display.print("Steps: ");
    display.println(stepCount);

    lineY += 2;
}

void WatchyVanilla::drawBattery() {
    int16_t x1, y1;
    uint16_t w, h;
    display.setFont(&FreeMono12pt7b);
    display.getTextBounds("X1Il^qpyi", 0, 0, &x1, &y1, &w, &h);
    lineY += h;

    float V = getBatteryVoltage();

    display.setFont(&FreeMono12pt7b);
    display.setCursor(0, lineY);
    display.print("Batt V: ");
    display.print(V);
    display.println("");

    lineY += 2;
}

void WatchyVanilla::drawConnectivity() {
    int16_t x1, y1;
    uint16_t w, h;
    display.setFont(&FreeMono12pt7b);
    display.getTextBounds("X1Il^qpyi", 0, 0, &x1, &y1, &w, &h);
    lineY += h;

    display.setFont(&FreeMono12pt7b);
    display.setCursor(0, lineY);
    display.print("Wifi: ");
    display.print(WIFI_CONFIGURED ? "Y" : "N");

    display.print(" BLE: ");
    display.println(BLE_CONFIGURED ? "Y" : "N");

    lineY += 2;
}

void WatchyVanilla::drawWeather() {
    weatherData currentWeather = getWeatherData();
    int8_t temperature = currentWeather.temperature;
    int16_t weatherConditionCode = currentWeather.weatherConditionCode;
    int16_t x1, y1;
    uint16_t w, h;

    display.setFont(&FreeMono12pt7b);
    display.getTextBounds("X1Il^qpyi", 0, 0, &x1, &y1, &w, &h);
    lineY += h;

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

    display.setCursor(w + 4, lineY - h / 2);
    display.print("o");
}

void WatchyVanilla::initialize() {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    lineY = 0;
}