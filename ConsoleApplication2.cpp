#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <thread>
#include <stdlib.h>
#include <omp.h>

int winniePlace = NULL;
int arrNumb;


//Начальный вывод программы, показывающий значение случайно сгенерированных данных
void startProgramOutput(int length, int winnieThePooh) {
	std::cout << "Bees divided forest into " + std::to_string(length) + " sectors\n";
	std::cout << "Winnie the Pooh is on " + std::to_string(winnieThePooh) + " sector\n";
}

//Метод проверки одной стаей пчёл соответствующего сектора
void checkForestSector(std::vector<bool> sector, int beeChecker, int i) {
	if (sector[beeChecker]) {
		std::cout << "BeeChecker Group #" + std::to_string(i + 1) +
			" found Winnie The Pooh on their sector\n";
		winniePlace = beeChecker;
		arrNumb = i;
	}
	else {
		std::cout << "BeeChecker Group # " + std::to_string(i + 1) + " didn't find anything on their sector \n";
	};
};

//Установка положения Винни-Пуха
std::vector<std::vector<bool>> placeWinnieThePooh(int length, int winnieThePooh, int threadsNumb) {
	std::vector<std::vector<bool>> forest(threadsNumb);
	int tempLength = length;
	int tempInt = 0;
	for (int j = 0; j < threadsNumb; j++) {
		if (j != threadsNumb - 1) {
			std::vector<bool> tempArr(length / threadsNumb);
			tempLength -= length / threadsNumb;
			forest[j] = tempArr;
		}
		else {
			std::vector<bool> tempArr(tempLength);
			tempLength -= tempLength;
			forest[j] = tempArr;
		}

		for (int i = 0; i < forest[j].size(); ++i) {
			if (i + tempInt != winnieThePooh)
				forest[j][i] = false;
			else
				forest[j][i] = true;
		};
		tempInt += forest[j].size();
	}

	return forest;
}



int main() {

	std::cout << "Enter amount of sectors: ";
	char str[100];

	std::cin >> str;

	//Есть смысл определить одну логическую переменную
	//чтобы знать, как закончился цикл

	//проверяем, является ли строка числом
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] < 48 || str[i]>57) { std::cout << "Incorrect input";  return NULL; }


	std::string inpStr(str);

	int length = std::stoi(inpStr);

	if (length < 1)
	{
		std::cout << "Incorrect input";
		return NULL;
	}


	std::cout << "Enter Winnie The Pooh's sector number (from 1 to sector's amount): ";
	char _str[100];

	std::cin >> _str;

	//Есть смысл определить одну логическую переменную
	//чтобы знать, как закончился цикл

	//проверяем, является ли строка числом
	for (int i = 0; _str[i] != '\0'; i++)
		if (_str[i] < 48 || _str[i]>57) { std::cout << "Incorrect input";  return NULL; }


	std::string _inpStr(_str);


	int winnieThePooh = std::stoi(_inpStr);

	if (winnieThePooh < 1 || winnieThePooh > length)
	{
		std::cout << "Incorrect input";
		return NULL;
	}




	std::cout << "Enter number of bee groups(from 1 to sector's number): ";
	char __str[100];

	std::cin >> __str;

	//Есть смысл определить одну логическую переменную
	//чтобы знать, как закончился цикл

	//проверяем, является ли строка числом
	for (int i = 0; __str[i] != '\0'; i++)
		if (__str[i] < 48 || __str[i]>57) { std::cout << "Incorrect input";  return NULL; }


	std::string __inpStr(__str);


	int threadsNumb = std::stoi(__inpStr);

	if (threadsNumb < 1 || threadsNumb > length)
	{
		std::cout << "Incorrect input";
		return NULL;
	}






	startProgramOutput(length, winnieThePooh);

	std::vector<std::vector<bool>> forest = placeWinnieThePooh(length, winnieThePooh - 1, threadsNumb);
	int temp = 0;
#pragma omp parallel for
	//Объявляем потоки и начинаем с ними работу
	for (int i = 0; i <= threadsNumb - 1; ++i) {
		for (int j = 0; j < forest[i].size(); j++) {
			checkForestSector(forest[i], j, i);
		}
	}

	//Итоговый вывод программы
	std::cout << "Winnie The Pooh was found on sector " + std::to_string(winniePlace + length / threadsNumb * arrNumb + 1) +
		" and has been publically punished by the bees!\n";
	std::cout << "Tip: WinnieThePooh's position was randomly generated and he was at sector #" +
		std::to_string(winnieThePooh);

	return 0;
};