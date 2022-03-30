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
T& List<T>::Iterator::operator*() { //Операция доступа по значению теперь возвращает NULL, если итератор равен NULL (возможно стоило бы бросать исключения)
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
	delete this->object; 
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
	
	//this->size = list->size;
	//Iterator iter(list);
	//iter = list.begin();
	//if (iter != list.end()) {
	//	this->head = new Node(*iter); //Надо тестить
	//	Node prev = this->head;
	//	++iter;
	//	while (iter != list.begin())
	//	{
	//		Node* cur = new Node(*iter);
	//		prev.next = cur; //???
	//		prev = cur;
	//		delete cur;
	//		++iter;
	//	}
	//	prev.next = this->head;
	//}
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
	//Iterator iter(*this);
	//for (int i = 0; i < this->size; i++){
	//	Node* del = iter.cur; //???
	//	++iter; //Под подозрением -_-
	//	delete del;
	//}
}

template <class T>
bool List<T>::isEmpty() {
	return size == 0; 
}

template <class T>
bool List<T>::hasObject(T object) {
	//Iterator iter(*this);
	//iter = this->begin();
	//for (int i = 0; i < this->size; i++){
	//	if ((*iter) == object) { //????
	//		return true;
	//	}
	//}
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
	// TODO
	return false;
}

template <class T>
int List<T>::getPosition(T object) {
	Node* tmp = this->head;
	int index = 0;
	while (tmp->next != this->head) {
		if (tmp->object == object) {
			return index + 1; // надо инкремент?
		}
		index++;
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
}

template <class T>
bool List<T>::add(T object, int index) {
	// TODO
	return false;
}


template <class T>
bool List<T>::remove(T object) {
	// TODO
	return false;
}

template <class T>
bool List<T>::removeAt(int index) {
	// TODO
	return false;
}
