#ifndef HELLOMOONPHASE_H
#define HELLOMOONPHASE_H

#include "Watchy.h"
#include "MoonPhase.h"
#include "WatchySDK.h"

extern time_t currentTime;

class ShowMoonPhase : public WatchySDK::Text{
    public:
        MoonPhase mp;
        ShowMoonPhase(time_t epoch) : WatchySDK::Text()
        {
            mp = MoonPhase();
            text = (char*) getMoonPhase(epoch).c_str();
        };

        void onStart(int argc, char* argv[]){
            display().setFullWindow();
            display().fillScreen(GxEPD_BLACK);
            display().setFont(&FreeMonoBold9pt7b);
            display().setTextColor(GxEPD_WHITE);
            display().setCursor(0, 10);
        
            display().setCursor(0, MENU_HEIGHT);

            display().println(text);
        
            display().display(true); // full refresh

            guiState = APP_STATE;
        } 
    private:       
        String getMoonPhase(time_t epoch){        
            mp.calculate(epoch);
            
            String str = "Date: ";
            str += String(mp.jDate);
            str += "\n";
            str += "Phase: ";
            str += String(mp.phase);
            str += "\n";
            str += "Age: ";
            str += String(mp.age);
            str += " days\n";
            str += "Visibility: ";
            str += String(mp.fraction);
            str += "%\n";
            str += "Distance: ";
            str += String(mp.distance);
            str += " er\n";
            str += "Lat: ";
            str += String(mp.latitude, 6);
            str += "°\n";
            str += "Lon: ";
            str += String(mp.longitude, 6);
            str += "°\n";
            str += "Ph.: ";
            str += String(mp.phaseName);
            str += "\n";
            str += "Zodiac: ";
            str += String(mp.zodiacName);

            return str;
        }
};
#endif