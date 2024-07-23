#include "WatchySDK.h"
#include "WatchySDK_Apps.h"

#ifdef ARDUINO_ESP32S3_DEV
  #define ACTIVE_LOW 0
#else
  #define ACTIVE_LOW 1
#endif

int WatchySDK::handleInput(WatchySDK::App *app){
    //Handle the input


    //If UP or DOWN is pressed
    if (digitalRead(UP_BTN_PIN) == ACTIVE_LOW){
        app->onButtonUp();
        return UP_BTN_PIN;
    }

    if (digitalRead(DOWN_BTN_PIN) == ACTIVE_LOW){
        app->onButtonDown();
        return DOWN_BTN_PIN;
    }

    if (digitalRead(MENU_BTN_PIN) == ACTIVE_LOW){
        app->onButtonMenu();
        return MENU_BTN_PIN;
    }

    if (digitalRead(BACK_BTN_PIN) == ACTIVE_LOW){
        app->onButtonBack();
        return BACK_BTN_PIN;
    }
    return -1;
}



//Implement the method render(App app) that may be able to render All App.
void WatchySDK::render(WatchySDK::App *app){    
    app->onStart();

    while(1){
            
            int input = handleInput(app);
    
            //Render
            Serial.println("render app");
            
            //If type is text
            app->render();

            //If back button is pressed
            if (input == BACK_BTN_PIN){
                app->onButtonBack();
                break;
            }

            sleep(100);
    }

    app->onStop();
}


void WatchySDK::launchApp(WatchySDK::App *app){
  Serial.println("Launching SDK App");
  WatchySDK::App *activeApp = (WatchySDK::App *) app;
  render(activeApp);
  Serial.println("SDK App Finished");
}
