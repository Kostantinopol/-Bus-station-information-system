#include "pch.h"
#include "Excursion.h"
#include "Route.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void printTrait(int);
void printCap(int);

void Excursion::SetTitle(string& newTitle) {
	this->title = newTitle;
}

istream& Excursion::Input(istream& in) {
	Route::Input(in);
	in.get();
	this->description.clear();
	char str[200];
	bool flag = true;
	while (flag) {
		in.getline(str, 200, '\n');
		if (strcmp(str, "---") == 0) {
			flag = false;
		}
		else this->description.push_back(string(str));
	}
	return in;
}

ostream& Excursion::Record(ostream& out) {
	Route::Record(out);
	out << '\n';
	vector<string>::iterator it = this->description.begin();
	while (it != this->description.end()) {
		out << (*it) << endl;
		++it;
	}
	out << "---" << endl;
	return out;
}

void Excursion::Changing() {
	system("cls");
	cout << " 1. Изменить параметры маршрута.\n";
	cout << " 2. Изменить описание экскурсии.\n>";
	switch (EnterOption(1, 2)) {
	case 1:
		Route::Changing();
		break;
	case 2: {
		system("cls");
		bool flag = true;
		string str;
		this->description.clear();
		cout << "Новое описание:\n";
		while (flag) {
			rewind(stdin);
			getline(cin, str, '\n');
			this->description.push_back(str);
			cout << "Продолжить ввод?(1 - да, 0 - нет) ";
			if (!EnterOption(0, 1)) flag = false;
		}
		break;
	}
	}
}

bool Excursion::operator==(Excursion& obj) {
	if (this->title == obj.title) return true;
	else return false;
}

istream& operator>>(istream& in, Excursion& obj) {
	in >> dynamic_cast<Route&>(obj);
	bool flag = true;
	cout << "Описание: \n";
	string str;
	while (flag) {
		rewind(stdin);
		getline(in, str, '\n');
		obj.description.push_back(string(str));
		cout << "Продолжить ввод?(1 - да, 0 - нет) ";
		if (!EnterOption(0, 1)) flag = false;
	}
	return in;
}

ostream& operator<<(ostream& out, Excursion& obj) {
	printCap(2);
	printTrait(2);
	out << dynamic_cast<Route&>(obj);
	cout << endl;
	printTrait(2);
	int number = 1;
	vector<string>::iterator it = obj.description.begin();
	cout << " Описание:\n";
	while (it != obj.description.end()) {
		cout << number++ << ") " << (*it) << endl;
		++it;
	}
	return out;
}