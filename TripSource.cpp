#include "pch.h"
#include "Trip.h"
#include "DateTime.h"
#include "Route.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void printTrait(int);

string Trip::GetReg() { return this->regularity; }

istream& Trip::Input(istream& in) {
	Route::Input(in);
	in.get();
	char str[10];
	in.getline(str, 10, '\n');
	this->regularity = string(str);
	return in;
}

ostream& Trip::Record(ostream& out) {
	Route::Record(out);
	out << '\t' << this->regularity << endl;
	return out;
}

Trip& Trip::operator=(Trip& obj) {
	dynamic_cast<Route&>(*this) = dynamic_cast<Route&>(obj);
	this->arrivalPoint = obj.arrivalPoint;
	this->regularity = obj.regularity;
	return *this;
}

bool Trip::operator==(Trip& obj) {
	if (dynamic_cast<Route&>(*this) == dynamic_cast<Route&>(obj)) return true;
	else return false;
}

void Trip::Changing() {
	cout << " 1. Изменить параметры маршрута.\n";
	cout << " 2. Изменить регулярность рейса.\n>";
	switch (EnterOption(1, 2)) {
	case 1:
		Route::Changing();
		break;
	case 2: {
		system("cls");
		cout << " Текущая регулярность: ";
		if (strcmp(this->regularity.c_str(), "по_будням")) cout << "по будням\n";
		else cout << this->regularity << endl;
		cout << " Новая регулярность рейса(по будням/выходные/ежедневно): ";
		char str[20];
		bool flag = true;
		while (flag) {
			flag = false;
			rewind(stdin);
			cin.getline(str, 20, '\n');
			if (strcmp(str, "по будням") != 0 && strcmp(str, "выходные") != 0 && strcmp(str, "ежедневно") != 0) {
				cin.clear();
				flag = true;
				cout << " Несоответствие требованиям. Выберите одну из трёх категорий: ";
			}
		}
		if (strcmp(str, "по будням") == 0) strcpy_s(str, "по_будням");
		this->regularity = string(str);
		break;
	}
	}
}

istream& operator>>(istream& in, Trip& obj) {
	in >> dynamic_cast<Route&>(obj);
	cout << "Введите регулярность рейса(по будням/выходные/ежедневно): ";
	bool flag = true;
	char str[20];
	while (flag) {
		flag = false;
		rewind(stdin);
		in.getline(str, 20, '\n');
		if (strcmp(str, "по будням") != 0 && strcmp(str, "выходные") != 0 && strcmp(str, "ежедневно") != 0) {
			in.clear();
			flag = true;
			cout << "Несоответствие требованиям. Выберите одну из трёх категорий: ";
		}
	}
	if (strcmp(str, "по будням") == 0) strcpy_s(str, "по_будням");
	obj.regularity = string(str);
	return in;
}

ostream& operator<<(ostream& out, Trip& obj) {
	out << dynamic_cast<Route&>(obj);
	if (obj.regularity == "по_будням") out << setw(14) << "по будням" << "|";
	else out << setw(14) << obj.regularity << "|";
	return out;
}