#ifndef WATCHYSDK_H
#define WATCHYSDK_H

#ifndef WATCHY_H
#include "Watchy.h"
#endif

class WatchySDK {
    public:
        class App {
            public:
                void (*onStart)(void);
                void (*onStop)(void);
                void (*onButtonUp)(void);
                void (*onButtonDown)(void);
                void (*onButtonMenu)(void);
                void (*onButtonBack)(void);
        };

        class Text : App {
            public:
                int pos_x = 0;
                int pos_y = 0;
                char* text;
                const GFXfont* font = &FreeMonoBold9pt7b;
        };

        class InputText : Text{
            public:
                Text app;    
                char* input;
                int inputLength = 0;
                bool isPassword = false;
                void (*onValueChange)(void) = NULL;
        };

        //InputInt
        class InputInt : Text{
            public:
                Text app;
                int value = 0;
                int min = 0;
                int max = 0;
                int step = 1;
                int color = GxEPD_WHITE;
                int colorText = GxEPD_BLACK;
                void (*onValueChange)(void) = NULL;
        };

        class InputFloat : Text{ 
            public:
                Text app;
                float value = 0;
                float min = 0;
                float max = 0;
                float step = 1;
                int color = GxEPD_WHITE;
                int colorText = GxEPD_BLACK;
                void (*onValueChange)(void) = NULL;
        };

        class Button : Text {
            public:
                Text app;
            
                int width = 0;
                int height = 0;
            
                int color = GxEPD_WHITE;
                int colorPressed = GxEPD_BLACK;
                int colorText = GxEPD_BLACK;
                int colorTextPressed = GxEPD_WHITE;
            
                void (*onPressed)(void) = NULL;
        };

        class Item : App {
            public:
                App app;
                void (*onSelect)(void) = NULL;
        };

        class Collection {
            public:
                int itemCount = 0;
                class Item *items;    
        };

        class ButtonMenu : Collection {
            public:
                Collection collection;
                int selected = 0;
        };

        class TextMenu : Collection {
            public:                
                Collection collection;
                int selected = 0;
        };

        class Image : App {
            public:
                App app;
                const unsigned char* image;
                int width = 0;
                int height = 0;
        };

    public:
    //Render Method (Headers):
        int handleInput(WatchySDK::App app);
        void render(WatchySDK::App app);
        /*
        void persistSetting(char* key, char* value);
        char* getSetting(char* key);
        */
        void _do();
};

#endif