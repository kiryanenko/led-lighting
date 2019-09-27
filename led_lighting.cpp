//
// Created by kiryanenko on 14.09.19.
//

#include <Wire.h>
#include "Settings.h"
#include "input/InputManager.h"

Settings *settings = Settings::getInstance();
InputManager input_manager;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
    settings->checkCommit();
    input_manager.tick();
}
