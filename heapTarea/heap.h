// Karime Martínez
// Tarea heap 01/11/2026
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T>

class Heap{
    private:
        T *data;
        unsigned int max;
        unsigned int count;
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);
    public:
        Heap(unsigned int) ;
        ~Heap();
        bool empty() const;
        bool full() const;
        void push(T) ;
        void pop() ;
        unsigned int size() const;
        T top() const;
        void clear();
        string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int talla){
    max = talla;
    count = 0;
    data = new T[max];
}

template <class T>
Heap<T>::~Heap() {
    delete [] data;
    data = 0;
    max = 0;
    count = 0;
}

template <class T>
string Heap<T>::toString() const {
	stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}

template <class T>
bool Heap<T>::full() const {
    return (count == max);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2 * pos) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}
template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le <= count && data[le] < data[min]) {
		min = le;
	}
	if (ri <= count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::clear() {
	count = 0;
}

template <class T>
unsigned int Heap<T>::size() const {
    return count;
 }

 template <class T>
T Heap<T>::top() const {
	return data[0];
}

template <class T>
void Heap<T>::pop() {
	if (empty()) {
        return;
    }

	count--;
	data[0] = data[count];
	heapify(0);
}

template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos;
	if (full()) {
		return;
	}

	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

#endif