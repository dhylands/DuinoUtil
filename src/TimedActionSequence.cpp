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
 *   @file   TimedActionSequence.cpp
 *
 *   @brief  Class whih performs a sequence of actions on specfied intervals.
 *
 ****************************************************************************/

#include "TimedActionSequence.h"

#include "millis.h"
#include "Util.h"

void TimedActionSequence::init() {
    this->seq_idx = -1;
    this->lastAction = 0;
    if (this->mode == Mode::CONTINUUS) {
        this->start();
    }
}

void TimedActionSequence::run() {
    if (!this->running()) {
        // Sequence hasn't been started yet, or has already finished.
        return;
    }
    if (millis() - this->lastAction < this->seq[this->seq_idx].delay_msec) {
        // Not enough time has elapsed
        return;
    }

    this->seq_idx++;

    if (this->seq_idx >= static_cast<ssize_t>(this->seq_len)) {
        if (this->is_continuous()) {
            this->seq_idx = 0;
        } else {
            return;
        }
    }

    this->lastAction = millis();
    this->seq[this->seq_idx].action();
}

void TimedActionSequence::start() {
    if (this->running()) {
        return;
    }
    this->seq_idx = 0;
    this->lastAction = millis();
    this->seq[this->seq_idx].action();
}
