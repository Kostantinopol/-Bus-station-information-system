#include "pch.h"
#include "Exceptions.h"
#include <iostream>
using namespace std;

void BadInput::What() {
	cout << "��� ������: " << errorCode << ". ";
	switch (errorCode) {
	case -10:
		cout << "����� ������ ����� � ������������ ���������.\n";
		break;
	case -11:
		cout << "����� ������ ����� ������������� �����.\n";
		break;
	case -12:
		cout << "���� �� ����� ��������� ������������ ���� � ������.\n";
		break;
	case -13:
		cout << "����� �� ����� ��������� ���������� ����� � ������.\n";
		break;
	case -14:
		cout << "����� �� ����� ��������� ���������� ����� � ����.\n";
		break;
	case -15:
		cout << " � ��������� ����� 25 ����.\n";
		break;
	case -16:
		cout << " � �������� ����� 40 ����.\n";
		break;
	case -17:
		cout << " ������ �� �������.\n";
		break;

	case -20:
		cout << " �� ������ ������ ����� ��� ��������.\n";
		break;
	case -21:
		cout << " ������������ ������ ����� �������� ��������.\n";
		break;
	case -25:
		cout << "������������ ����.\n";
		break;
	case -27:
		cout << "���������� ����������� ����� �������� ��������.\n";
		break;
	case -28:
		cout << "�������� ������ �������� ������� �� ������� 2019 �. � ������ 2020 �.\n";
		break;
	case  -31:
		cout << "������ �� �������.\n";
		break;
	}
}

void BadFile::What() {
	cout << "��� ������: " << errorCode << ". ";
	switch (errorCode) {
	case -41:
		cout << "���� ����.\n";
		break;
	case -42:
		cout << "������ ��� �������� �����.\n";
		break;
	}
}
