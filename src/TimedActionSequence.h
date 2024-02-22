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
 *   @file   TimedActionSequence.h
 *
 *   @brief  Class whih performs a sequence of actions on specfied intervals.
 *
 ****************************************************************************/

#pragma once

#include <sys/types.h>

#include <cstdint>
#include <functional>

//! Performs a sequence of actions with a time interval between each one.
class TimedActionSequence {
 public:
    //! Is the sequence continuous or one shot?
    enum class Mode {
        CONTINUUS,  //!< Sequence repeats
        ONE_SHOT,   //!< Sequence runs once and stops.
    };

    //! Single Action of the sequence.
    struct Action {
        std::function<void()> action;  //!< Action to perform.
        uint32_t delay_msec;           //!< Amount of time to delay after performing action.
    };

    //! Constructor
    TimedActionSequence(
        Action* seq,                 //!< [in] The sequence of actions to perform.
        size_t seq_len,              //!< [in] Length of the sequence.
        Mode mode = Mode::CONTINUUS  //!< [in] Type of sequence
        )
        : seq{seq}, seq_len{seq_len}, mode{mode} {}

    //! Determines if the sequence has been started yet or not.
    //! @returns true if the sequence has been started..
    //! @return  false if the sequence hasn't been started yet.
    bool started() const { return this->seq_idx >= 0; }

    //! Determines if the sequence is currently running or not.
    //! @returns true if the sequence is currently running.
    //! @returns false if the sequence is not running.
    bool running() const { return this->started() && !this->done(); }

    //! Determines if the sequence has finished running.
    //! @returns true if the sequence has finished running.
    //! @returns false if the sequence has not finished running.
    bool done() const { return this->seq_idx >= static_cast<ssize_t>(this->seq_len); }

    //! Determines whether the sequence is continuus or one-shot.
    //! @return Mode::CONTINUOUS if this is a continuous sequence.
    //! @return Mode::ONE_SHOT is this is a one time sequence.
    bool is_continuous() const { return this->mode == Mode::CONTINUUS; }

    //! Initializes the Action sequence.
    void init();

    //! Runs the sequence, as appropriate
    void run();

    //! Starts the sequence if it isn't currently running.
    void start();

 private:
    Action* const seq;  //!< The sequence being run.
    size_t seq_len;     //!< The length of the sequence.
    Mode mode;          //!< Is the sequence one-shot or continuous?

    uint32_t lastAction = 0;  //!< Last time that the LED was toggled.
    ssize_t seq_idx = -1;     //!< Where we are in the sequence.
};
