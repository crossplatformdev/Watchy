#ifndef WATCHYSDK_H
#define WATCHYSDK_H

#include "Watchy.h"

class WatchySDK : public Watchy {
    public:       
        class App {
            public:
                void (*onStart)(void);
                void (*onStop)(void);
                void (*onButtonUp)(void);
                void (*onButtonDown)(void);
                void (*onButtonMenu)(void);
                void (*onButtonBack)(void);
                void render() { return; };
        };

        class Text : public App {
            public:
                int pos_x = 0;
                int pos_y = 0;
                char* text;
                const GFXfont* font = &FreeMonoBold9pt7b;
                void render(){                
                    getDisplay().setFont(font);
                    getDisplay().setCursor(pos_x, pos_y);
                    getDisplay().print(text); 
                }
        };

        class InputText : public Text{
            public:
                Text app;    
                char* input;
                int inputLength = 0;
                bool isPassword = false;
                void (*onValueChange)(void) = NULL;
                void render(){
                    getDisplay().setFont(font);
                    getDisplay().setCursor(pos_x, pos_y);
                    getDisplay().print(text);
                    getDisplay().print(input);             
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
                void (*onValueChange)(void) = NULL;
                void render(){
                    getDisplay().setFont(font);
                    getDisplay().setCursor(pos_x, pos_y);
                    getDisplay().print(text);
                    getDisplay().print(value);             
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
                void (*onValueChange)(void) = NULL;
        
                void render(){
                    getDisplay().setFont(font);
                    getDisplay().setCursor(pos_x, pos_y);
                    getDisplay().print(text);
                    getDisplay().print(value);             
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
            
                void (*onPressed)(void) = NULL;

                void render(){
                    getDisplay().setFont(font);
                    getDisplay().fillRect(pos_x, pos_y, width, height, color);
                    getDisplay().setCursor(pos_x + (width / 2), pos_y + (height / 2));
                    getDisplay().print(text); 
                }
        };
        WatchySDK(const watchySettings &settings) : Watchy(settings) {};
        static int handleInput(WatchySDK::App *app);
        static void render(WatchySDK::App *app);
        static void launchApp(WatchySDK::App *app);
};
#endif