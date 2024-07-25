#include "WatchySDK.h"
#include "WatchySDK_Apps.h"

#ifdef ARDUINO_ESP32S3_DEV
  #define ACTIVE_LOW 0
#else
  #define ACTIVE_LOW 1
#endif

#include <iostream>

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return static_cast<const Base*>(ptr) != nullptr;
}

int WatchySDK::handleInput(WatchySDK::App *app){
    //Handle the input


    //If UP or DOWN is pressed
    if (digitalRead(UP_BTN_PIN) == ACTIVE_LOW){
        Serial.println("UP");
        app->onButtonUp();
        return UP_BTN_PIN;
    }

    if (digitalRead(DOWN_BTN_PIN) == ACTIVE_LOW){
        Serial.println("DOWN");
        app->onButtonDown();
        return DOWN_BTN_PIN;
    }

    if (digitalRead(MENU_BTN_PIN) == ACTIVE_LOW){
        Serial.println("MENU");
        app->onButtonMenu();
        return MENU_BTN_PIN;
    }

    if (digitalRead(BACK_BTN_PIN) == ACTIVE_LOW){
        Serial.println("BACK");
        app->onButtonBack();
        return BACK_BTN_PIN;
    }
    return -1;
}



//Implement the method render(App app) that may be able to render All app->
void WatchySDK::render(WatchySDK::App *app, int argc, char* argv[]){ 
    Serial.println("FullScreen");
    app->display().setFullWindow();
    Serial.print("Darkmode: ");
    Serial.println(app->darkMode);
    app->display().fillScreen(app->darkMode ? GxEPD_BLACK : GxEPD_WHITE);
    app->display().setTextColor(app->darkMode ? GxEPD_WHITE : GxEPD_BLACK);
   
    Serial.print("onStart");
    Serial.println(argc);
    Serial.print(": ");
    for(int i = 0; i < argc; i++){
        Serial.print(argv[i]);
        Serial.print(" ");
    }

    app->onStart(argc, argv);

    Serial.println("render loop");
    Serial.println(app->interval);
    
    while(1){
            unsigned long currentMillis = millis();

            int input = handleInput(app);
               //If back button is pressed
            if (input == BACK_BTN_PIN){            
                app->onButtonBack();
                break;
            }
    

            if (currentMillis - app->previousMillis > app->interval) {
                app->previousMillis = currentMillis;
                //Render

                Serial.println("render app");
                //If type is text
                if(instanceof<WatchySDK::Text>(app)){
                    Serial.println("Text");
                    WatchySDK::Text *textApp = (WatchySDK::Text*) app;
                    textApp->render();
                }
                Serial.println("refresh");
                app->display().display(true);
        }
    }
    Serial.print("onStop: ");
    Serial.println(0);
    app->onStop(0);
}


void WatchySDK::launchApp(WatchySDK::App *app, int argc, char* argv[]){
  Serial.println("Launching SDK App");
  render(app, argc, argv);
  Serial.println("SDK App Finished");
}
