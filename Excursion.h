#pragma once
#include "pch.h"
#include "Route.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Excursion : public Route {
private:
	string title;	//��������
	vector<string> description;	//��������
public:
	Excursion(bool inter = false) : Route(inter), title("") {}
	virtual ~Excursion() {}
	void SetTitle(string&);
	istream& Input(istream&);	//������ �� �����
	ostream& Record(ostream&);	//������ � ����
	virtual void Changing();	//��������� ������
	bool operator==(Excursion&);
	friend istream& operator>>(istream&, Excursion&);
	friend ostream& operator<<(ostream&, Excursion&);
};
