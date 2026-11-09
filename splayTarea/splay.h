/*
 *  Created on: 09/11/2026
 *  Author: Karime Martínez
 */

#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	// rotaciones
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*, Node<T>*);

	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void inorder(stringstream&) const;
	void preorder(stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) {
	value = val;
	left = 0;
	right = 0;
	parent = 0;
}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p) {
		value = val;
		left = le;
		right = ri;
		parent = p;
	}


// this es un puntero que apunta al objeto actual de la clase en la que estoy
template <class T>
Node<T>* Node<T>::add(T val) {
	if (val <value) {
		if (left != 0) {
			return left->add(val);
		} else {
			// el papá es this porque al crear el hijo nuevo sigo parado en el padre
			left = new Node<T>(val, 0, 0, this);
			return left;
		}
	} else {
		if (right != 0) {
			return right->add(val);
		} else {
			right = new Node<T>(val, 0, 0, this);
			return right;
		}
	}
}

template <class T>
Node<T>* Node<T>::find(T val) {
	if (val == value) {
		return this;
	} else if (val < value) {
		if (left != 0)
			return left->find(val);
		else
			return this;
	} else {
		if (right != 0)
			return right->find(val);
		else
			return this;
	}
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *old;
	if (val <value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				if (old->right != 0){
					old->right->parent = this;
					left = old->right;
				} else if (old->left != 0) {
					old->left->parent = this;
					left = old->left;
				} else {
					left = 0;
				}
				delete old;
				return this;
			} else{
				return left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				if (old->right != 0) {
					old->right->parent = this;
					right = old->right;
				} else if (old->left != 0) {
					old->left->parent = this;
					right = old->left;
				} else {
					right = 0;
				}
				delete old;
				return this;
			} else {
				return right->remove(val);
			}
		}
	}
	return this;
}


template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x) {
	Node<T> *y = x->right;
	x->right = y->left;
	if (y->left)
		y->left->parent = x;
	y->left = x;
	y->parent = x->parent;
	x->parent = y;
	if (y->parent) {
		if (y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x) {
	Node<T> *y = x->left;
	x->left = y->right;
	if (y->right)
		y->right->parent = x;
	y->right = x;
	y->parent = x->parent;
	x->parent = y;
	if (y->parent) {
		if (y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x) {
	while (x->parent != 0) {

		if (x->parent->value == root->value) {
			if (x->parent->left && x->parent->left->value == x->value) {
				rot_right(x->parent);
			} else {
				rot_left(x->parent);
			}
		} else {
			Node<T>* p = x->parent;
			Node<T>* g = p->parent;
			if (p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value) {
				rot_right(g);
				rot_right(p);
			} else if (p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value) {
				rot_left(g);
				rot_left(p);
			} else if (p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value) {
				rot_right(p);
				rot_left(g);
			} else {
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::preorder(stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	void add(T);
	bool find(T);
	void remove(T);
	string inorder() const;
	string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree(){
	root = 0;
}

template <class T>
string SplayTree<T>::inorder() const {
	stringstream aux;

	aux << "[";
	if (root != 0) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string SplayTree<T>::preorder() const {
	stringstream aux;

	aux << "[";
	if (root != 0) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}


template <class T>
void SplayTree<T>::add(T val) {
	if (root != 0) {
		Node<T>* added =root->add(val);
		root = root->splay(root, added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		Node<T>* eliminado= root->remove(val);
		root= root->splay(root, eliminado);
	}
}

template <class T>
bool SplayTree<T>::find(T val) {
	if (root != 0) {
		Node<T>* element = root->find(val);
		root = root->splay(root, element);
		return (root->value==val);
	}
	return false;
}

#endif