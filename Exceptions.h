#pragma once
#include "pch.h"
#include <iostream>
using namespace std;

class Exception {	
protected:
	int errorCode;
	Exception(int number) : errorCode(number) {}
public:
	virtual void What() = 0;
};

class BadInput : public Exception {	//��������� ������ ��� �����
public:
	BadInput(int number) : Exception(number) {}
	void What() override;
};

class BadFile : public Exception {	//��������� ������ � �����
public:
	BadFile(int number) : Exception(number) {}
	void What() override;
};