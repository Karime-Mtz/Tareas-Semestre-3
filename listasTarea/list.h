/*
 * list.h
 *
 *  Created on: 27/09/2026
 *      Author: Karime Martínez López
 */

 #ifndef LIST_H
 #define LIST_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;


template <class T> class List;


template <class T>
class Link {
    private: 
        T value;
        Link <T> *next;

        Link();
        Link(T);
        Link(T, Link<T>*);

        friend class List<T>; 
};

template <class T>
Link<T>::Link(){
    value = 0;
    next = 0;
}

template <class T>
Link<T>::Link(T val){
    value = val;
    next = 0;
}

template <class T>
Link<T>::Link(T val, Link<T> *sig){
    value = val;
    next = sig;
}


template <class T> 
class List {
    private:
        Link<T> *head;
        int size;

    public:
        List();
        ~List();

        void insertion(T);
        T search(T);
        void update(T, T);
        void deleteAt(T);
        string toString() const;
        void clear();
};

template <class T> 
List<T>::List(){
    size = 0;
    head = 0;
}

template <class T>
void List<T>::insertion(T num){
    Link<T> *nuevo = new Link<T>(num);
    if(head == 0){
        head = nuevo;
    }else{
    Link<T> *aux = head;
    while(aux->next != 0){
        aux = aux->next; 
        }
        aux->next = nuevo;
    }
    size++;
}

template <class T>
T List<T>::search(T valor){
    Link<T> *aux = head;
    T index = 0;
    while(aux != 0){
        if(valor == aux->value){
            return index;
        }else{
            index++;
            aux = aux->next;
        }
    }
    return -1;
}

template <class T>
void List<T>::update(T pos, T val){
    Link<T> *aux = head;
    int cont = 0;
    while (aux != 0){
        if(cont == pos){
            aux->value = val;
            return;
        }else{
            aux = aux->next;
            cont++;
        }
    }
}

template <class T>
void List<T>::deleteAt(T pos){
    if (head == 0 or pos < 0 or pos >= size){
        return;
    }

    Link<T> *eliminado;

    if(pos==0){
        eliminado = head;
        head = head->next;
    } else{
        Link<T> *aux = head;
        int cont = 0;
        while(cont < pos -1){
            aux = aux ->next;
            cont++;
        }
        eliminado = aux ->next;
        aux->next = eliminado ->next;
    }
    delete eliminado;
    size--;
}

template <class T>
string List<T>::toString() const {
	stringstream aux;
	Link<T> *p;

	p = head;
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
void List<T>::clear(){
    Link<T> *p = head;
    while(p != 0){
        Link<T> *q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    size = 0;
}

template <class T>
List<T>::~List(){
    clear ();
}

 #endif
 