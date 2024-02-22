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
 *   @file   Util.h
 *
 *   @brief  Simple utility functions/macros
 *
 ****************************************************************************/

#pragma once

#include <cstddef>

//! Returns the length of an array, but a compile time error if you pass in a pointer.
//! @tparam T The type of the object
//! @tparam N The length of the array
//! @returns The length of the array (in items).
template <typename T, size_t N>
size_t constexpr LEN(T (&)[N]) {
    return N;
}

//! Function that you can set a breakpoint on in gdb.
static inline void debug() {}
