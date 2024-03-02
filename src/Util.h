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

#include <cassert>
#include <cstddef>
#include <type_traits>

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

//! Template for storing bits in an integral value.
//! @tparam T Underlying type to hold bits.
template <typename T>
struct Bits {
    static_assert(std::is_integral_v<T>);

    //! The type used to store values for this collection of bits.
    using Type = T;

    //! Default constructor.
    Bits() : value{} {}

    //! Constructor using an initial value.
    Bits(
        const T& value  //!< [in] Initial value.
    ) : value{value} {}

    //! Checks if all of the bits in a mask are set.
    //! @returns true if all of the bits in `mask` are set.
    //! @returns false if any bits in `mask` are clear.
    bool isSet(
        T mask  //!< [in] Mask to check.
    ) {
        return (this->value & mask) == mask;
    }

    //! Checks if all of the bits in a mask are clear.
    //! @returns true if all of the bits in `mask` are set.
    //! @returns false if any bits in `mask` are clear.
    bool isClear(
        T mask  //!< [in] Mask to check.
    ) {
        return (this->value & mask) == 0;
    }

    //! Sets all of the bits in a mask.
    void set(
        T mask  //!< [in] Mask of bits to set.
    ) {
        this->value |= mask;
    }

    //! Clears all of the bits in a mask.
    void clear(
        T mask  //!< [in] Mask of bits to set.
    ) {
        this->value &= ~mask;
    }

    //! Comparison operator between 2 Bits objects
    //! @returns true if the 2 objects are equal
    //! @returns false if the 2 objects are not equal
    bool operator==(
        const Bits<T>& rhs  //! [in] right hand side of comparison
    ) const {
        return this->value == rhs.value;
    }

    //! Comparison operator between 2 Bits objects
    //! @returns true if the 2 objects are not equal
    //! @returns false if the 2 objects are equal
    bool operator!=(
        const Bits<T>& rhs  //!< [in] right hand side of comparison
    ) const {
        return !(*this == rhs);
    }

    //! Comparison operator between this objects value and another value.
    //! @returns true if the 2 objects are equal
    //! @returns false if the 2 objects are not equal
    bool operator==(
        const T& rhs  //!< [in] right hand side of comparison.
    ) const {
        return this->value == rhs;
    }

    //! Comparison operator between this objects value and another value.
    //! @returns true if the 2 objects are not equal
    //! @returns false if the 2 objects are equal
    bool operator!=(
        const T& rhs  //!< [in] right hand side of comparison.
    ) const {
        return !(*this == rhs);
    }

    T value;  //!< Value containing bits.
};
