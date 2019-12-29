#include "pch.h"
#include "Exceptions.h"
#include <iostream>
using namespace std;

void BadInput::What() {
	cout << "Код ошибки: " << errorCode << ". ";
	switch (errorCode) {
	case -10:
		cout << "Нужно ввести число в определенном диапазоне.\n";
		break;
	case -11:
		cout << "Нужно ввести целое положительное число.\n";
		break;
	case -12:
		cout << "Чило не может превышать количествово дней в месяце.\n";
		break;
	case -13:
		cout << "Число не может превышать количество часов в сутках.\n";
		break;
	case -14:
		cout << "Число не может превышать количество минут в часу.\n";
		break;
	case -15:
		cout << " В маршрутке всего 25 мест.\n";
		break;
	case -16:
		cout << " В автобусе всего 40 мест.\n";
		break;
	case -17:
		cout << " рейсов не найдено.\n";
		break;

	case -20:
		cout << " Вы должны ввести текст без пробелов.\n";
		break;
	case -21:
		cout << " Используются только буквы русского алфавита.\n";
		break;
	case -25:
		cout << "Некорректный ввод.\n";
		break;
	case -27:
		cout << "Необходимо испоьзовать буквы русского алфавита.\n";
		break;
	case -28:
		cout << "Просмотр рейсов возможет толькло на декабрь 2019 г. и январь 2020 г.\n";
		break;
	case  -31:
		cout << "Ошибка со списком.\n";
		break;
	}
}

void BadFile::What() {
	cout << "Код ошибки: " << errorCode << ". ";
	switch (errorCode) {
	case -41:
		cout << "Файл пуст.\n";
		break;
	case -42:
		cout << "Ошибка при открытии файла.\n";
		break;
	}
}
