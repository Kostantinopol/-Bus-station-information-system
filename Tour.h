#pragma once
#include "pch.h"
#include "Excursion.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Tour : public Excursion {
private:
	vector<string> tourRoad;	//маршрут тура
public:
	Tour(bool viz = false) : Excursion(viz) {}
	virtual ~Tour() {}
	istream& Input(istream&);	//чтение из файла
	ostream& Record(ostream&);	//запись в файл
	virtual void Changing() override;	//изменение данных
	friend istream& operator>>(istream&, Tour&);
	friend ostream& operator<<(ostream&, Tour&);
};