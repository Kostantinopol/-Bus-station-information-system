#include "pch.h"
#include "TeamStack.h"
#include <locale.h>
#include <Windows.h>
#include <iostream>
using namespace std;

int EnterOption(int, int);
void userMenu();
void adminMenu(TeamStack&);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	TeamStack teamStack;
	system("color F0");
	setlocale(LC_ALL, "");
	bool flag = true;
	while (flag) {
		system("cls");
		cout << "\tГлавное меню\n\n";
		cout << " 1. Просмотреть информацию о маршрутах.\n";
		cout << " 2. Изменить информацию о маршрутах.\n";
		cout << " 0. Выйти из программы.\n>";
		switch (EnterOption(0, 2)) {
		case 1:
			userMenu();
			break;
		case 2:
			adminMenu(teamStack);
			break;
		case 0:
			system("cls");
			flag = false;
			break;
		}
	}
	return 0;
}


