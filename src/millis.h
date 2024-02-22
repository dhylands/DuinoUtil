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
 *   @file   millis.h
 *
 *   @brief  Class whih performs a sequence of actions on specfied intervals.
 *
 ****************************************************************************/

#pragma once

#if defined(ARDUINO)
#include <Arduino.h>

// Arduino.h defines:
//
//  unsigned long millis();

#else

#include <time.h>
#include <inttypes.h>

//! Return the number of milliseconds of uptime.
//! @returns the number of milliseconds since boot.
uint32_t millis();

#endif
