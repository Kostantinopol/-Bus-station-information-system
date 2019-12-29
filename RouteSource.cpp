#include "pch.h"
#include "Route.h"
#include "Exceptions.h"
#include "DateTime.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int EnterOption(int, int);
int EnterNumber(istream&, int);

void Route::SetKeyId(int id) { this->KeyId = id; }
int Route::GetKeyId() { return this->KeyId; }
int Route::GetRouteId() { return this->routeId; }
void Route::SetRouteId(int id) { this->routeId = id; }

DateTime Route::GetShipTime() { return this->shipmentTime; }

void Route::Changing() {
	cout << " Что вы хотите изменить?\n";
	cout << " 1. Время отправки." << endl;
	cout << " 2. Время прибытия." << endl;
	cout << " 3. Цену." << endl;
	cout << " 4. Количество мест.\n>";
	switch (EnterOption(1, 4)) {
	case 1: {
		system("cls");
		DateTime newShipTime;
		cout << "Текущее время отправки: ";
		this->shipmentTime.Print(cout);
		cout << "\tТекущее время прибытия: ";
		this->arrivalTime.Print(cout);
		cout << " \nВведите новое время отправки: ";
		bool flag = true;
		while (flag) {
			flag = false;
			cin >> newShipTime;
			if (newShipTime > this->arrivalTime) {
				cin.clear();
				cout << " Отправка должна быть позже прибытия.\n Повторите попытку: ";
				flag = true;
			}
		}
		this->shipmentTime = newShipTime;
		this->duration = this->arrivalTime - this->shipmentTime;
		break;
	}
	case 2: {
		system("cls");
		DateTime newArrTime;
		cout << "Текущее время отправки: ";
		this->shipmentTime.Print(cout);
		cout << "\tТекущее время прибытия: ";
		this->arrivalTime.Print(cout);
		cout << " \nВведите новое время прибытия: ";
		bool flag = true;
		while (flag) {
			flag = false;
			cin >> newArrTime;
			if (this->shipmentTime > newArrTime) {
				cin.clear();
				cout << " Прибытие должно быть позже отправки.\n Повторите попытку: ";
				flag = true;
			}
		}
		this->arrivalTime = newArrTime;
		this->duration = this->arrivalTime - this->shipmentTime;
		break;
	}
	case 3: {
		system("cls");
		bool flag = true;
		cout << "Текущая цена: " << this->cost << "руб.\n";
		cout << "Новая цена: ";
		this->cost = EnterNumber(cin, 0);
		break;
	}
	case 4: {
		system("cls");
		cout << "Текущее число мест: " << this->seatsNumber << ".\n";
		cout << "Число мест: ";
		this->seatsNumber = EnterNumber(cin, 4);
		break;
	}
	}
}

void Route::Input(istream& in) {
	in >> this->KeyId;
	in.get();
	in >> this->routeId;
	shipmentTime.Input(in);
	in.get();
	duration.Input(in);
	in.get();
	arrivalTime.Input(in);
	in.get();
	in >> this->cost;
	in.get();
	in >> this->seatsNumber;
}

Route& Route::operator=(Route& obj) {
	this->KeyId = obj.KeyId;
	this->routeId = obj.routeId;
	this->shipmentTime = obj.shipmentTime;
	this->duration = obj.duration;
	this->arrivalTime = obj.arrivalTime;
	this->cost = obj.cost;
	this->seatsNumber = obj.seatsNumber;
	this->viza = obj.viza;
	return *this;
}

bool Route::operator==(Route& obj) {
	if (this->KeyId == obj.KeyId && this->routeId == obj.routeId && this->shipmentTime == obj.shipmentTime &&
		this->duration == obj.duration && this->arrivalTime == obj.arrivalTime && this->cost == obj.cost &&
		this->seatsNumber == obj.seatsNumber) return true;
	else return false;
}

ostream& Route::Record(ostream& out) {
	out << this->KeyId << " " << this->routeId << "\t";
	this->shipmentTime.Record(out);
	out << "\t";
	this->duration.Record(out);
	out << "\t";
	this->arrivalTime.Record(out);
	out << "\t" << this->cost << "\t" << this->seatsNumber;
	return out;
}

ostream& operator<<(ostream& out, Route& r) {
	//if (r.duration.GetDays() != 0 && r.duration.GetHours() == 0) out << " ";
	if(r.shipmentTime.GetHours() >= 10) out << "  " << r.shipmentTime << " |" << setw(5);
	else out << setw(8) << r.shipmentTime << " |" << setw(5);
	r.duration.Print(out);
	out << "|" << setw(6) << r.arrivalTime << " |" << setw(9) << r.cost << " |" << setw(14) << r.seatsNumber << " |";
	return out;
}

istream& operator>>(std::istream& in, Route& r) {
	cout << "Время отправления: \n";
	in >> r.shipmentTime;
	cout << "Время прибытия: \n";
	bool flag = true;
	while (flag) {
		in >> r.arrivalTime;
		if (r.shipmentTime > r.arrivalTime) {
			cout << "Брибытие должно быть позже отправки." << endl;
			in.clear();
			cout << "Повторите попытку: ";
		}
		else flag = false;
	}
	r.duration = r.arrivalTime - r.shipmentTime;
	cout << "Время в пути: " << r.duration << endl;
	cout << "Цена: ";
	in >> r.cost;
	cout << "Количество мест в автобусе: ";
	in >> r.seatsNumber;
	return in;
}
