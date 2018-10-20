#ifndef RC_SETUP_H
#define RC_SETUP_H

#include <Arduino.h>
#include "RC_Globals.h"

void rc_setup()
{
    if(IS_DEBUG)
    {
        Serial.begin(9600);
    }
}

#endif