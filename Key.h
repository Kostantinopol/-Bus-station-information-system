#pragma once
#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
class Key {
private:
	int id;	//����-��������
	string name;	//��������
public:
	Key() : id(0), name("") {}
	Key(int i, string n) : id(i), name(n) {}
	~Key() {}
	void SetKeyId(int);
	void SetName(string);
	int GetKeyId();
	string GetName();
	Key& operator=(Key&);
	bool operator==(Key&);
	istream& Input(istream&);	//������ �� �����
	ostream& Record(ostream&);	//������ � ����
	friend ostream& operator<<(ostream&, Key&);
	friend istream& operator>>(istream&, Key&);
};