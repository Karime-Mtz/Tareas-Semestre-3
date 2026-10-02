/*
 * dlist.h
 *
 *  Created on: 01/10/2026
 *      Author: Karime Martínez López
 */

#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T> class DList;

template <class T>
class DLink {
private:
    T value;
    DLink<T> *previous;
    DLink<T> *next;

    DLink();
    DLink(T);
    DLink(T, DLink<T>*, DLink<T>*);

    friend class DList<T>;
};

template <class T>
DLink<T>::DLink(){
    value = 0;
    previous = 0;
    next = 0;
}

template <class T>
DLink<T>::DLink(T val){
    value = val;
    previous = 0;
    next = 0;
}

template <class T>
DLink<T>::DLink(T val, DLink<T> *ant, DLink<T> *sig){
    value = val;
    previous = ant;
    next = sig;
}

template <class T>
class DList {
private:
    DLink<T> *head;
    DLink<T> *tail;
    int size;

public:
    DList();
    ~DList();

    void insertion(T);
    T search(T);
    void update(int, T);
    void deleteAt(int);
    string toStringForward() const;
    string toStringBackward() const;
    void clear();
};

template <class T>
DList<T>::DList(){
    size = 0;
    head = 0;
    tail = 0;
}

template <class T>
void DList<T>::insertion(T val){
    DLink<T> *nuevo = new DLink<T>(val);

    if (size == 0) {
        head = nuevo;
        tail = nuevo;
    } else {
        tail->next = nuevo;
        nuevo->previous = tail;
        tail = nuevo;
    }
    size++;
}

template <class T>
T DList<T>::search(T val){
    DLink<T> *aux = head;
    int pos = 0;
    while (aux != 0) {
        if (aux->value == val) {
            return pos;
        }
        aux = aux->next;
        pos++;
    }
    return -1;
}

template <class T>
void DList<T>::update(int pos, T val){
    if (pos < 0 || pos >= size) {
        return;
    }
    if (pos > size / 2) {
        DLink<T> *final = tail;
        int cont = size - 1;
        while (cont != pos) {
            final = final->previous;
            cont--;
        }
        final->value = val;
    } else {
        DLink<T> *inicio = head;
        int cont = 0;
        while (cont != pos) {
            inicio = inicio->next;
            cont++;
        }
        inicio->value = val;
    }
}

template <class T>
void DList<T>::deleteAt(int pos){
    if (pos < 0 || pos >= size || head == 0){
        return;
    }
    DLink<T> *aux;

    if (pos == 0) {
        aux = head;
        head = head->next;
        if (head != 0) {
            head->previous = 0;
        } else {
            tail = 0;
        }
    } else if (pos == size - 1) {
        aux = tail;
        tail = tail->previous;
        if (tail != 0) {
            tail->next = 0;
        } else {
            head = 0;
        }
    } else {
        if (pos <= size / 2) {
            aux = head;
            int cont = 0;
            while (cont != pos) {
                aux = aux->next;
                cont++;
            }
        } else {
            aux = tail;
            int cont = size - 1;
            while (cont != pos) {
                aux = aux->previous;
                cont--;
            }
        }

        aux->previous->next = aux->next;
        aux->next->previous = aux->previous;
    }

    delete aux;
    size--;
}

template <class T>
string DList<T>::toStringForward() const {
    stringstream aux;
    DLink<T> *p = head;

    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
string DList<T>::toStringBackward() const {
    stringstream aux;
    DLink<T> *p = tail;

    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

template <class T>
void DList<T>::clear(){
    DLink<T> *p = head;
    while (p != 0) {
        DLink<T> *q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
DList<T>::~DList(){
    clear();
}

#endif