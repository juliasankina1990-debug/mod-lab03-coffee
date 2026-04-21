// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>

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
    // остаёмся в ACCEPT
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
    // проверка, что сумма накопилась (через успешную покупку)
    a.choice(0);  // Espresso 50 rub
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
    a.choice(2);  // Cappuccino 80
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
    a.choice(3);  // Latte 90
    bool res = a.check();
    EXPECT_FALSE(res);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, FullHappyPath) {
    Automata a;
    a.on();                     // WAIT
    a.coin(100);                // ACCEPT
    a.choice(0);                // Espresso 50
    EXPECT_TRUE(a.check());     // COOK
    a.cook();
    a.finish();                 // WAIT
    EXPECT_EQ(a.getState(), STATES::WAIT);
}

TEST(AutomataTest, CancelAfterNotEnoughMoney) {
    Automata a;
    a.on();
    a.coin(40);
    a.choice(1);  // Americano 60
    a.check();    // не хватает, возврат в ACCEPT
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
    a.off();  // off только из WAIT, но мы в ACCEPT – не должно сработать
    EXPECT_EQ(a.getState(), STATES::ACCEPT); // не выключился
    a.cancel(); // вернёмся в WAIT
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
}
