#pragma once
#include "pch.h"
#include "Key.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string EnterText(istream&, int, int);
void Key::SetKeyId(int newId) { this->id = newId; }
void Key::SetName(string newName) { this->name = newName; }
int Key::GetKeyId() { return this->id; }
string Key::GetName() { return this->name; }

Key& Key::operator=(Key& obj) {
	this->id = obj.id;
	this->name = obj.name;
	return *this;
}

bool Key::operator==(Key& obj) {
	if (this->id == obj.id && this->name == obj.name) return true;
	else return false;
}

istream& Key::Input(istream& in) {
	in >> this->id;
	in.get();
	getline(in, this->name);
	return in;
}

ostream& Key::Record(ostream& out) {
	out << this->id << " " << this->name << endl;
	return out;
}

ostream& operator<<(ostream& out, Key& city) {
	out << city.id << ". " << city.name;
	return out;
}

istream& operator>>(istream& in, Key& city) {
	city.id = 0;
	string name;
	name = EnterText(in, 1, 0);
	locale loc("rus");
	string::iterator it;
	for (it = name.begin(); it != name.end(); it++) {
		*it = use_facet<ctype<char>>(loc).tolower(*it);
	}
	it = name.begin();
	*it = use_facet<ctype<char>>(loc).toupper(*it);
	city.SetName(name);
	return in;
}