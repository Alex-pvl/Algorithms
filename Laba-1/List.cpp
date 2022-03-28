#include "List.h"
#include <iostream>

using namespace std;

template <class T>
List<T>::Iterator::Iterator(List& list) {
	this->l = list;
	this->cur = list.head;
}

template <class T>
T& List<T>::Iterator::operator*() { //�������� ������� �� �������� ������ ���������� NULL, ���� �������� ����� NULL (�������� ������ �� ������� ����������)
	if (this->cur != nullptr) {
		return this->cur->object;
	}
	else {
		return nullptr;
	}
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++() {
	try {
		if (this->cur != nullptr) {
			this->cur = this->cur->next;
			return this;
		}
		else {
			throw exception("������ ����"); //��������� ���������� ��� �������� ������� ��������� ������ NULL (�� ����� �� ���?)
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
	Iterator beg(this);
	return beg;
}

template <class T>
typename List<T>::Iterator List<T>::end() {
	Iterator end(this);
	end.cur = nullptr;
	return end;
}

template <class T>
List<T>::List() {
	this->head = nullptr;
	this->size = 0;
}

template <class T>
List<T>::List(const List<T>& list) {
	this->size = list->size;
	Iterator iter(list);
	iter = list.begin();
	if (iter != list.end()) {
		this->head = new Node(*iter); //���� �������
		Node prev = this->head;
		++iter;
		while (iter != list.begin())
		{
			Node* cur = new Node(*iter);
			prev.next = cur; //???
			prev = cur;
			delete cur;
			++iter;
		}
		prev.next = this->head;
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
	Iterator iter(this);
	for (int i = 0; i < this->size; i++){
		Node* del = iter.cur; //???
		++iter; //��� ����������� -_-
		delete del;
	}
}

template <class T>
bool List<T>::isEmpty() {
	return !size; //Pizdec
}

template <class T>
bool List<T>::hasObject(T object) {
	Iterator iter(this);
	iter = this->begin();
	for (int i = 0; i < this->size; i++){
		if (*(*iter) == object) { //????
			return true;
		}
	}
	return false;
}

template <class T>
T List<T>::getObject(int n) {
	try {
		if (n > size || n < 1) {
			throw exception("������ ��� ������� ������");
		}
		else {
			Iterator iter(this);
			iter = this->begin();
			for (int i = 1; i < n; i++, ++iter);
			return *(*iter); //????
		}
	}
	catch (const exception e) {
		cerr << e.what();
	}
}

template <class T>
bool List<T>::editObject(T, int) {
	// TODO
	return false;
}

template <class T>
int List<T>::getPosition(T object) {
	Node* tmp = this->head;
	Iterator iter(this);
	iter = this->begin();
	for (int i = 0; i < size; i++) {
		if (*(*iter) == object) {
			return i;
		}
		++iter;
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

