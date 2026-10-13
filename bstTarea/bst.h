#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T> class BST;

template <class T>
class Node {
    private:
        T value;
        Node<T> *left;
        Node<T> *right;
        // es apuntador porque lo que devuelve la función es un apuntador
        Node<T> *predecesor();
    
    public:
        Node(T);
        Node(T, Node<T>*, Node<T>*);

        void add(T);
        bool find(T);
        void inorder(stringstream&) const;
	    void preorder(stringstream&) const;
        void postorder(stringstream&) const;
        void levelorder(stringstream&, int) const;
        int height();
        int whatlevelamI(T);
        void removeChilds();
        
        friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left (0), right (0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node <T> *ri) : value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val){
    Node<T> *nuevo = new Node<T>(val);
    if (val < value){
        if(left != 0){
            left->add(val);
        }else{
            left = nuevo;
        }
    }else{
        if(right != 0){
            right->add(val);
        }else{
            right = nuevo;
        }
    }
}

template <class T>
// se necesita return porque la función devuelve un true or false
// si la función fuera void no es necesario el return y solo se usa la recursión
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		if(left != 0){
			return left->find(val);
		}
	} else if (val > value) {
		if(right != 0){
			return right->find(val);
		}
	}
	return false;
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
void Node<T>::inorder(stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() > 0) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::postorder(stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
    }
	if (right != 0) {
		right->postorder(aux);
	}
    if (aux.tellp() > 0) {
		aux << " ";
	}
    aux << value;
}

template <class T>
void Node<T>::levelorder(stringstream& aux, int level) const {
    if (level == 1) {
        if (aux.tellp() > 1) { // Aseguramos que se comporte igual que los demás recorridos
            aux << " ";
        }
        aux << value;
    } else {
        if (left != 0) {
            left->levelorder(aux, level - 1);
        }
        if (right != 0) {
            right->levelorder(aux, level - 1);
        }
    }
}

template <class T>
int Node<T>::height() {
    int leftHeight = 0;
    int rightHeight = 0;
    
    if (left != 0) {
        leftHeight = left->height();
    }
    
    if (right != 0) {
        rightHeight = right->height();
    }
    
    if (leftHeight > rightHeight) {
        return 1 + leftHeight;
    } else {
        return 1 + rightHeight;
    }
}

template <class T>
int Node<T>::whatlevelamI(T val) {
    if (value == val) {
        return 1; 
    } else if (val < value) {
        if (left != 0) {
            int level = left->whatlevelamI(val);
            if (level != -1) {
                return level + 1;
            }
        }
    } else if (val > value) {
        if (right != 0) {
            int level = right->whatlevelamI(val);
            if (level != -1) {
                return level + 1;
            }
        }
    }
    return -1;
}


template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
class BST {
    private:
        Node<T> *root;
    public:
        BST();
        ~BST();
        void add(T);
        void levelorder(stringstream&) const;
        string visit() const;
        int height() const;
        string ancestors(T) const;
        int whatlevelamI(T) const;
        void removeAll();
};

template <class T>
BST<T>::BST() : root(0) {}


template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void BST<T>::levelorder(std::stringstream &aux) const {
    if (root == 0) {
        aux << "[]";
        return;
    }

    aux << "[";
    int h = height();
    for (int i = 1; i <= h; i++) {
        root->levelorder(aux, i);
    }
    aux << "]";
}

template <class T>
string BST<T>::visit() const {
    stringstream aux;
    if (root != 0) {
        levelorder(aux);
        
        stringstream temp1;
        root->inorder(temp1);
        aux << "\n[" << temp1.str() << "]";
        
        stringstream temp2;
        root->postorder(temp2);
        aux << "\n[" << temp2.str() << "]";
        
        stringstream temp3;
        root->preorder(temp3);
        aux << "\n[" << temp3.str() << "]";
    }
    return aux.str();
}


template <class T>
int BST<T>::height() const {
    if (root == 0) {
        return 0;
    }
    return root->height();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    if (root == 0) {
        return -1;
    }
    return root->whatlevelamI(val);
}

template <class T>
string BST<T>::ancestors(T val) const {
    stringstream aux;
    Node<T>* actual = root;

    aux << "[";
    while (actual != 0 && actual->value != val) {
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << actual->value;
		if (val < actual->value) {
			actual = actual->left;
		} else {
			actual = actual->right;
		}
	}
	if (actual == 0) {
		return "[]";
	}
	aux << "]";
	return aux.str();
}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

#endif