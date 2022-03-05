#include "List.h"

template <class T>
List<T>::Iterator::Iterator(List& list) {
	this->l = list;
	this->cur = nullptr;
}

template <class T>
T& List<T>::Iterator::operator*() {
	return this->cur->object;
}

template <class T>
List<T>::Iterator List<T>::Iterator::operator++() {
	this->cur = this->cur->next;
	return this;
}

template <class T>
bool List<T>::Iterator::operator==(Iterator& iter) {
	return (* (this->l) == *(iter->l)) && (* (this->cur) == *(iter->cur));
}

template <class T>
bool List<T>::Iterator::operator!=(Iterator& iter) {
	return (*(this->l) != *(iter->l)) || (*(this->cur) != *(iter->cur));
}
