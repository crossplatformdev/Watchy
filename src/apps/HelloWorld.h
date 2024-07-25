#include "WatchySDK.h"

class HelloWorld : public WatchySDK::Text{
    public:
        HelloWorld(){
            pos_x = 50;
            pos_y = 50;
            text = (char*) "Hello World!";
        };
};