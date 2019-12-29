#pragma once
#include "pch.h"
#include "DateTime.h"
#include "Route.h"
#include <iostream>
#include <string>
using namespace std;
class Trip : public Route {
private:
	string arrivalPoint;	//����� ��������
	string regularity;	//�����������������
public:
	Trip(bool viz = false) : Route(viz), arrivalPoint(""), regularity("") {}
	virtual ~Trip() {}
	string GetReg();
	istream& Input(istream&);	//������ �� �����
	ostream& Record(ostream&);	//������ � ����
	Trip& operator=(Trip&);
	bool operator==(Trip&);
	virtual void Changing() override;	//��������� ������
	friend istream& operator>>(istream&, Trip&);
	friend ostream& operator<<(ostream&, Trip&);
};
