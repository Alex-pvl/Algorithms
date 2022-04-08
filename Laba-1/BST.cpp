#include "BST.h"
#include <iostream>

using namespace std;

// --------------------- Итератор ------------------------------
template <class K, class V>
BST<K, V>::Iterator::Iterator(BST& tree) {
	this->tree = &tree;
	//TODO
}

template <class K, class V>
V& BST<K, V>::Iterator::operator*() {
	Node* dead = new Node;
	delete dead;
	if (this->cur != nullptr && this->cur->right != dead->right) {
		return this->cur->value;
	}
	else {
		throw exception("Исключение\n");
	}

}

template <class K, class V>
typename BST<K, V>::Iterator BST<K, V>::Iterator::operator++() {
	Node* dead = new Node;
	delete dead;
	if (this->cur != nullptr && this->cur->next != dead->right) {
		//TODO
		return *this;
	}
	else {
		throw exception("Исключение\n");
	}
}

template <class K, class V>
bool BST<K, V>::Iterator::operator==(Iterator& iter) {
	return ((this->tree) == (iter.tree)) && ((this->cur) == (iter.cur));
}

template <class K, class V>
bool BST<K, V>::Iterator::operator!=(Iterator& iter) {
	return ((this->tree) != (iter.tree)) || ((this->cur) != (iter.cur));
}

template <class K, class V>
typename BST<K, V>::Iterator BST<K, V>::begin() {
	Iterator beg(*this);
	return beg;
}

template <class K, class V>
typename BST<K, V>::Iterator BST<K, V>::end() {
	Iterator end(*this);
	end.cur = nullptr;
	return end;
}
