#include "pch.h"
#include "Exceptions.h"
#include "File.h"
#include "Key.h"
#include <iostream>
#include <iomanip>
using namespace std;

void printCap(int op) {// 1 - рейс, 2 - тур/экскурсия
	if (op == 1) {
		cout << "_________________________________________________________________________________________________" << endl;
		cout << setw(7) << "Номер" << "|" << setw(13) << "Отправление" << "|" << setw(20) << "В пути" << "|" << setw(11) << 
			"Прибытие" << "|" << setw(10) << "Стоимость" << "|" << setw(12) << "Количество мест" << 
			"|" << setw(14) << "Регулярность" << "|" << endl;
	}
	if (op == 2) {
		cout << "__________________________________________________________________________" << endl;
		cout << setw(13) << "Отправление" << "|" << setw(20) << "В пути" << "|" << setw(11) <<
			"Прибытие" << "|" << setw(10) << "Стоимость" << "|" << setw(15) << "Количество мест" << "|" << endl;
	}
}

void printTrait(int op) {
	if (op == 1) {
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
	if (op == 2) {
		cout << "--------------------------------------------------------------------------" << endl;
	}
}

int EnterOption(int min, int max) {
	int op;
	while (true) {
		try {
			if (!(cin >> op)) throw BadInput(-11);
			int sum = 0;
			for (int i = min; i <= max; i++) {
				if (op != i) sum++;
			}
			if (sum == max - min + 1) throw BadInput(-10);
			return op;
		}
		catch (BadInput& obj) {
			obj.What();
			cin.clear();
			rewind(stdin);
			cout << "Повторите попытку: ";
		}
	}
}

string EnterText(istream& in, int op, int var) {  //op = 1 - без пробелов, op = 2 - с пробелами, var = 1 - для месяца	
	string text;								 
	bool flag = true;
	while (flag) {
		flag = false;
		rewind(stdin);
		getline(in, text, '\n');
		try {
			for (int i = 0; i < text.size(); i++) {
				if ((text[i] > 'b' && text[i] < 'z') || (text[i] > 'A' && text[i] < 'Z')) throw BadInput(-21);
				if (op == 1) {
					if ((text[i] < 'а' || text[i] > 'я') && (text[i] < 'А' || text[i] > 'Я')) throw BadInput(-25);
				}
				if (op == 2) {
					if ((text[i] < 'а' || text[i] > 'я') && (text[i] < 'А' || text[i] > 'Я') && text[i] != ' ') throw BadInput(-25);
				}
			}
			if (var) if ((text != "декабрь" && text != "январь")) throw BadInput(-28);
		}
		catch (BadInput& obj) {
			flag = true;
			obj.What();
			text.clear();
			in.clear();
			cout << "Повторите попытку: ";
		}
	}
	return text;
}

string EnterMonth(istream& in) {
	string month;
	bool flag = true;
	while (flag) {
		flag = false;
		rewind(stdin);
		in >> month;
		try {
			for (int i = 0; i < month.size(); i++) {
				if (month[i] < 'а' || month[i] > 'я') throw BadInput(-25);
			}
			if (month != "декабрь" && month != "январь") throw BadInput(-28);
		}
		catch (BadInput& obj) {
			flag = true;
			obj.What();
			month.clear();
			in.clear();
			cout << "Повторите попытку: ";
		}
	}
	return month;
}

int EnterNumber(istream& in, int option) {	
	string number;							
	bool flag = true;				
	int num;									
	while (flag) {
		flag = true;
		in >> number;
		try {
			for (int i = 0; i < number.size(); i++) {
				if ((number[i] < '0' || number[i] > '9') && number[i] != '\n') throw BadInput(-25);
			}
			num = atoi(number.c_str());
			if (num < 0) throw BadInput(-11);
			if (option == 1) if (num > 31) throw BadInput(-12);
			if (option == 2) if (num >= 24) throw BadInput(-13);
			if (option == 3) if (num >= 60) throw BadInput(-14);
			if (option == 4) if (num > 25) throw BadInput(-15);
			if (option == 5) if (num > 40) throw BadInput(-16);
			flag = false;
		}
		catch (BadInput& obj) {
			obj.What();
			number.clear();
			in.clear();
			cout << "Повторите попытку: ";
		}
	}
	return num;
}

string GetWeekDay(int& day) {
	switch (day) {
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
		return "по_будням"; 
		break;
	case 6:
	case 7:
		return "выходные";
		break;
	}
}

string GetRegularity(string& month, int& day) {
	if (month == "декабрь") {
		int ms[] = { 2,3,4,5,6,7,1 };
		for (int i = 0; i < 7; i++) {
			int num = i + 1;
			while (ms[i] <= 31) {
				if (day == ms[i]) return GetWeekDay(num);
				ms[i] += 7;
			}
		}
	}
	if (month == "январь") {
		int ms[] = { 6,7,1,2,3,4,5 };
		for (int i = 0; i < 7; i++) {
			int num = i + 1;
			while (ms[i] <= 31) {
				if (day == ms[i]) return GetWeekDay(num);
				ms[i] += 7;
			}
		}
	}
}

string EnterTripDate() {
	cout << " Просмотр рейсов возможен только до февраля 2020 г.!\n";
	cout << " Введите дату поездки.\n";
	cout << " Месяц: ";
	string month = EnterText(cin, 0, 1);
	cout << " Число: ";
	int day = EnterNumber(cin, 1);
	return GetRegularity(month, day);
}

bool RegularityComparing(string reg1, string reg2) {
	if (reg1 == "ежедневно") return true;
	if (reg1 == "выходные" && reg2 == "выходные") return true;
	if (reg1 == "по_будням" && reg2 == "по_будням") return true;
	return false;
}

string setType(int option) {
	switch (option) {
	case 1:
		return "E:/KURSACH_3sem/files/National.txt";
		break;
	case 2:
		return "E:/KURSACH_3sem/files/International.txt";
		break;
	case 3:
		return "E:/KURSACH_3sem/files/Excursions.txt";
		break;
	case 4:
		return "E:/KURSACH_3sem/files/Tours_in_Belarus.txt";
		break;
	case 5:
		return "E:/KURSACH_3sem/files/Overseas_tours.txt";
		break;
	case 11:
		return "E:/KURSACH_3sem/files/National_data.txt";
		break;
	case 12:
		return "E:/KURSACH_3sem/files/International_data.txt";
		break;
	case 13:
		return "E:/KURSACH_3sem/files/Excursions_data.txt";
		break;
	case 14:
		return "E:/KURSACH_3sem/files/Tours_in_Belarus_data.txt";
		break;
	case 15:
		return "E:/KURSACH_3sem/files/Overseas_tours_data.txt";
		break;
	}
}

int selection() {
	system("cls");
	cout << "\tВыберите категорию:\n";
	cout << " 1. Междугородный рейс.\n";
	cout << " 2. Международный рейс.\n";
	cout << " 3. Заказная экскурсия по Беларуси.\n";
	cout << " 4. Тур по Беларуси.\n";
	cout << " 5. Заграничный тур.\n";
	cout << " 0. Назад.\n>";
	switch (EnterOption(0, 5)) {
	case 1: return 1; break;
	case 2: return 2; break;
	case 3: return 3; break;
	case 4: return 4; break;
	case 5: return 5; break;
	case 0: return 0; break;
	}
}
