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

//! The counter that millis returns.
//! @details for unit tests, this allows the milliseconds to be controlled
//!          very precisely.

extern uint32_t test_millis_count;

// Return test_millis_count
uint32_t millis();
