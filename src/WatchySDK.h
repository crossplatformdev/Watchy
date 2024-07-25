#ifndef WATCHYSDK_H
#define WATCHYSDK_H

#include "Watchy.h"

class WatchySDK {
    public:       
        class App {
            public:
                virtual ~App() {};
                void onStart(int argc, char* argv[]){ return; };
                void onStop(int code){ return; };
                void onButtonUp(){ return; };
                void onButtonDown(){ return; };
                void onButtonMenu(){ return; };
                void onButtonBack(){ return; };
                virtual void render() { 
                    display().setTextColor(darkMode ? whiteColor : blackColor);
                    display().fillScreen(darkMode ? blackColor : whiteColor);                    
                 };

                GxEPD2_BW<WatchyDisplay, WatchyDisplay::HEIGHT> display() { return Watchy::display; };

                long previousMillis = 0;
                long interval       = 200;
                bool darkMode = false;
                int whiteColor = GxEPD_WHITE;
                int blackColor = GxEPD_BLACK;
        };

        class Text : public App {
            public:
                int pos_x = 0;
                int pos_y = 0;
                char* text;
                const GFXfont* font = &FreeMonoBold9pt7b;
                virtual void render(){ 
                    
                    App::render();

                    display().setFont(font);
                    display().setCursor(pos_x, pos_y);
                    display().print(text); 
                    //Makes the UI stay in APP. DO NOT PUT for toasts.
                    guiState = APP_STATE;
                }
        };

        class InputText : public Text{
            public:
                Text app;    
                char* input;
                int inputLength = 0;
                bool isPassword = false;
                void onValueChange(char* value){ return; };
                virtual void render(){
                    display().setFullWindow();
                    display().fillScreen(darkMode ? GxEPD_BLACK : GxEPD_WHITE);
                    display().setTextColor(darkMode ? GxEPD_WHITE : GxEPD_BLACK);

                    guiState = APP_STATE;

                    display().setFont(font);
                    display().setCursor(pos_x, pos_y);
                    display().print(text);
                    display().print(input);             

                    display().display(true);
                }
        };

        //InputInt
        class InputInt : public Text{
            public:
                Text app;
                int value = 0;
                int min = 0;
                int max = 0;
                int step = 1;
                int color = GxEPD_WHITE;
                int colorText = GxEPD_BLACK;
                void onValueChange(char* value){ return; };
                virtual void render(){
                    display().setFullWindow();
                    display().fillScreen(darkMode ? GxEPD_BLACK : GxEPD_WHITE);
                    display().setTextColor(darkMode ? GxEPD_WHITE : GxEPD_BLACK);

                    guiState = APP_STATE;

                    display().setFont(font);
                    display().setCursor(pos_x, pos_y);
                    display().print(text);
                    display().print(value);             

                    display().display(true);                    
                }
        };

        class InputFloat : public Text{ 
            public:
                Text app;
                float value = 0;
                float min = 0;
                float max = 0;
                float step = 1;
                int color = GxEPD_WHITE;
                int colorText = GxEPD_BLACK;
                void onValueChange(char* value){ return; };        
                virtual void render(){
                    display().setFullWindow();
                    display().fillScreen(darkMode ? GxEPD_BLACK : GxEPD_WHITE);
                    display().setTextColor(darkMode ? GxEPD_WHITE : GxEPD_BLACK);

                    guiState = APP_STATE;

                    display().setFont(font);
                    display().setCursor(pos_x, pos_y);
                    display().print(text);
                    display().print(value);             

                    display().display(true);


                }
        };

        class Button : public Text {
            public:
                Text app;
            
                int width = 0;
                int height = 0;
            
                int color = GxEPD_WHITE;
                int colorPressed = GxEPD_BLACK;
                int colorText = GxEPD_BLACK;
                int colorTextPressed = GxEPD_WHITE;
            
                void onPressed(){ 
                    if(darkMode){
                        display().fillRect(pos_x, pos_y, width, height, colorPressed);
                        display().setTextColor(colorTextPressed);
                    } else {
                        display().fillRect(pos_x, pos_y, width, height, color);
                        display().setTextColor(colorText);
                    }
                 };

                virtual void render(){
                    display().setFont(font);
                    display().fillRect(pos_x, pos_y, width, height, color);
                    display().setTextColor(colorText);
                    
                    display().setCursor(pos_x + (width / 2), pos_y + (height / 2));
                    display().print(text); 
                }
        };
        explicit WatchySDK() {};
        static int handleInput(WatchySDK::App *app);
        static void render(WatchySDK::App *app, int argc, char* argv[]);
        static void launchApp(WatchySDK::App *app, int argc, char* argv[]);
};
#endif