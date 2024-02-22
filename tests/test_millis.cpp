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
 *   @file   test_millis.cpp
 *
 *   @brief  Provides a version of millis suitable for testing.
 *
 ****************************************************************************/

#include "millis.h"

uint32_t test_millis_count;

uint32_t millis() {
    return test_millis_count;
}
