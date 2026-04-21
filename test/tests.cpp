// Copyright 2022 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include "Automata.h"

TEST(AutomataTest, InitialStateOff) {
    Automata a;
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(AutomataTest, TurnOn) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, TurnOffFromWait) {
    Automata a;
    a.on();
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(AutomataTest, CoinFromWaitGoesToAccept) {
    Automata a;
    a.on();
    a.coin(50);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, CoinFromAcceptAddsCash) {
    Automata a;
    a.on();
    a.coin(50);
    a.coin(30);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
    a.choice(0);
    EXPECT_TRUE(a.check());
}

TEST(AutomataTest, CancelFromAcceptReturnsToWait) {
    Automata a;
    a.on();
    a.coin(100);
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, ChoiceFromAcceptMovesToCheck) {
    Automata a;
    a.on();
    a.coin(80);
    a.choice(2);
    EXPECT_EQ(a.getState(), STATES::CHECK);
}

TEST(AutomataTest, CheckWithEnoughMoneyMovesToCook) {
    Automata a;
    a.on();
    a.coin(80);
    a.choice(2);
    bool res = a.check();
    EXPECT_TRUE(res);
    EXPECT_EQ(a.getState(), STATES::COOK);
}

TEST(AutomataTest, CheckWithNotEnoughMoneyStaysInAccept) {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(3);
    bool res = a.check();
    EXPECT_FALSE(res);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, FullHappyPath) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(0);
    EXPECT_TRUE(a.check());
    a.cook();
    a.finish();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, CancelAfterNotEnoughMoney) {
    Automata a;
    a.on();
    a.coin(40);
    a.choice(1);
    a.check();
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, GetMenuNotEmpty) {
    Automata a;
    std::string menu = a.getMenu();
    EXPECT_FALSE(menu.empty());
    EXPECT_NE(menu.find("Espresso"), std::string::npos);
}

TEST(AutomataTest, OffClearsCashAndSelection) {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(0);
    a.off();
    EXPECT_EQ(a.getState(), STATES::CHECK);
    EXPECT_TRUE(a.check());
    a.cook();
    a.finish();
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
}
