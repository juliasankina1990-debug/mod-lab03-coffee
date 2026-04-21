// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataTest, Dummy) {
    Automata a;
    EXPECT_EQ(a.getState(), STATES::OFF);
}
