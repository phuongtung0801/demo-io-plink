#ifndef _OTA_H
#define _OTA_H

#include <WebServer.h>
#include <Update.h>

class UpdateOTA{
public:
    void initOTA();
    void loopOTA();
};

extern UpdateOTA PyrOTA;

#endif