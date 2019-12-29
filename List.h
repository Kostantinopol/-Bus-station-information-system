#pragma once
#include "pch.h"
#include "Algorithms.h"
#include "Exceptions.h"
#include "File.h"
#include "Key.h"
#include "Trip.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string setType(int);	//устанавливает определенный путь к файлу

template<class T> struct listNode {
	T value;	//значение
	listNode *next, *prev;	//указатели на предыдущий и следующий указатели
};

template<class T, class T1> class List {
private:
	listNode<T> *listHead, *listCurrent;	//указатели на начало и конец списка
	int listSize;	//размер списка
public:
	List() : listHead(NULL), listCurrent(NULL), listSize(0) {}
	~List() { if (!IsClear()) Clear(); }
	bool IsClear();
	void Clear();
	void Add(T);
	bool Delete(T&);
	void Print();
	void FillFromFile(T1&);	//заполнение списка из файла
	void WriteToFile(T1&, int);	//запись списка в файл
	void TripsInsertion(T1&, T, bool);	//отсортированная вставка рейса
	void Sort1();	//сортировка по времени отправки
	void Indexing();	//расстановка индексов

	class Iterator {
	private:
		listNode<T>* listLink;	//указатель на элемент списка
	public:
		Iterator() : listLink(NULL) {}
		Iterator(listNode<T>* p) : listLink(p) {}
		~Iterator() {}

		void operator++() { listLink = listLink->next; }
		void operator--() { listLink = listLink->prev; }
		Iterator operator=(const Iterator& it) {
			this->listLink = it.listLink;
			return *this;
		}
		bool operator==(const Iterator& obj) const { return listLink == obj.listLink; }
		bool operator!=(const Iterator& obj) const { return !(listLink == obj.listLink); }
		T& operator*() const { return listLink->value; }
		bool operator>(const Iterator& obj) { return (*this > (*obj)); }
	};
	Iterator begin() { return Iterator(listHead); }	//возвращает итератор на начало списка
	Iterator end() { return Iterator(listCurrent); }	//возвращает итератор на конец списка
};



template<class T, class T1> bool List<T, T1>::IsClear() {
	if (listHead == NULL) return true;
	else return false;
}

template<class T, class T1> void List<T, T1>::Add(T obj) {
	listNode<T> *newNode = new listNode<T>;
	newNode->value = obj;
	listSize++;
	if (listHead == nullptr) {
		newNode->next = newNode->prev = NULL;
		listHead = listCurrent = newNode;
	}
	else {
		listCurrent->next = newNode;
		newNode->prev = listCurrent;
		newNode->next = NULL;
		listCurrent = newNode;
	}
}

template<class T, class T1> bool List<T, T1>::Delete(T& obj) {
	try {
		if (IsClear()) throw BadInput(-31);
	}
	catch (BadInput& obj) {
		obj.What();
		return false;
	}
	bool flag = false;
	listNode<T>* pointer = listHead;
	if (listHead->next == NULL && listHead->value == obj) {
		listSize--;
		delete listHead;
		listHead = NULL;
		return true;
	}
	while (pointer != NULL) {
		if (pointer->value == obj) {
			listSize--;
			flag = true;
			if (pointer == listHead) {
				pointer = listHead->next;
				pointer->prev = NULL;
				delete listHead;
				listHead = pointer;
			}
			else {
				if (pointer != listCurrent) {
					pointer->next->prev = pointer->prev;
					pointer->prev->next = pointer->next;
					delete pointer;
				}
				else {
					pointer = listCurrent->prev;
					pointer->next = NULL;
					delete listCurrent;
					listCurrent = pointer;
				}
			}
			break;
		}
		pointer = pointer->next;
	}
	return flag;
}

template <class T, class T1> void List<T, T1>::Clear() {
	listSize = 0;
	listCurrent = listHead;
	while (listHead != NULL) {
		listCurrent = listHead->next;
		delete listHead;
		listHead = listCurrent;
	}
	delete listHead;
	delete listCurrent;
}

template<class T, class T1> void List<T, T1>::Print() {
	if (listHead == NULL) {
		cout << "Список пуст.\n";
		return;
	}
	typename List<T, T1>::Iterator first = this->begin(), last = this->end();	//сождаем итератор на начало списка
	Algorithms<typename List<T, T1>::Iterator, T>::Show(first, last);	//вызываем метод-алгоритм для распечатки списка
	cout << endl;
}

template<class T, class T1> void List<T, T1>::FillFromFile(T1& file_data) {
	if (!IsClear()) Clear();
	if (!(file_data.Open(ios::in))) throw BadFile(-42);	//открываем файл для перезаписи
	T content;
	while (content.Input(file_data.GetFileStream())) {
		if (content.GetKeyId() == 0) {
			break;
		}
		this->Add(content);
	}
	file_data.Close();
}

template<class T, class T1> void List<T, T1>::TripsInsertion(T1& file_data, T obj, bool OP) {
	if (!IsClear()) Clear();
	file_data.Open(ios::in);	//открываем файл для перезаписи
	T content;
	bool flag = false;
	if (OP) {
		while (content.Input(file_data.GetFileStream())) {
			if (!flag) {
				if (obj.GetKeyId() == content.GetKeyId()) {
					if (obj.GetShipTime().GetHours() < content.GetShipTime().GetHours()) {	
						flag = true;
						this->Add(obj);
						this->Add(content);
					}
					if (obj.GetShipTime().GetHours() > content.GetShipTime().GetHours()) {
						this->Add(content);
					}
					if (obj.GetShipTime().GetHours() == content.GetShipTime().GetHours()) {
						if (obj.GetShipTime().GetMinutes() < content.GetShipTime().GetMinutes()) {
							flag = true;
							this->Add(obj);
							this->Add(content);
						}
						else this->Add(content);
					}
				}
				if (obj.GetKeyId() < content.GetKeyId()) {
					flag = true;
					this->Add(obj);
					this->Add(content);
				}
				else this->Add(content);
			}
			else this->Add(content);
		}
		if (!flag) this->Add(obj);
		typename List<T, T1>::Iterator it = this->begin();
		int  index = 1;
		while (it != NULL) {
			(*it).SetRouteId(index++);
			++it;
		}
	}
	else {
		while (content.Input(file_data.GetFileStream())) {
			if (!(content == obj)) this->Add(content);
		}
	}
	this->Print();
	file_data.Close();
}

template<class T, class T1> void List<T, T1>::WriteToFile(T1& file_data, int option) {
	if (file_data.IsOpen()) file_data.Close();
	ofstream file_stream;
	file_stream.open(setType(option));
	typename List<T, T1>::Iterator it = this->begin();
	while (it != NULL) {
		(*it).Record(file_stream);
		++it;
	}
	file_stream.close();
}

template<class T, class T1> void List<T, T1>::Indexing() {
	int index = 1;
	typename List<T, T1>::Iterator it = this->begin();
	while (it != NULL) {
		(*it).SetKeyId(index++);
		++it;
	}
}

template<class T, class T1> void List<T, T1>::Sort1() {
	//typename List<T, T1>::Iterator first = this->begin(), last = this->end();
	//Algorithms<typename List<T, T1>::Iterator, T>::Sort(first, last);
	for (listNode<T>* first = this->listHead; first != NULL; first = first->next) {
		for (listNode<T>* second = this->listCurrent; second != first; second = second->prev) {
			if (second->value.GetKeyId() < first->value.GetKeyId()) {
				auto *buffer = new listNode<T>;
				buffer->value = second->value;
				second->value = first->value;
				first->value = buffer->value;
			}
		}
	}
	typename List<T, T1>::Iterator it1 = this->begin();
	typename List<T, T1>::Iterator it2 = this->begin();
	++it2;
	int id1, id2;
	int index = 1;
	while (it1 != NULL) {
		if (it2 == NULL) {
			(*it1).SetRouteId(index);
			break;
		}
		id1 = (*it1).GetKeyId();
		id2 = (*it2).GetKeyId();
		(*it1).SetRouteId(index);
		if (id2 != id1) {
			index = 1;
		}
		else index++;
		++it1;
		++it2;
	}

}



//template<class T, class T1> void List<T, T1>::Sort() {
//	if (typeid(T) == typeid(Key)) {
//		for (listNode<T>* first = this->listHead; first != NULL; first = first->next) {
//			for (listNode<T>* second = this->listCurrent; second != first; second = second->prev) {
//				if (strcmp(first->value.GetName().c_str(), second->value.GetName().c_str()) > 0) {
//					auto *buffer = new listNode<T>;
//					buffer->value = first->value;
//					first->value = second->value;
//					second->value = buffer->value;
//				}
//			}
//		}
//		typename List<T, T1>::Iterator it = this->begin();
//		int index = 1;
//		while (it != NULL) {
//			(*it).SetKeyId(index++);
//			++it;
//		}
//	}
//}