// Copyright 2022 UNN-IASR
#include "Automata.h"
#include <iostream>

int main() {
    Automata machine;
    std::cout << "Автомат выключен. Включаем...\n";
    machine.on();
    std::cout << "Состояние: " << static_cast<int>(machine.getState()) << " (WAIT=1)\n";

    std::cout << "\nМеню:\n" << machine.getMenu();

    std::cout << "\nВносим 70 рублей...\n";
    machine.coin(70);
    std::cout << "Состояние: " << static_cast<int>(machine.getState()) << " (ACCEPT=2)\n";

    std::cout << "\nВыбираем напиток №2 (Americano, цена 60 руб)\n";
    machine.choice(1);  // индекс 1 = Americano
    std::cout << "Состояние: " << static_cast<int>(machine.getState()) << " (CHECK=3)\n";

    if (machine.check()) {
        std::cout << "Денег достаточно. Начинаем приготовление.\n";
        machine.cook();
        machine.finish();
    } else {
        std::cout << "Недостаточно средств.\n";
        machine.cancel();
    }

    std::cout << "\nФинальное состояние: " << static_cast<int>(machine.getState()) << " (WAIT=1)\n";
    return 0;
}
