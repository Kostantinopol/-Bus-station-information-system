#pragma once
#include "pch.h"
#include "DateTime.h"
#include "Route.h"
#include <iostream>
#include <string>
using namespace std;
class Trip : public Route {
private:
	string arrivalPoint;	//место прибытия
	string regularity;	//продолжительность
public:
	Trip(bool viz = false) : Route(viz), arrivalPoint(""), regularity("") {}
	virtual ~Trip() {}
	string GetReg();
	istream& Input(istream&);	//чтение из файла
	ostream& Record(ostream&);	//запись в файл
	Trip& operator=(Trip&);
	bool operator==(Trip&);
	virtual void Changing() override;	//изменение данных
	friend istream& operator>>(istream&, Trip&);
	friend ostream& operator<<(ostream&, Trip&);
};
