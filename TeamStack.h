#pragma once
#include "pch.h"
#include <iostream>
#include "Route.h"
#include "Key.h"
#include "Trip.h"
#include <stack>
#include <memory>
#include <vector>
using namespace std;
struct TeamStack {
	stack<int> optionStack;	//���� �����
	stack<int> operationStack;	//���� ��������
	stack<Key> keyStack;	//���� �������� ��������
	stack<shared_ptr<Route>> objectStack;	//���� ��������
	vector<Trip> savedList;	//������ ��������� ������
};

//1 - ���������� �������
//11 - ���������� ������
//111 - ���������� �����
//2 - �������� �������
//22 - �������� ������(��������� �����)
//222 - �������� �����
//3 - ��������� �������
//33 - ��������� ������
//333 - ��������� �����