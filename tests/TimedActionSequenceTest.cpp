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
 *   @file   TimedActionSequenceTest.cpp
 *
 *   @brief  Tests for functions in DumpMem.cpp
 *
 ****************************************************************************/

// The files.mk file sets MOCK_MILLIS to test_millis for unittest purposes.

#include <gtest/gtest.h>

#include "TimedActionSequence.h"
#include "test_millis.h"
#include "Util.h"

//! Actions to test timed sequences
class TestClass {
 public:
    //! Action called as part of test sequence.
    void action() { this->action_called = true; }

    //! Action called as part of test sequence.
    void action2() { this->action2_called = true; }

    bool action_called = false;   //!< Set to true if action is called.
    bool action2_called = false;  //!< Set to true if action2 is called.
};

TEST(TimedActionSequenceTest, Continuous) {
    test_millis_count = 0;

    TestClass inst;

    TimedActionSequence::Action seq_list[] = {
        {std::bind(&TestClass::action, &inst), 3},
    };
    TimedActionSequence seq{seq_list, LEN(seq_list)};

    EXPECT_FALSE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(seq.is_continuous());
    EXPECT_FALSE(inst.action_called);

    test_millis_count++;
    seq.init();  // lastAction = 1

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(inst.action_called);

    test_millis_count++;
    seq.run();

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());

    test_millis_count++;
    seq.run();

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());

    test_millis_count++;
    seq.run();

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());
}

TEST(TimedActionSequenceTest, OneShot) {
    TestClass inst;

    TimedActionSequence::Action seq_list[] = {
        {std::bind(&TestClass::action, &inst), 2},
        {std::bind(&TestClass::action2, &inst), 2},
    };
    TimedActionSequence seq{seq_list, LEN(seq_list), TimedActionSequence::Mode::ONE_SHOT};

    EXPECT_FALSE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_FALSE(seq.is_continuous());
    EXPECT_FALSE(inst.action_called);
    EXPECT_FALSE(inst.action2_called);

    test_millis_count++;  // millis = 1

    seq.init();  // lastAction = 1 seq_idx = 0

    // One shot actions need to be started explicitly

    EXPECT_FALSE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_FALSE(inst.action_called);
    EXPECT_FALSE(inst.action2_called);

    test_millis_count++;  // millis = 2
    seq.run();            // Not started yet

    EXPECT_FALSE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_FALSE(inst.action_called);
    EXPECT_FALSE(inst.action2_called);

    test_millis_count++;  // millis = 3
    seq.start();          // Sequence started, seq_idx == 0

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(inst.action_called);
    EXPECT_FALSE(inst.action2_called);

    seq.start();  // Running start while it's running should do nothing

    test_millis_count++;  // millis = 4
    seq.run();            // Not enough time has passed yet

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(inst.action_called);
    EXPECT_FALSE(inst.action2_called);

    test_millis_count++;  // millis = 5
    seq.run();            // This should increment seq_idx to 1 so we're done

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(inst.action_called);
    EXPECT_TRUE(inst.action2_called);

    test_millis_count++;  // millis = 6
    seq.run();            // Still on seq_idx 1

    EXPECT_TRUE(seq.started());
    EXPECT_TRUE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(inst.action_called);
    EXPECT_TRUE(inst.action2_called);

    test_millis_count++;  // millis = 7
    seq.run();            // Should increment seq_idx = 2 so we're done

    EXPECT_TRUE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_TRUE(seq.done());
    EXPECT_TRUE(inst.action_called);
    EXPECT_TRUE(inst.action2_called);

    test_millis_count++;  // millis = 7\8
    seq.run();            // Should still be done

    EXPECT_TRUE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_TRUE(seq.done());
    EXPECT_TRUE(inst.action_called);
    EXPECT_TRUE(inst.action2_called);
}

TEST(TimedActionSequenceTest, NoInit) {
    TestClass inst;

    TimedActionSequence::Action seq_list[] = {
        {std::bind(&TestClass::action, &inst), 1},
    };
    TimedActionSequence seq{seq_list, LEN(seq_list)};

    EXPECT_FALSE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(seq.is_continuous());
    EXPECT_FALSE(inst.action_called);

    seq.run();

    EXPECT_FALSE(seq.started());
    EXPECT_FALSE(seq.running());
    EXPECT_FALSE(seq.done());
    EXPECT_TRUE(seq.is_continuous());
    EXPECT_FALSE(inst.action_called);
}
