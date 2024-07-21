#ifndef WATCHYSDK_TYPEDEFS_H
#define WATCHYSDK_TYPEDEFS_H


struct App{
    void (*onStart)(void)                          = NULL;
    void (*onStop)(void)                           = NULL;
    void (*onButtonUp)(void)                       = NULL;
    void (*onButtonDown)(void)                     = NULL;
    void (*onButtonMenu)(void)                     = NULL;
    void (*onButtonBack)(void)                     = NULL;
} App;

struct Text : App{
    int pos_x = 0;
    int pos_y = 0;
    char* text;
    const GFXfont* font = &FreeMonoBold9pt7b;
} Text;

struct InputText : Text{
    Text app;    
    char* input;
    int inputLength = 0;
    bool isPassword = false;
    void (*onValueChange)(void) = NULL;
} InputText;

//InputInt
struct InputInt : Text{
    Text app;
    int value = 0;
    int min = 0;
    int max = 0;
    int step = 1;
    int color = GxEPD_WHITE;
    int colorText = GxEPD_BLACK;
    void (*onValueChange)(void) = NULL;
} InputInt;

struct InputFloat : Text{ 
    Text app;
    float value = 0;
    float min = 0;
    float max = 0;
    float step = 1;
    int color = GxEPD_WHITE;
    int colorText = GxEPD_BLACK;
    void (*onValueChange)(void) = NULL;
} InputFloat;

struct Button : Text {
    Text app;
    
    int width = 0;
    int height = 0;
    
    int color = GxEPD_WHITE;
    int colorPressed = GxEPD_BLACK;
    int colorText = GxEPD_BLACK;
    int colorTextPressed = GxEPD_WHITE;
    
    void (*onPressed)(void) = NULL;
} Button;

struct Item : App {
    App app;
    void (*onSelect)(void) = NULL;
} Item;

struct Collection {
    int itemCount = 0;
    struct Item *items;    
} Collection;

struct ButtonMenu : Collection {
    Collection collection;
    int selected = 0;
} ButtonMenu;

struct TextMenu : Collection {
    Collection collection;
    int selected = 0;
} TextMenu;

struct Image : App {
    App app;
    const unsigned char* image;
    int width = 0;
    int height = 0;
} Image;

#endif