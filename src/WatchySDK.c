#include "WatchySDK.h"

//Implement the method render(App app) that may be able to render All App.
void render(App *app){
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
        if (typeof(app.app) == typeof(Collection)){
            for (int i = 0; i < app.itemCount; i++){
                render(app.items[i].app);
            }
        }

        //if App.app exist, render it
        if (app.app != NULL){
            render(app.app);
        }

        //if App.app == Text, render it
        if (typeof(app.app) == typeof(Text)){
            display.setFont(app.font);
            display.setCursor(app.pos_x, app.pos_y);
            display.print(app.text);        
        } 


        //ALL the logic
        switch (input){
            case UP:
                app.onButtonUp()
                break;
            case DOWN:
                app.onButtonDown()
                break;
            case MENU:
                app.onButtonMenu()
                break;
            case BACK:
                app.onButtonBack()
                break;
        }

        //if back is pressed, onStop()
        if (app.onBack()){
            Serial.println("onStop");
            app.onStop();
        }
    }
    
}

void handleInput(App *app){
    //Handle the input
    int input = handleButtonPress();

    //If UP or DOWN is pressed
    if (input == UP_BTN_PIN){
        app.onButtonUp();
    }

    if (input == DOWN_BTN_PIN){
        app.onButtonDown();
    }

    //If MENU is pressed

    if (input == MENU_BTN_PIN){
        app.onButtonMenu();
    }

    //If BACK is pressed

    if (input == BACK_BTN_PIN){
        app.onButtonBack();
    }
}

void _do(){

}