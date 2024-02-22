/****************************************************************************
 *
 *   @copyright Copyright (c) 2024 Dave Hylands     <dhylands@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the MIT License version as described in the
 *   LICENSE file in the root of this repository.
 *
 ****************************************************************************/
/**
 *   @file   Heartbeat.ino
 *
 *   @brief  Example using the TimedActionSequence.
 *
 ****************************************************************************/

#include <Arduino.h>

#include "DuinoUtil.h"

#if !defined(LED_BUILTIN)
#error No definition for LED_BUILTIN
#endif

static int counter = 0;

static void toggle_led() {
    if (digitalRead(LED_BUILTIN) == PinStatus::LOW) {
        digitalWrite(LED_BUILTIN, PinStatus::HIGH);
        Serial.print('*');
    } else {
        digitalWrite(LED_BUILTIN, PinStatus::LOW);
        Serial.print('.');
    }
    counter++;
    if (counter == 40) {
        Serial.println("");
        counter = 0;
    }
}

static TimedActionSequence::Action heartbeat_list[] = {
    {toggle_led, 100},
    {toggle_led, 100},
    {toggle_led, 100},
    {toggle_led, 700},
};
static TimedActionSequence heartbeat{heartbeat_list, LEN(heartbeat_list)};

//! One time initialization.
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    heartbeat.init();
    Serial.begin();
}

//! Runs indefinitely
void loop() {
    heartbeat.run();
}
