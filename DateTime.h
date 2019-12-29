#pragma once
#include "pch.h"
#include <iostream>
#include <iomanip>
using namespace std;
class DateTime {
private:
	int days;	//дни
	int hours;	//часы
	int minutes;	//минуты
public:
	DateTime() : days(0), hours(0), minutes(0){}
	DateTime(int newHours, int newMinutes) : days(0), hours(newHours), minutes(newMinutes){}
	~DateTime(){}
	int GetDays();
	int GetHours();
	int GetMinutes();
	void Print(ostream&);
	istream& Input(istream&);	//чтение из файла
	ostream& Record(ostream&);	//запись в файл
	bool operator==(DateTime&);	
	DateTime operator=(DateTime);
	bool operator>(DateTime&);	//сравнение по времени
	friend ostream& operator<<(std::ostream&, DateTime&);
	friend istream& operator>>(istream&, DateTime&);
	friend DateTime operator-(DateTime&, DateTime&);	//вычисление длительности
};