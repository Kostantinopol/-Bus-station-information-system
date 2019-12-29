#pragma once
#include "pch.h"
#include "Tour.h"
#include "Excursion.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

istream& Tour::Input(istream& in) {
	Excursion::Input(in);
	bool flag = true;
	char str[60];
	while (flag) {
		in.getline(str, 60, ',');
		if (strcmp(str, "---") == 0) {
			flag = false;
		}
		else this->tourRoad.push_back(string(str));
	}
	return in;
}

ostream& Tour::Record(ostream& out) {
	Excursion::Record(out);
	vector<string>::const_iterator it = this->tourRoad.begin();
	while (it != this->tourRoad.end()) {
		out << (*it) << ",";
		++it;
	}
	out << "---," << endl;
	return out;
}

void Tour::Changing() {
	system("cls");
	cout << " 1. Изменить параметры маршрута/описание.\n";
	cout << " 2. Изменить направление тура.\n>";
	switch (EnterOption(1, 2)) {
	case 1:
		Excursion::Changing();
		break;
	case 2: {
		system("cls");
		bool flag = true;
		char str[100];
		while (flag) {
			cin.getline(str, 100, '\n');
			this->tourRoad.push_back(string(str));
			cout << "Продолжить ввод?(1 - да, 0 - нет) ";
			if (!EnterOption(0, 1)) flag = false;
		}
	}
	}
}

istream& operator>>(istream& in, Tour& obj) {
	in >> dynamic_cast<Excursion&>(obj);
	bool flag = true;
	char str[100];
	cout << "Составьте маршрут: ";
	while (flag) {
		rewind(stdin);
		in.getline(str, 100, '\n');
		obj.tourRoad.push_back(string(str));
		cout << "Продолжить ввод?(1 - да, 0 - нет) ";
		if (!EnterOption(0, 1)) flag = false;
	}
	return in;
}

ostream& operator<<(ostream& out, Tour& obj) {
	out << dynamic_cast<Excursion&>(obj);
	vector<string>::const_iterator it = obj.tourRoad.begin();
	out << "\n Маршрут тура: Минск -> ";
	while (it != obj.tourRoad.end()) {
		out << *it << " -> ";
		++it;
	}
	out << "Минск\n";
	out << endl;
	return out;
}