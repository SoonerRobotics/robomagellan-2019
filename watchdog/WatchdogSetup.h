#ifndef WATCHDOG_SETUP_H
#define WATCHDOG_SETUP_H

#include <Arduino.h>
#include "WatchdogGlobals.h"

void watchdogSetup()
{
    if(IS_DEBUG)
    {
        Serial.begin(9600);
    }
}

#endif