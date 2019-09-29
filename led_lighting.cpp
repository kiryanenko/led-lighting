//
// Created by kiryanenko on 14.09.19.
//

#include <Arduino.h>
#include <Wire.h>
#include "Settings.h"
#include "input/InputManager.h"
#include "led/LedsManager.h"

#ifdef ENCODER_ENABLED
#include "input/EncoderHandler.h"
#endif

#ifdef TTP229_ENABLED
#include "input/TTP229Handler.h"
#endif

InputManager input_manager;
LedsManager leds_manager;

#ifdef ENCODER_ENABLED
Encoder *encoder;
EncoderHandler encoderHandler;
#endif

#ifdef TTP229_ENABLED
TTP229 ttp229;
TTP229Handler ttp229_handler;
#endif

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);

#ifdef RESET
    settings->reset();
#endif


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
#ifdef ENCODER_ENABLED
    encoder->tick();
    encoderHandler.handle(input_manager, *encoder);
#endif

#ifdef TTP229_ENABLED
    ttp229.readKeys();
    ttp229_handler.handle(input_manager, ttp229);
#endif

    input_manager.tick();
    leds_manager.tick();

    settings->checkCommit();

//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(300);                       // wait for a second
//    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//    delay(300);
}
