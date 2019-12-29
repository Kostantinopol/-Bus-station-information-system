#pragma once
#include "pch.h"
#include "Excursion.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Tour : public Excursion {
private:
	vector<string> tourRoad;	//������� ����
public:
	Tour(bool viz = false) : Excursion(viz) {}
	virtual ~Tour() {}
	istream& Input(istream&);	//������ �� �����
	ostream& Record(ostream&);	//������ � ����
	virtual void Changing() override;	//��������� ������
	friend istream& operator>>(istream&, Tour&);
	friend ostream& operator<<(ostream&, Tour&);
};