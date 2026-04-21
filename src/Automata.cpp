// Copyright 2022 UNN-IASR
#include "Automata.h"

Automata::Automata() : cash(0), state(STATES::OFF), selectedDrink(-1) {
    // инициализация меню (позже заполню)
}

void Automata::on() {
    // stub
}

void Automata::off() {
    // stub
}

void Automata::coin(int money) {
    // stub
}

std::string Automata::getMenu() const {
    return "";  // stub
}

STATES Automata::getState() const {
    return state;
}

void Automata::choice(int drinkIndex) {
    // stub
}

bool Automata::check() {
    return false;  // stub
}

void Automata::cancel() {
    // stub
}

void Automata::cook() {
    // stub
}

void Automata::finish() {
    // stub
}
