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
 *   @file   DeathTest.cpp
 *
 *   @brief  Helpers for DeathTests
 *
 ****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {

//! Override __assert_fail (called by assert).
//! @details The normal __assert_fail calls abort() which causes the fact that assert
//!          was called to get missed by coverage processing. So we override it and
//!          exit(1) instead.
void __assert_fail(
    const char* assertion,  //!< [in] Assertion that fails.
    const char* file,       //!< [in] Name of file that the assert happens in.
    unsigned int line,      //!< [in] Line number within the file of the assert.
    const char* function    //!< [in] Function that the assert happens in.
    ) noexcept {
    fprintf(stderr, "%s:%u: %s: Assertion `%s' failed.\n", file, line, function, assertion);
    fflush(stderr);
    exit(1);
}

}  // extern "C"
