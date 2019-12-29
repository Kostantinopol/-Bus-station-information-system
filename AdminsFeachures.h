#pragma once
#include "pch.h"
#include "Route.h"
#include "Trip.h"
#include "File.h"
#include "Route.h"
#include "Key.h"
#include "Excursion.h"
#include "Tour.h"
#include "List.h"
#include "TeamStack.h"
#include <locale.h>
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
using namespace std;


string EnterText(istream&, int, int);

template<class T> void adding(int option, TeamStack& teamStack) {
	system("cls");
	if (typeid(T) == typeid(Trip)) {
		cout << "\tЧто вы хотите добавить?\n";
		cout << " 1. Новый город.\n";
		cout << " 2. Новый рейс в конкретный город.\n>";
		switch (EnterOption(1, 2)) {
		case 1: {
			system("cls");
			TextFile<Key> file(setType(option));
			Key newCity;
			cout << "Город: ";
			cin >> newCity;
			if (file.Find(newCity)) cout << "Такой город уже записан.\n";
			else {
				newCity.SetKeyId(file.GetLastKeyIndex() + 1);
				file.RecordInFile(newCity);
				//file.Print();
				teamStack.operationStack.push(11); //операция добавления города
				teamStack.optionStack.push(option); //тип
				teamStack.keyStack.push(newCity); //ключевой объект
				List<Key, TextFile<Key>> list;
				try {
					list.FillFromFile(file);
				}
				catch (BadFile& obj) {
					obj.What();
					return;
				}
				//list.Print();
				list.WriteToFile(file, option);
				cout << "Добавлен новый город.\n";
			}
			break;
		}
		case 2: {
			system("cls");
			Trip newTrip;
			TextFile<Key> file(setType(option));
			file.Print();
			cout << "Город(номер): ";
			newTrip.SetKeyId(EnterOption(1, file.GetLastKeyIndex()));
			TextFile<Trip> file_data(setType(option + 10));
			cout << "Новый рейс:\n";
			cin >> newTrip;
			teamStack.operationStack.push(111);
			teamStack.optionStack.push(option);
			teamStack.objectStack.push(make_shared<Trip>(newTrip));
			List<Trip, TextFile<Trip>> list;
			//list.FillFromFile(file_data);
			list.TripsInsertion(file_data, newTrip, true);
			list.Sort1();
			//list.Print();
			list.WriteToFile(file_data, option + 10);
			cout << "Добавлен новый рейс." << endl;
			break;
		}
		}
	}
	else {
		TextFile<Key> file(setType(option));
		Key newObjKey;
		string newObjName;
		if (typeid(T) == typeid(Excursion)) cout << "Название новой экскурсии: ";
		if (typeid(T) == typeid(Tour)) cout << "Название нового тура: ";
		newObjKey.SetName(EnterText(cin, 2, 0));
		int max = file.GetLastKeyIndex();
		if (file.Find(newObjKey)) {
			if (typeid(T) == typeid(Excursion)) cout << "Такая экскурсия уже записана.\n";
			if (typeid(T) == typeid(Tour)) cout << "Такой тур уже записан.\n";
			return;
		}
		else {
			newObjKey.SetKeyId(max + 1);
			file.RecordInFile(newObjKey);
			teamStack.operationStack.push(1);
			teamStack.optionStack.push(option);
			teamStack.keyStack.push(newObjKey);
		}
		T newObj;
		newObj.SetKeyId(max + 1);
		TextFile<T> file_data(setType(option + 10));
		cin >> newObj;
		List<T, TextFile<T>> list_data;
		list_data.FillFromFile(file_data);
		list_data.Add(newObj);
		T newObj_null(false);
		list_data.Add(newObj_null);
		list_data.WriteToFile(file_data, option + 10);
		if (typeid(T) == typeid(Excursion)) cout << "Добавлена новая экскурсия.\n";
		if (typeid(T) == typeid(Tour)) cout << "Добавлен новый тур.\n";
	}
}

template<class T> void deletion(int option, TeamStack& teamStack) {
	system("cls");
	if (typeid(T) == typeid(Trip)) {
		cout << "\tЧто вы хотите удалить?\n";
		cout << " 1. Город.\n";
		cout << " 2. Рейс в конкретный город.\n";
		cout << " 0. Назад.\n>";
		switch (EnterOption(0, 2)) {
		case 1: {
			system("cls");
			TextFile<Key> file(setType(option));
			file.Print();
			cout << "Выберите город: ";
			int choize = EnterOption(1, file.GetLastKeyIndex());
			Key city = file.GetContentByIndex(choize);
			List<Key, TextFile<Key>> list;
			list.FillFromFile(file);
			
			list.Print();
			list.Delete(city);

			teamStack.operationStack.push(2);
			teamStack.optionStack.push(option);
			teamStack.keyStack.push(city);

			TextFile<Trip> file_data(setType(option + 10));
			List<Trip, TextFile<Trip>> list_data;
			list_data.FillFromFile(file_data);
			List<Trip, TextFile<Trip>>::Iterator it1 = list_data.begin();
			teamStack.savedList.clear();
			while (it1 != nullptr) {
				if ((*it1).GetKeyId() == choize) {
					while ((*it1).GetKeyId() == choize) {
						teamStack.savedList.push_back(*it1);
						list_data.Delete(*it1);
						++it1;
					}
					break;
				}
				else ++it1;
			}
			list.Indexing();
			it1 = list_data.begin();
			if ((*it1).GetKeyId() != 1) {
				int index;
				while (it1 != NULL) {
					index = (*it1).GetKeyId() - 1;
					(*it1).SetKeyId(index);
					++it1;
				}
			}
			else {
				int index, prev = (*it1).GetKeyId();
				++it1;
				while (it1 != NULL) {
					if ((*it1).GetKeyId() - prev == 2) {
						while (it1 != NULL) {
							index = (*it1).GetKeyId();
							(*it1).SetKeyId(index - 1);
							++it1;
						}
						break;
					}
					else {
						prev = (*it1).GetKeyId();
						++it1;
					}
				}
			}
			list_data.WriteToFile(file_data, option + 10);
			list.WriteToFile(file, option);
			break;
		}
		case 2: {
			system("cls");
			TextFile<Key> file(setType(option));
			file.Print();
			cout << "Выберите город: ";
			int choize = EnterOption(1, file.GetLastKeyIndex());
			TextFile<Trip> file_data(setType(option + 10));
			List<Trip, TextFile<Trip>> list_data;
			list_data.FillFromFile(file_data);
			List<Trip, TextFile<Trip>>::Iterator it = list_data.begin();
			int numberOfTrips = 0;
			bool flag = false;
			int number = 1;
			while (it != NULL) {
				if ((*it).GetKeyId() == choize) {
					numberOfTrips++;
					if (!flag) {
						printCap(1);
						printTrait(1);
					}
					flag = true;
					cout << setw(6) << number++ << " |" << (*it) << endl;
					printTrait(1);
				}
				++it;
			}
			if (!numberOfTrips) {
				cout << "Нужных вам рейсов нет.\n";
			}
			else {
				cout << "Рейс(номер): ";
				int neededId = EnterOption(1, numberOfTrips);
				it = list_data.begin();
				while (it != NULL) {
					if ((*it).GetRouteId() == neededId) {
						list_data.Delete(*it);
						break;
					}
					++it;
				}
				it = list_data.begin();
				int index;
				while (it != NULL) {
					if ((*it).GetKeyId() == choize && (*it).GetRouteId() == neededId + 1) {
						while ((*it).GetKeyId() == choize && it != nullptr) {
							index = (*it).GetRouteId();
							(*it).SetRouteId(index - 1);
							++it;
						}
					}
					else ++it;
				}
			}
			list_data.WriteToFile(file_data, option + 10);
			cout << "\nРейс удалён.\n";
			break;
		}
		}
	}
	if (typeid(T) == typeid(Excursion) || typeid(T) == typeid(Tour)) {
		TextFile<Key> file(setType(option));
		file.Print();
		if (typeid(T) == typeid(Excursion)) cout << " Выберите экскурсию: \n";
		if (typeid(T) == typeid(Tour)) cout << " Выберите тур: \n";
		int choize = EnterOption(1, file.GetLastKeyIndex());
		List<Key, TextFile<Key>> list;
		list.FillFromFile(file);
		List<Key, TextFile<Key>>::Iterator it = list.begin();
		teamStack.operationStack.push(2);
		teamStack.optionStack.push(option);
		while (it != NULL) {
			if ((*it).GetKeyId() == choize) {
				teamStack.keyStack.push(*it);
				list.Delete(*it);
				break;
			}
			++it;
		}
		list.Indexing();
		list.Print();
		list.WriteToFile(file, option);
		TextFile<T> file_data(setType(option + 10));
		List<T, TextFile<T>> list_data;
		list_data.FillFromFile(file_data);
		typename List<T, TextFile<T>>::Iterator it1 = list_data.begin();
		while (it1 != nullptr) {
			if ((*it1).GetKeyId() == choize) {
				teamStack.optionStack.push(option);
				teamStack.objectStack.push(make_shared<T>(*it1));
				list_data.Delete(*it1);
				break;
			}
			++it1;
		}
		list_data.Indexing();
		T obj_null(false);
		list_data.Add(obj_null);
		cout << "Новый список:\n";
		list_data.Print();
		list_data.WriteToFile(file_data, option + 10);
		if (typeid(T) == typeid(Excursion)) cout << " Экскурсия удалена.\n";
		if (typeid(T) == typeid(Tour)) cout << " Тур удален.\n";
	}

}

template<class T> void changing(int option, TeamStack& teamStack) {
	system("cls");
	if (typeid(T) == typeid(Trip)) {
		cout << "\tЧто вы хотите изменить?\n";
		cout << " 1. Город.\n";
		cout << " 2. Рейс в конкретный город.\n";
		switch (EnterOption(1, 2)) {
		case 1: {
			system("cls");
			TextFile<Key> file(setType(option));
			file.Print();
			cout << "Город(номер): ";
			int choize = EnterOption(1, file.GetLastKeyIndex());
			List<Key, TextFile<Key>> list;
			list.FillFromFile(file);
			Key newCity;
			List<Key, TextFile<Key>>::Iterator it = list.begin(), temp;
			while (it != nullptr) {
				if ((*it).GetKeyId() == choize) {
					bool flag = true;
					cout << "Заменить город " << (*it).GetName() << " на: ";
					while (flag) {
						flag = false;
						rewind(stdin);
						cin >> newCity;
						temp = list.begin();
						while (temp != nullptr) {
							if ((*temp).GetName() == newCity.GetName()) {
								cout << "Такой город уже записан.\n";
								cout << "Введите новый город: ";
								flag = true;
								break;
							}
							++temp;
						}
					}
					newCity.SetKeyId((*it).GetKeyId());
					teamStack.keyStack.push((*it));
					(*it) = newCity;
					cout << newCity << endl;
					teamStack.operationStack.push(33);
					teamStack.optionStack.push(option);
				}
				++it;
			}
			list.WriteToFile(file, option);
			cout << "Город заменён.\n";
			break;
		}
		case 2: {
			system("cls");
			TextFile<Key> file(setType(option));
			file.Print();
			cout << "Город(номер): ";
			int choize = EnterOption(1, file.GetLastKeyIndex());
			TextFile<T> file_data(setType(option + 10));
			List<T, TextFile<T>> list_data;
			list_data.FillFromFile(file_data);
			typename List<T, TextFile<T>>::Iterator it = list_data.begin();
			int numberOfTrips = 0;
			printCap(1);
			printTrait(1);
			int number = 1;
			while (it != nullptr) {
				if ((*it).GetKeyId() == choize) {
					cout << setw(6) << number++ << " |" << (*it) << endl;
					printTrait(1);
					numberOfTrips++;
				}
				++it;
			}
			if (!numberOfTrips) cout << "Нужных вам рейсов нет.\n";
			else {
				cout << "Рейс(номер): ";
				int neededId = EnterOption(1, numberOfTrips);
				it = list_data.begin();
				while (it != nullptr) {
					if ((*it).GetKeyId() == choize && (*it).GetRouteId() == neededId) {
						teamStack.operationStack.push(333);
						teamStack.optionStack.push(option);
						teamStack.objectStack.push(make_shared<T>((*it)));
						(*it).Changing();
					}
					++it;
				}
				cout << " Рейс изменён.\n";
				list_data.WriteToFile(file_data, option + 10);
			}
			break;
		}
		}
	}
	else {
		TextFile<Key> file(setType(option));
		if (typeid(T) == typeid(Excursion)) cout << "Выберите экскурсию: \n";
		if (typeid(T) == typeid(Tour)) cout << "Выберите тур: \n";
		file.Print();
		cout << "0. Назад.\n>";
		int choize = EnterOption(0, file.GetLastKeyIndex());
		if (!choize) return;
		cout << " Что вы хотите изменить?\n";
		if (typeid(T) == typeid(Excursion)) {
			cout << " 1. Название экскурсии.\n";
			cout << " 2. Характеристику экскурсии.\n";
		}
		if (typeid(T) == typeid(Tour)) {
			cout << " 1. Название тура.\n";
			cout << " 2. Характеристику тура.\n";
		}
		switch (EnterOption(1, 2)) {
		case 1: {
			string newName;
			List<Key, TextFile<Key>> list;
			list.FillFromFile(file);
			typename List<Key, TextFile<Key>>::Iterator it = list.begin(), temp;
			while (it != nullptr) {
				if ((*it).GetKeyId() == choize) {
					bool flag = true;
					cout << "Новое название: ";
					while (flag) {
						flag = false;
						newName = EnterText(cin, 2, 0);
						temp = list.begin();
						while (temp != nullptr) {
							if ((*temp).GetName() == newName) {
								cout << "Такая экскурсия уже записана.\n";
								cout << "Введите новую: ";
								flag = true;
								break;
							}
							++temp;
						}
					}
					teamStack.keyStack.push((*it));
					teamStack.operationStack.push(33);
					teamStack.optionStack.push(option);
					(*it).SetName(newName);
					break;
				}
				++it;
			}
			list.WriteToFile(file, option);
			cout << "Название изменено.\n";
			break;
		}
		case 2: {
			TextFile<T> file_data(setType(option + 10));
			List<T, TextFile<T>> list_data;
			list_data.FillFromFile(file_data);
			typename List<T, TextFile<T>>::Iterator it = list_data.begin();
			teamStack.operationStack.push(333);
			teamStack.optionStack.push(option);
			while (it != nullptr) {
				if ((*it).GetKeyId() == choize) {
					teamStack.objectStack.push(make_shared<T>(*it));
					(*it).Changing();
					break;
				}
				++it;
			}
			T obj_null(false);
			list_data.Add(obj_null);
			list_data.WriteToFile(file_data, option + 10);
			break;
		}
		}
	}
}

void cancellation(TeamStack& teamStack) {
	int topOperation = teamStack.operationStack.top();
	if (topOperation == 11) {
		int topOption = teamStack.optionStack.top();
		if (topOption == 1 || topOption == 2) {
			TextFile<Key> file(setType(topOption));
			List<Key, TextFile<Key>> list;
			list.FillFromFile(file);
			Key city = dynamic_cast<Key&>(teamStack.keyStack.top());
			list.Delete(city);
			TextFile<Trip> file_data(setType(topOption + 10));
			List<Trip, TextFile<Trip>> list_data;
			list_data.FillFromFile(file_data);
			List<Trip, TextFile<Trip>>::Iterator it1 = list_data.begin();
			while (it1 != NULL) {
				if ((*it1).GetKeyId() == city.GetKeyId()) {
					list_data.Delete(*it1);
				}
				++it1;
			}
			list.Indexing();
			it1 = list_data.begin();
			if ((*it1).GetKeyId() != 1) {
				int index;
				while (it1 != NULL) {
					index = (*it1).GetKeyId() - 1;
					(*it1).SetKeyId(index);
					++it1;
				}
			}
			else {
				int index, prev = (*it1).GetKeyId();
				++it1;
				while (it1 != NULL) {
					if ((*it1).GetKeyId() - prev == 2) {
						while (it1 != NULL) {
							index = (*it1).GetKeyId();
							(*it1).SetKeyId(index - 1);
							++it1;
						}
						break;
					}
					else {
						prev = (*it1).GetKeyId();
						++it1;
					}
				}
			}
			list_data.WriteToFile(file_data, topOption + 10);
			list.WriteToFile(file, topOption);
			teamStack.keyStack.pop();
			cout << " Действие отменено.\n";
		}
		if (topOption == 3) {
			TextFile<Key> file(setType(topOption));
			List<Key, TextFile<Key>> list;
			list.FillFromFile(file);
			Key exc = dynamic_cast<Key&>(teamStack.keyStack.top());
			List<Key, TextFile<Key>>::Iterator it = list.begin();
			while (it != NULL) {
				if ((*it).GetKeyId() == exc.GetKeyId()) list.Delete(*it);
				++it;
			}
			list.Indexing();
			list.WriteToFile(file, topOption);
			TextFile<Excursion> file_data(setType(topOption + 10));
			List<Excursion, TextFile<Excursion>> list_data;
			list_data.FillFromFile(file_data);
			typename List<Excursion, TextFile<Excursion>>::Iterator it1 = list_data.begin();
			while (it1 != nullptr) {
				if ((*it1).GetKeyId() == exc.GetKeyId()) {
					list_data.Delete(*it1);
					break;
				}
				++it1;
			}
			list_data.Print();
			list_data.Indexing();

			Excursion exc_null(false);
			list_data.Add(exc_null);
			list_data.WriteToFile(file_data, topOption + 10);
			teamStack.keyStack.pop();
		}
		if (topOption == 4 || topOption == 5) {
			TextFile<Key> file(setType(topOption));
			Key tour = dynamic_cast<Key&>(teamStack.keyStack.top());
			List<Key, TextFile<Key>> list;
			list.FillFromFile(file);
			List<Key, TextFile<Key>>::Iterator it = list.begin();
			while (it != NULL) {
				if ((*it).GetKeyId() == tour.GetKeyId()) list.Delete(*it);
				++it;
			}
			list.Indexing();
			list.Print();
			list.WriteToFile(file, topOption + 10);
			TextFile<Tour> file_data(setType(topOption + 10));
			List<Tour, TextFile<Tour>> list_data;
			list_data.FillFromFile(file_data);
			typename List<Tour, TextFile<Tour>>::Iterator it1 = list_data.begin();
			while (it1 != nullptr) {
				if ((*it1).GetKeyId() == tour.GetKeyId()) {
					list_data.Delete(*it1);
					cout << "\n---delete---\n";
				}
				++it1;
			}
			list_data.Indexing();
			Tour obj_null(false);
			list_data.Add(obj_null);
			cout << "Новый список:\n";
			list_data.Print();
			list_data.WriteToFile(file_data, topOption + 10);
			teamStack.keyStack.pop();
		}
		teamStack.optionStack.pop();
	}
	if (topOperation == 111) {
		int topOption = teamStack.optionStack.top();
		TextFile<Trip> file_data(setType(topOption + 10));
		Trip addedTrip = dynamic_cast<Trip&>(*(teamStack.objectStack.top()));
		List<Trip, TextFile<Trip>> list_data;
		list_data.FillFromFile(file_data);
		list_data.Delete(addedTrip);
		list_data.Sort1();
		list_data.WriteToFile(file_data, topOption + 10);
		teamStack.objectStack.pop();
		teamStack.optionStack.pop();
		cout << "Действие отменено.\n";
	}

	if (topOperation == 2) {
		int topOption = teamStack.optionStack.top();
		if (topOption == 1 || topOption == 2) {
			TextFile<Key> file(setType(topOption));
			Key deletedCity = dynamic_cast<Key&>(teamStack.keyStack.top());
			deletedCity.SetKeyId(file.GetLastKeyIndex() + 1);
			file.RecordInFile(deletedCity);
			TextFile<Trip> file_data(setType(topOption + 10));
			List<Trip, TextFile<Trip>> list_data;
			list_data.FillFromFile(file_data);
			vector<Trip>::iterator it = teamStack.savedList.begin();
			int newIndex = deletedCity.GetKeyId();
			while (it != teamStack.savedList.end()) {
				(*it).SetKeyId(newIndex);
				list_data.Add(*it);
				++it;
			}
			teamStack.savedList.clear();
			teamStack.keyStack.pop();
		}
		if (topOption == 3) {
			TextFile<Key> file(setType(topOption));
			Key deletedExcKey = dynamic_cast<Key&>(teamStack.keyStack.top());
			int newIndex = file.GetLastKeyIndex() + 1;
			deletedExcKey.SetKeyId(newIndex);
			file.RecordInFile(deletedExcKey);

			Excursion deletedExcObj = dynamic_cast<Excursion&>(*(teamStack.objectStack.top()));
			deletedExcObj.SetKeyId(newIndex);
			TextFile<Excursion> file_data(setType(topOption + 10));
			List<Excursion, TextFile<Excursion>> list_data;
			list_data.FillFromFile(file_data);
			list_data.Add(deletedExcObj);
			Excursion newExc_null(false);
			list_data.Add(newExc_null);
			list_data.WriteToFile(file_data, topOption + 10);
			teamStack.keyStack.pop();
			teamStack.objectStack.pop();
		}
		if (topOption == 4 || topOption == 5) {
			TextFile<Key> file(setType(topOption));
			Key deletedTourKey = dynamic_cast<Key&>(teamStack.keyStack.top());
			int newIndex = file.GetLastKeyIndex() + 1;
			deletedTourKey.SetKeyId(newIndex);
			file.RecordInFile(deletedTourKey);

			Tour deletedTourObj = dynamic_cast<Tour&>(*(teamStack.objectStack.top()));
			deletedTourObj.SetKeyId(newIndex);
			TextFile<Tour> file_data(setType(topOption + 10));
			List<Tour, TextFile<Tour>> list_data;
			list_data.FillFromFile(file_data);
			list_data.Add(deletedTourObj);
			Tour newTour_null(false);
			list_data.Add(newTour_null);
			list_data.WriteToFile(file_data, topOption + 10);
			teamStack.keyStack.pop();
			teamStack.objectStack.pop();
		}
		teamStack.optionStack.pop();
	}
	if (topOperation == 33) {
		int topOption = teamStack.optionStack.top();
		TextFile<Key> file(setType(topOption));
		Key changedCity = dynamic_cast<Key&>(teamStack.keyStack.top());
		List<Key, TextFile<Key>> list;
		list.FillFromFile(file);
		typename List<Key, TextFile<Key>>::Iterator it = list.begin();
		while (it != nullptr) {
			if ((*it).GetKeyId() == changedCity.GetKeyId()) {
				(*it) = changedCity;
				break;
			}
			++it;
		}
		list.WriteToFile(file, topOption);
		teamStack.keyStack.pop();
		teamStack.optionStack.pop();
		cout << "Действие отменено.\n";
	}
	if (topOperation == 333) {
		int topOption = teamStack.optionStack.top();
		if (topOperation == 1 || topOperation == 2){
			TextFile<Trip> file_data(setType(topOption + 10));
			Trip changedObj = dynamic_cast<Trip&>(*(teamStack.objectStack.top()));
			List<Trip, TextFile<Trip>> list_data;
			list_data.FillFromFile(file_data);
			typename List<Trip, TextFile<Trip>>::Iterator it = list_data.begin();
			while (it != nullptr) {
				if ((*it).GetKeyId() == changedObj.GetKeyId()) {
					(*it) = changedObj;
					break;
				}
				++it;
			}
			list_data.WriteToFile(file_data, topOption + 10);
		}
		if (topOperation == 3) {
			TextFile<Excursion> file_data(setType(topOption + 10));
			Excursion changedObj = dynamic_cast<Excursion&>(*(teamStack.objectStack.top()));
			List<Excursion, TextFile<Excursion>> list_data;
			list_data.FillFromFile(file_data);
			typename List<Excursion, TextFile<Excursion>>::Iterator it = list_data.begin();
			while (it != nullptr) {
				if ((*it).GetKeyId() == changedObj.GetKeyId()) {
					(*it) = changedObj;
					break;
				}
				++it;
			}
			list_data.WriteToFile(file_data, topOption + 10);
		}
		if (topOperation == 4 || topOperation == 5) {
			TextFile<Tour> file_data(setType(topOption + 10));
			Tour changedObj = dynamic_cast<Tour&>(*(teamStack.objectStack.top()));
			List<Tour, TextFile<Tour>> list_data;
			list_data.FillFromFile(file_data);
			typename List<Tour, TextFile<Tour>>::Iterator it = list_data.begin();
			while (it != nullptr) {
				if ((*it).GetKeyId() == changedObj.GetKeyId()) {
					(*it) = changedObj;
					break;
				}
				++it;
			}
			list_data.WriteToFile(file_data, topOption + 10);
		}
		teamStack.optionStack.pop();
		teamStack.objectStack.pop();
		cout << "Действие отменено.\n";
	}
	teamStack.operationStack.pop();
}