#pragma once
#include "pch.h"
#include "Route.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Excursion : public Route {
private:
	string title;	//название
	vector<string> description;	//описание
public:
	Excursion(bool inter = false) : Route(inter), title("") {}
	virtual ~Excursion() {}
	void SetTitle(string&);
	istream& Input(istream&);	//чтение из файла
	ostream& Record(ostream&);	//запись в файл
	virtual void Changing();	//изменение данных
	bool operator==(Excursion&);
	friend istream& operator>>(istream&, Excursion&);
	friend ostream& operator<<(ostream&, Excursion&);
};
