#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <thread>
#include <stdlib.h>
#include <omp.h>

int winniePlace;

//Начальный вывод программы, показывающий значение случайно сгенерированных данных
void startProgramOutput(int length, int winnieThePooh) {
    std::cout << "Bees divided forest into " + std::to_string(length) + " sectors\n";
    std::cout << "Winnie the Pooh is on " + std::to_string(winnieThePooh) + " sector\n";
}

//Метод проверки одной стаей пчёл соответствующего сектора
void checkForestSector(std::vector<bool> forest, int beeChecker) {
    if (forest[beeChecker]) {
        std::cout << "BeeChecker #" + std::to_string(beeChecker) +
            " found Winnie The Pooh on his sector\n";
        winniePlace = beeChecker;
    }
    else {
        std::cout << "BeeChecker # " + std::to_string(beeChecker) + " didn't find anything on his sector\n";
    };
};

//Установка положения Винни-Пуха
std::vector<bool> placeWinnieThePooh(int length, int winnieThePooh) {
    std::vector<bool> forest(length);

    for (int i = 0; i < length; ++i) {
        if (i != winnieThePooh)
            forest[i] = false;
        else
            forest[i] = true;
    };
    return forest;
}



int main() {
    //Задаём случайные значения количеству секторов и положению Винни-Пуха
    std::srand(std::time(NULL));
    int length = std::rand() % 1000 + 1;
    int winnieThePooh = std::rand() % length;

    startProgramOutput(length, winnieThePooh);

    std::vector<bool> forest = placeWinnieThePooh(length, winnieThePooh);

    //Объявляем потоки и начинаем с ними работу
#pragma omp parallel for
        for (int i = 0; i < length; ++i) {
            checkForestSector(forest, i);
        }

    //Итоговый вывод программы
    std::cout << "Winnie The Pooh was found on sector " + std::to_string(winniePlace) +
        " and has been publically punished by the bees!\n";
    std::cout << "Tip: WinnieThePooh's position was randomly generated and he was at sector #" +
        std::to_string(winnieThePooh);

    return 0;
};