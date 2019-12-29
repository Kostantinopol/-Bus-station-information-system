#pragma once
#include "pch.h"
#include "Trip.h"
#include "Tour.h"
#include "Excursion.h"
#include "Exceptions.h"
#include "List.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void printCap(int);	//распечатка шапки таблицы
void printTrait(int);	//распечатка колонки таблицы
bool RegularityComparing(string, string);	//сравнение дат

template<class T> class TextFile {
private:
	string filePath;	//путь к файлу
	fstream fileStream;	//файловый поток
public:
	TextFile(const string& filePath) : filePath{ filePath } { }
	~TextFile(){}
	fstream& GetFileStream() { return this->fileStream; }
	string& GetFilePath() { return this->filePath; }
	void SetFilePath(string path) { this->filePath = path; }
	bool IsOpen() const {
		return fileStream.is_open();
	}

	bool Open(unsigned int mode = ios::out | ios::app) {
		this->fileStream.open(this->filePath, mode);
		return this->fileStream.is_open();
	}

	bool Close() {
		if (!IsOpen()) return true;
		fileStream.close();
		return true;
	}

	bool RecordInFile(T& obj) {
		try {
			if (!IsOpen() && !Open()) throw BadFile(-42);
			obj.Record(fileStream);
			return Close();
		}
		catch (BadFile& obj) {
			obj.What();
			this->fileStream.close();
			return false;
		}
	}

	int GetLastKeyIndex() {	//получение индекса последнего элемента в файле
		try {
			if (!IsOpen() && !Open(std::ios::in))
				throw BadFile(-42);
		}
		catch (BadFile& obj) {
			obj.What();
			Close();
			return 0;
		}
		T content;
		int length = 0;
		while (content.Input(fileStream)) {
			if (content.GetKeyId() == 0) break;
			length++;
		}
		Close();
		return length;
	}

	void Print() {
		try {
			if (!IsOpen() && !Open(std::ios::in))
				throw BadFile(-42);
		}
		catch (BadFile& obj) {
			obj.What();
			Close();
			return;
		}
		T content;
		while (content.Input(this->fileStream)) {
			if (content.GetKeyId() == 0) break;
			cout << " " << content << "\n";
		}
		Close();
	}

	bool Find(T& obj) {	//нахождение конкретного элемента в файле
		try {
			if (!IsOpen() && !Open(ios::in))
				throw BadFile(-42);
		}
		catch (BadFile& obj) {
			obj.What();
			Close();
			return 0;
		}
		T content;
		while (content.Input(fileStream)) {
			if (content.GetKeyId() == 0) return false;
			if (obj.GetName() == content.GetName()) {
				Close();
				return true;
			}
		}
		Close();
		return false;
	}

	T GetContentByIndex(int i) {
		if (!IsOpen() && !Open(std::ios::in)) {
			throw BadFile(-42);
		}
		T content;
		while (content.Input(fileStream)) {
			if (i == content.GetKeyId()) {
				Close();
				return content;
			}
		}
	}

	void PrintByIndex(int i) {
		if (!IsOpen() && !Open(ios::in)) throw BadFile(-42);
		while (!fileStream.eof()) {
			T content;
			content.Input(fileStream);
			if (i == content.GetKeyId()) {
				cout << content << endl;
				break;
			}
		}
		Close();
	}

	void PrintByRequest(int i, string date) {	//распечатка объектов по определенным признакам
		if (!IsOpen() && !Open(ios::in)) throw BadFile(-42);
		bool flag = false;
		T content = nullptr;
		int number = 1;
		printCap(1);
		printTrait(1);
		while (content.Input(fileStream)) {
			if (i == content.GetKeyId() && RegularityComparing(content.GetReg(), date)) {
				flag = true;
				cout << setw(6) << number++ << " |" << content << endl;
				printTrait(1);
			} 
		}
		if (!flag) {
			system("cls");
			if (date == "по_будням") cout << " на будние дни рейсов нет.\n";
			if (date == "выходные") cout << " на выходные дни рейсов нет.\n";
		}
		Close();
	}

	void Clear() {
		remove(this->filePath.c_str());
	}
};