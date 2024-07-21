#include "WatchySDK.h"
#include "Watchy.h"

int WatchySDK::handleInput(App app){
    //Handle the input


    //If UP or DOWN is pressed
    if (digitalRead(UP_BTN_PIN) == ACTIVE_LOW){
        app.onButtonUp();
        return UP_BTN_PIN;
    }

    if (digitalRead(DOWN_BTN_PIN) == ACTIVE_LOW){
        app.onButtonDown();
        return DOWN_BTN_PIN;
    }

    if (digitalRead(MENU_BTN_PIN) == ACTIVE_LOW){
        app.onButtonMenu();
        return MENU_BTN_PIN;
    }

    if (digitalRead(BACK_BTN_PIN) == ACTIVE_LOW){
        app.onButtonBack();
        return BACK_BTN_PIN;
    }

}


//Implement the method render(App app) that may be able to render All App.
void WatchySDK::render(App app){
        //All the logic
    //Handle button press
    
    //Render
    Serial.println("onStart");
    app.onStart();
    //Handle button press
    while(1){

        handleInput(app);

        //Render
        Serial.println("render app");
        //for all elements in a collection, render it
        if(app.app != NULL){
            if (typeof app.app == typeof Collection){
                for (int i = 0; i < app.itemCount; i++){
                    render(app.items[i].app);
                }
            }

            //if App.app exist, render it
            if (app.app != NULL){
                render(app.app);
            }

            //if App.app == Text, render it
            if (typeof app.app == typeof Text){
                display.setFont(app.font);
                display.setCursor(app.pos_x, app.pos_y);
                display.print(app.text);        
            } 
        } else {
            //if App.app == Text, render it
            if (typeof app == typeof Text){
                display.setFont(app.font);
                display.setCursor(app.pos_x, app.pos_y);
                display.print(app.text);        
            } 
        }


        //ALL the logic
        switch (input){
            case UP:
                app.onButtonUp();
                break;
            case DOWN:
                app.onButtonDown();
                break;
            case MENU:
                app.onButtonMenu();
                break;
            case BACK:
                app.onButtonBack();
                break;
        }

        //if back is pressed, onStop()
        if (app.onBack()){
            Serial.println("onStop");
            app.onStop();
        }
    }
    
}

void WatchySDK::_do(){

}