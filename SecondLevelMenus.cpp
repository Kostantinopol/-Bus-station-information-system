#include "pch.h"
#include "AdminsFeachures.h"
#include "Route.h"
#include "Trip.h"
#include "File.h"
#include "Route.h"
#include "Key.h"
#include "Excursion.h"
#include "Tour.h"
#include "List.h"
#include "TeamStack.h"
#include <iostream>
#include <string>
using namespace std;

void menuForTrips();
void menuForTours();
void menuForExcursions();
string EnterTripDate();
int selection();

string setType(int);

void menuForTrips() {
	system("cls");
	bool flag = true;
	while (flag) {
		cout << "\t�������� ��� �����:\n\n";
		cout << " 1. �������������.\n";
		cout << " 2. �������������.\n";
		cout << " 0. �����.\n>";
		int op = EnterOption(0, 2);
		if (op == 0) break;
		TextFile<Key> file(setType(op));
		system("cls");
		cout << "\t������� ������ �����(�����)\n\n";
		file.Print();
		cout << ">";
		int choize = EnterOption(1, file.GetLastKeyIndex());
		Key city = file.GetContentByIndex(choize);
		string date = EnterTripDate();
		TextFile<Trip> file_data(setType(op + 10));
		system("cls");
		cout << " �����-->" << city.GetName() << ", " << date << "." << endl;
		try {
			file_data.PrintByRequest(city.GetKeyId(), date);
		}
		catch (BadFile& obj) {
			obj.What();
		}
	}
}

void menuForExcursions() {
	system("cls");
	bool flag = true;
	int op = 3;
	while (flag) {
		cout << "\t��������� �� ��������:\n";
		TextFile<Key> file(setType(op));
		file.Print();
		cout << "0. �����.\n>";
		int choize = EnterOption(0, file.GetLastKeyIndex());
		if (!choize) return;
		Key exc = file.GetContentByIndex(choize);
		cout << exc.GetKeyId() << "   " << exc.GetName() << endl;
		TextFile<Excursion> file_data(setType(op + 10));
		system("cls");
		cout << " ���������: " << exc.GetName() << endl;
		file_data.PrintByIndex(exc.GetKeyId());
	}
}

void menuForTours() {
	system("cls");
	bool flag = true;
	while (flag) {
		cout << "\t�������� ��� ����:\n";
		cout << " 1. �� ��������.\n";
		cout << " 2. �����������.\n";
		cout << " 0. �����.\n>";
		int op = 3 + EnterOption(0, 2);
		if (op - 3 == 0) return;
		system("cls");
		TextFile<Key> file(setType(op));
		file.Print();
		int choize = EnterOption(0, file.GetLastKeyIndex());
		if (choize == 0) return;
		Key tour = file.GetContentByIndex(choize);
		TextFile<Tour> file_data(setType(op + 10));
		system("cls");
		cout << "���: " << tour.GetName() << endl;
		try {
			file_data.PrintByIndex(tour.GetKeyId());
		}
		catch (BadFile& obj) {
			obj.What();
		}
		
	}
}

void userMenu() {
	bool flag = true;
	while (flag) {
		system("cls");
		cout << "\t�������� ���������: \n\n";
		cout << " 1. ���������� �����.\n";
		cout << " 2. �������� ����.\n";
		cout << " 3. �������� ��������� �� ��������.\n";
		cout << " 0. ��������� � ������� ����.\n>";
		switch (EnterOption(0, 3)) {
		case 1:
			menuForTrips();
			break;
		case 2:
			menuForTours();
			break;
		case 3:
			menuForExcursions();
			break;
		case 0:
			flag = false;
			break;
		}
	}
}

void adminMenu(TeamStack& teamStack) {
	system("cls");
	//TeamStack teamStack;
	bool flag = true;
	while (flag) {
		cout << " 1. ��������.\n";
		cout << " 2. �������.\n";
		cout << " 3. �������������.\n";
		cout << " 4. �������� ��������� ��������.\n";
		cout << " 0. ��������� � ������� ����.\n>";
		switch (EnterOption(0, 4)) {
		case 1: {
			int option = selection();
			switch (option) {
			case 1:
			case 2:
				adding<Trip>(option, teamStack);
				break;
			case 3:
				adding<Excursion>(option, teamStack);
				break;
			case 4:
			case 5:
				adding<Tour>(option, teamStack);
				break;
			case 0:
				flag = false;
				break;
			}
			break;
		}
		case 2: {
			int option = selection();
			switch (option) {
			case 1:
			case 2:
				deletion<Trip>(option, teamStack);
				break;
			case 3:
				deletion<Excursion>(option, teamStack);
				break;
			case 4:
			case 5:
				deletion<Tour>(option, teamStack);
				break;
			}
			break;
		}
		case 3: {
			int option = selection();
			switch (option) {
			case 1:
			case 2:
				changing<Trip>(option, teamStack);
				break;
			case 3:
				changing<Excursion>(option, teamStack);
				break;
			case 4:
			case 5:
				changing<Tour>(option, teamStack);
				break;
			}
			break;
		}
		case 4:
			cancellation(teamStack);
			break;
		case 0:
			flag = false;
			break;
		}
	}
}