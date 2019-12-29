#pragma once
#include "pch.h"
#include <iostream>
#include "Route.h"
#include "Key.h"
#include "Trip.h"
#include <stack>
#include <memory>
#include <vector>
using namespace std;
struct TeamStack {
	stack<int> optionStack;	//стек типов
	stack<int> operationStack;	//стек операций
	stack<Key> keyStack;	//стек ключевых значений
	stack<shared_ptr<Route>> objectStack;	//стек объектов
	vector<Trip> savedList;	//список удаленных рейсов
};

//1 - добавление объекта
//11 - добавление города
//111 - добавление рейса
//2 - удаление объекта
//22 - удаление города(удаляются рейсы)
//222 - удаление рейса
//3 - изменение объекта
//33 - изменение города
//333 - изменение рейса