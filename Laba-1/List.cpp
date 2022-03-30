#include "List.h"
#include <iostream>

using namespace std;


// --------------------- Итератор ------------------------------
template <class T>
List<T>::Iterator::Iterator(List& list) {
	this->l = &list;
	this->cur = list.head;
}

template <class T>
T& List<T>::Iterator::operator*() {
	try {
		if (this->cur != nullptr) {
			return this->cur->object;
		}
		else {
			throw exception("Отказ доступа"); // что?
		}
	}
	catch (const exception e) {
		cerr << e.what();
	}
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++() {
	try {
		if (this->cur != nullptr) {
			this->cur = this->cur->next;
			return *this;
		}
		else {
			throw exception("Список пуст"); //Добавлено исключение при значении объекта итератора равном NULL (но нужно ли оно?)
		}
	}
	catch (const exception e) {
		cerr << e.what();
	}
}

template <class T>
bool List<T>::Iterator::operator==(Iterator& iter) {
	return (* (this->l) == *(iter->l)) && (* (this->cur) == *(iter->cur)); 
}

template <class T>
bool List<T>::Iterator::operator!=(Iterator& iter) {
	return (*(this->l) != *(iter->l)) || (*(this->cur) != *(iter->cur));
}

template <class T>
typename List<T>::Iterator List<T>::begin() {
	Iterator beg(*this);
	return beg;
}

template <class T>
typename List<T>::Iterator List<T>::end() {
	Iterator end(*this);
	end.cur = nullptr;
	return end;
}

// --------------------- Узел ------------------------------

template <class T> 
List<T>::Node::Node() {
	this->object = nullptr; // new T
	this->next = nullptr;
}

template <class T>
List<T>::Node::Node(T object) {
	this->object = object; 
	this->next = nullptr;
}

template <class T>
List<T>::Node::~Node() {

}

// --------------------- Список ------------------------------

template <class T>
List<T>::List() {
	this->head = nullptr;
	this->size = 0;
}

template <class T>
List<T>::List(const List<T>& list) {
	this->size = list->size;
	if (this->size > 0) {
		Node* tmp = list.head;
		this->head = new Node(tmp->object);
		Node* cur = this->head;
		tmp = tmp->next;
		while (tmp != list.head) {
			Node* newNode = new Node(tmp->object);
			cur->next = newNode;
			cur = cur->next;
		}
		cur->next = this->head;
	}
	else {
		this->head = nullptr;
	}
}

template <class T>
List<T>::~List() {
	this->clear();
}

template <class T>
int List<T>::getSize() {
	return this->size;
}

template <class T>
void List<T>::clear() {
	Node* tmp = this->head;
	for (int i = 0; i < this->size; i++){
		Node* del = tmp;
		tmp = tmp->next;
		delete del;
	}
}

template <class T>
bool List<T>::isEmpty() {
	return size == 0; 
}

template <class T>
bool List<T>::hasObject(T object) {
	Node* tmp = this->head;
	for (int i = 0; i < this->size; i++){
		if (tmp->object == object) {
			return true;
		}
	}
	return false;
}

template <class T>
T List<T>::getObject(int n) {
	try {
		if (n > size || n < 1) throw exception("Некорректный индекс");
		Node* tmp = this->head;
		for (int i = 0; i < n - 1; i++) tmp = tmp->next;
		return *(tmp->object);
	}
	catch (const exception e) {
		cerr << e.what();
	}
}

template <class T>
bool List<T>::editObject(T object, int index) {
	if (index > size || index < 1) {
		return false;
	}
	else {
		Node* tmp = this->head;
		for (int i = 0; i < index - 1; i++) tmp = tmp->next;
		tmp->object = object;
		return true;
	}
}

template <class T>
int List<T>::getPosition(T object) {
	Node* tmp = this->head;
	for (int i = 0; i < this->size; i++) {
		if (tmp->object == object) {
			return i + 1;
		}
		tmp = tmp->next;
	}
	return -1;
}

template <class T>
void List<T>::add(T object) {
	Node* newNode = new Node(object);
	if (this->head == nullptr) {
		this->head = newNode;
	}
	else {
		Node* tmp = this->head;
		while (tmp->next != this->head) {
			tmp = tmp->next;
		}
		tmp->next = newNode;
		newNode->next = this->head;
	}
	this->size++;
}

template <class T>
bool List<T>::add(T object, int index) {
	if (index > size + 1 || index < 0) {
		return false;
	}
	else if (this->size == 0) {
		this->head = new Node(object);

	}
	else {
		Node* tmp = this->head;
		if (index == 0) {
			while (tmp->next != this->head) {
				tmp = tmp->next;
			}
			Node* newNode = new Node(object);
			tmp->next = newNode;
			newNode->next = this->head;
			this->head = newNode;
		}
		else {
			for (int i = 0; i < index - 1; i++) tmp = tmp->next;
			Node* next = tmp->next;
			Node* newNode = new Node(object);
			tmp->next = newNode;
			newNode->next = next;
		}
	}
	this->size++;
	return true;
}


template <class T>
bool List<T>::remove(T object) {
	if (this->head == nullptr) {
		return false;
	}
	else if (this->size == 1) {
		delete this->head;
		this->head = nullptr;
	}
	else {
		Node* tmp = this->head;
		while (tmp->next->next != this->head) {
			tmp = tmp->next;
		}
		delete tmp->next;
		tmp->next = this->head;
	}
	this->size--;
	return true;
}

template <class T>
bool List<T>::removeAt(int index) {
	if (index > size || index < 1) {
		return false;
	}
	else {
		Node* tmp = this->head;
		if (index == 1) {
			while (tmp->next->next != this->head) {
				tmp = tmp->next;
			}
			this->head = tmp->next->next;
			delete tmp->next;
			tmp->next = this->head;
		}
		else {
			for (int i = 0; i < index - 2; i++) tmp = tmp->next;
			Node* next = tmp->next->next;
			delete tmp->next;
			tmp->next = next;
		}
		this->size--;
		return true;
	}
}
