#pragma once
#include "pch.h"
#include "List.h"
//#include "Trip.h"
#include <iostream>
using namespace std;

void printCap(int);
void printTrait(int);

template<class T, class T1> class Algorithms {
public:
	static void Show(T, T);	//распечатка
	static void Sort(T, T);	//сортировка
};

template<class T, class T1> void Algorithms<T, T1>::Show(T begin, T end) {
	while (begin != end) {
		cout << (*begin) << endl;
		++begin;
	}
	cout << (*begin) << endl;
	cout << endl;
}

template<class T, class T1> void Algorithms<T, T1>::Sort(T first, T last) {
	for (first; first != NULL; ++first) {
		for (last; last != first; --last) {
			if ((*last).GetKeyId() < (*first).GetKeyId()) {
				auto *buffer = new T;
				*buffer = last;
				last = first;
				first = *buffer;
			}
		}
	}
	T it1 = first, it2 = first;
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
		if (id2 != id1) index = 1;
		else index++;
		++it1;
		++it2;
	}
}
