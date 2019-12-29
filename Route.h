#pragma once
#include "pch.h"
#include "Exceptions.h"
#include "DateTime.h"
#include <iostream>
using namespace std;
int EnterOption(int, int);	//ввод целого числа в определенном диапазоне
int EnterNumber(istream&, int);	//1-дни, 2-часы, 3-минуты, 4-места в маршрутке, 5-места в автобусе
class Route {
protected:
	int KeyId;	//ключ-значение/индекс маршрута
	int routeId;	//индекс рейса
	DateTime shipmentTime;	//время отправки
	DateTime duration;	//длительность
	DateTime arrivalTime;	//место прибытия
	int cost;	//стоимость
	int seatsNumber;	//кол-во свободных мест
	bool viza;	//необъходимость визы
public:
	Route(bool viz = false) : KeyId(0), seatsNumber(0), routeId(0), cost(0),
		shipmentTime(), arrivalTime(), duration(), viza(viz) {}
	virtual ~Route() {}
	void SetKeyId(int);
	int GetKeyId();
	int GetRouteId();
	void SetRouteId(int);
	DateTime GetShipTime();
	virtual void Changing();	//изменение данных
	void Input(istream&);	//чтение из файла
	Route& operator=(Route&);
	bool operator==(Route&);
	ostream& Record(ostream&);	//запись в файл
	friend ostream& operator<<(ostream&, Route&);
	friend istream& operator>>(std::istream&, Route&);
};
