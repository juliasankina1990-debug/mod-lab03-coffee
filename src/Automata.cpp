// Copyright 2022 UNN-IASR

#include "Automata.h"
#include <iostream>
#include <sstream>

Automata::Automata() : cash(0), state(STATES::OFF), selectedDrink(-1) {
    // Инициализация меню и цен
    menu = {"Espresso", "Americano", "Cappuccino", "Latte"};
    prices = {50, 60, 80, 90};
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        state = STATES::OFF;
        cash = 0;
        selectedDrink = -1;
    }
}

void Automata::coin(int money) {
    if (money <= 0) return;
    if (state == STATES::WAIT) {
        cash = money;
        state = STATES::ACCEPT;
    } else if (state == STATES::ACCEPT) {
        cash += money;
        // остаёмся в ACCEPT
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPT) {
        // возврат денег (имитация)
        cash = 0;
        state = STATES::WAIT;
        selectedDrink = -1;
    }
}

std::string Automata::getMenu() const {
    std::ostringstream oss;
    for (size_t i = 0; i < menu.size(); ++i) {
        oss << i+1 << ". " << menu[i] << " - " << prices[i] << " rub\n";
    }
    return oss.str();
}

STATES Automata::getState() const {
    return state;
}

void Automata::choice(int drinkIndex) {
    if (state == STATES::ACCEPT && drinkIndex >= 0 && drinkIndex < static_cast<int>(menu.size())) {
        selectedDrink = drinkIndex;
        state = STATES::CHECK;
    }
}

bool Automata::check() {
    if (state != STATES::CHECK) return false;
    if (selectedDrink >= 0 && cash >= prices[selectedDrink]) {
        state = STATES::COOK;
        return true;
    } else {
        // недостаточно денег – возврат в ACCEPT
        state = STATES::ACCEPT;
        return false;
    }
}

void Automata::cook() {
    if (state == STATES::COOK) {
        // имитация приготовления
        std::cout << "Приготовление " << menu[selectedDrink] << "...\n";
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        // выдача напитка и сдачи
        cash -= prices[selectedDrink];
        std::cout << "Заберите ваш " << menu[selectedDrink] << "!\n";
        if (cash > 0) {
            std::cout << "Ваша сдача: " << cash << " rub\n";
        }
        cash = 0;
        selectedDrink = -1;
        state = STATES::WAIT;
    }
}
