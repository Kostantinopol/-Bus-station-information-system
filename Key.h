#pragma once
#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
class Key {
private:
	int id;	//ключ-значение
	string name;	//название
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
	istream& Input(istream&);	//чтение из файла
	ostream& Record(ostream&);	//запись в файл
	friend ostream& operator<<(ostream&, Key&);
	friend istream& operator>>(istream&, Key&);
};