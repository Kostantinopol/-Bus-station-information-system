#pragma once
#include "pch.h"
#include "DateTime.h"
#include <iostream>
#include <iomanip>
using namespace std;

int EnterNumber(istream&, int);

int DateTime::GetDays() { return this->days; }

int DateTime::GetHours() { return this->hours; }

int DateTime::GetMinutes() { return this->minutes; }

void DateTime::Print(ostream& out) {
	if ((this->days == 0 && this->hours == 0 && this->minutes != 0) || (this->days != 0 && this->hours == 0 && this->minutes == 0)) out << "              ";
	if (this->days == 0 && this->hours != 0 && this->minutes != 0) out << "         ";
	if (this->days == 0 && this->hours != 0 && this->minutes == 0) out << "               ";
	if (this->days != 0 && this->hours == 0 && this->minutes != 0) out << "         ";
	if (this->days != 0) out << this->days << "дн. ";
	if (this->hours < 10 && this->hours != 0) out << " ";
	if (this->hours != 0) out << this->hours << "ч. ";
	if (this->minutes < 10 && this->minutes != 0) out << " ";
	if (this->minutes != 0) out << this->minutes << "мин.";
}

istream& DateTime::Input(istream& in) {
	in >> days;
	in.get();
	in >> hours;
	in.get();
	in >> minutes;
	return in;
}

ostream& DateTime::Record(ostream& out) {
	out << this->days << ":" << this->hours << ":" << this->minutes;
	return out;
}

bool DateTime::operator==(DateTime& obj) {
	if (this->days == obj.days && this->hours == obj.hours && this->minutes == obj.minutes) return true;
	else return false;
}

DateTime DateTime::operator=(DateTime obj) {
	this->days = obj.days;
	this->hours = obj.hours;
	this->minutes = obj.minutes;
	return *this;
}

bool DateTime::operator>(DateTime& obj) {
	if (this->hours > obj.hours) return true;
	if (this->hours == obj.hours) {
		if (this->minutes > obj.minutes) return true;
		else return false;
	}
	return false;
}

ostream& operator<<(ostream& out, DateTime& dt) {
	if (dt.days == 0) {
		if (dt.hours < 10) cout << "0" << dt.hours;
		else cout << setw(7) << dt.hours;
		cout << ":";
		if (dt.minutes < 10) cout << "0" << dt.minutes;
		else cout << dt.minutes;
	}
	else {
		cout << dt.days << "дн. " << dt.hours << "ч.";
	}
	return out;
}

istream& operator>>(istream& in, DateTime& dt) {
	dt.days = 0;
	cout << "Часов: ";
	dt.hours = EnterNumber(in, 2);
	cout << "Минут: ";
	dt.minutes = EnterNumber(in, 3);
	return in;
}

DateTime operator-(DateTime& dt1, DateTime& dt2) {
	int newMinutes, newHours = dt1.hours - dt2.hours;
	if (dt1.minutes >= dt2.minutes) newMinutes = dt1.minutes - dt2.minutes;
	else {
		newMinutes = 60 - (dt2.minutes - dt1.minutes);
	}
	return DateTime(newHours, newMinutes);
}
