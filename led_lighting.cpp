//
// Created by kiryanenko on 14.09.19.
//

#include <Wire.h>
#include <GyverEncoder.h>
#include "Settings.h"
#include "input/InputManager.h"
#include "input/EncoderHandler.h"

Settings *settings = Settings::getInstance();

InputManager input_manager;

#ifdef ENCODER_ENABLED
Encoder *encoder;
EncoderHandler encoderHandler;
#endif

void setup()
{
    Wire.begin();
    Serial.begin(9600);

#ifdef ENCODER_ENABLED
#ifdef ENCODER_KEY
    encoder = new Encoder(ENCODER_S1, ENCODER_S2, ENCODER_KEY);
#else
    encoder = new Encoder(ENCODER_S1, ENCODER_S2);
#endif
    encoder->setType((modes) ENCODER_TYPE);
#endif
}

void loop()
{
    settings->checkCommit();

#ifdef ENCODER_ENABLED
    encoderHandler.handle(input_manager, *encoder);
#endif

    input_manager.tick();
}
