#ifndef WATCHYSDK_APPS_H
#define WATCHYSDK_APPS_H

#include "WatchySDK.h"

class HelloWorld : public WatchySDK::Text{
    public:
        HelloWorld(){
            text = (char*) "Hello World!";
        };
};


#endif