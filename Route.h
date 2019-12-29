#pragma once
#include "pch.h"
#include "Exceptions.h"
#include "DateTime.h"
#include <iostream>
using namespace std;
int EnterOption(int, int);	//���� ������ ����� � ������������ ���������
int EnterNumber(istream&, int);	//1-���, 2-����, 3-������, 4-����� � ���������, 5-����� � ��������
class Route {
protected:
	int KeyId;	//����-��������/������ ��������
	int routeId;	//������ �����
	DateTime shipmentTime;	//����� ��������
	DateTime duration;	//������������
	DateTime arrivalTime;	//����� ��������
	int cost;	//���������
	int seatsNumber;	//���-�� ��������� ����
	bool viza;	//�������������� ����
public:
	Route(bool viz = false) : KeyId(0), seatsNumber(0), routeId(0), cost(0),
		shipmentTime(), arrivalTime(), duration(), viza(viz) {}
	virtual ~Route() {}
	void SetKeyId(int);
	int GetKeyId();
	int GetRouteId();
	void SetRouteId(int);
	DateTime GetShipTime();
	virtual void Changing();	//��������� ������
	void Input(istream&);	//������ �� �����
	Route& operator=(Route&);
	bool operator==(Route&);
	ostream& Record(ostream&);	//������ � ����
	friend ostream& operator<<(ostream&, Route&);
	friend istream& operator>>(std::istream&, Route&);
};
