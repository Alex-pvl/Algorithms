#include "BST.h"
#include <iostream>

using namespace std;

// --------------------- Узел ----------------------------------
template<class K, class V>
BST<K, V>::Node::Node(K key, V value) {
	this->key = key;
	this->value = value;
	this->left = this->right = nullptr;
}

// -------------------- Дерево --------------------------------
template<class K, class V>
BST<K, V>::BST() {
	this->root = nullptr;
	this->size = 0;
}

template<class K, class V>
BST<K, V>::BST(const BST& tree) {
	this->root = tree->root;
	this->size = tree->size;
	// TODO: перенести
}

template<class K, class V>
BST<K, V>::~BST() {
	this->clear();
}

template<class K, class V>
int BST<K, V>::getSize() {
	return this->size;
}

template<class K, class V>
void BST<K, V>::clear() {
	// TODO
}

template<class K, class V>
bool BST<K, V>::isEmpty() {
	return this->root == nullptr;
}

template<class K, class V>
bool BST<K, V>::put(K key, V value) {
	if (this->root == nullptr) {
		this->root = new Node(key, value);
		return true;
	}
	Node* node = this->root;
	Node* pred = nullptr;
	while (node != nullptr) {
		pred = node;
		if (key == node->key) {
			return false;
		}
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	if (key < pred->key) {
		pred->left = new Node(key, value);
	}
	else {
		pred->right = new Node(key, value);
	}
	return true;
}

template<class K, class V>
bool BST<K, V>::remove(K key) {
	Node* node = this->root, * pred, * x, * y;
	while (node != nullptr && node->key != key) {
		pred = node;
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	if (node == nullptr) {
		return false;
	}
	pred = nullptr;
	if (node->left == nullptr && node->right == nullptr) {
		x = nullptr;
	}
	else if (node->left == nullptr) {
		x = node->right;
	}
	else if (node->right == nullptr) {
		x = node->left;
	}
	else {
		pred = node;
		y = node->right;
		while (y->left != nullptr) {
			pred = y;
			y = y->left;
		}
		node->key = y->key;
		node->value = y->value;
		x = y->right;
		node = y;
	}
	if (pred == nullptr) {
		this->root = x;
	}
	else {
		if (node->key < pred->key) {
			pred->left = x;
		}
		else {
			node->right = x;
		}
	}
	delete node;
	return true;
}

template<class K, class V>
V& BST<K, V>::get(K key) {
	Node* node = this->root;
	while (node != nullptr && node->key != key) {
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	if (node == nullptr) {
		throw exception("Исключение\n");
	}
	return node->value;
}

template<class K, class V>
void BST<K, V>::print() {
	this->printNode(this->root);
}

template<class K, class V>
void BST<K, V>::printNode(Node* cur) {
	if (cur->left != nullptr) {
		this->printNode(cur->left);
	}
	if (cur->right != nullptr) {
		this->printNode(cur->right);
	}
	cout << cur->key << " ";
}

template<class K, class V>
BST<K, V> BST<K, V>::join(BST& tree) {
	// TODO
	return nullptr;
}

// --------------------- Итератор ------------------------------
template <class K, class V>
BST<K, V>::Iterator::Iterator() {
	this->tree = nullptr;
	this->cur = nullptr;
	/*while (cur->right != nullptr) {
		cur = cur->right;
	}*/
}

template <class K, class V>
BST<K, V>::Iterator::Iterator(BST& tree) {
	this->tree = &tree;
	this->cur = tree.root;
	/*while (cur->left != nullptr) {
		cur = cur->left;
	}*/
}

template <class K, class V>
V& BST<K, V>::Iterator::operator*() {
	// TODO
	if (this->cur != nullptr) {
		return this->cur->value;
	}
	else {
		throw exception("Исключение\n");
	}
}

template <class K, class V>
typename BST<K, V>::Iterator BST<K, V>::Iterator::operator++() {
	// TODO
	if (this->cur != nullptr) {
		
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

// --------------------- Обратный Итератор ------------------------------
template <class K, class V>
BST<K, V>::RevIterator::RevIterator() {
	this->tree = nullptr;
	this->cur = nullptr;
	/*while (cur->right != nullptr) {
		cur = cur->right;
	}*/
}

template <class K, class V>
BST<K, V>::RevIterator::RevIterator(BST& tree) {
	this->tree = &tree;
	this->cur = tree.root;
	/*while (cur->right != nullptr) {
		cur = cur->right;
	}*/
}

template <class K, class V>
V& BST<K, V>::RevIterator::operator*() {
	// TODO
	if (this->cur != nullptr) {
		return this->cur->value;
	}
	else {
		throw exception("Исключение\n");
	}
}

template <class K, class V>
typename BST<K, V>::RevIterator BST<K, V>::RevIterator::operator++() {
	//TODO

	if (this->cur != nullptr) {
		
		return *this;
	}
	else {
		throw exception("Исключение\n");
	}
}

template <class K, class V>
bool BST<K, V>::RevIterator::operator==(RevIterator& iter) {
	return ((this->tree) == (iter.tree)) && ((this->cur) == (iter.cur));
}

template <class K, class V>
bool BST<K, V>::RevIterator::operator!=(RevIterator& iter) {
	return ((this->tree) != (iter.tree)) || ((this->cur) != (iter.cur));
}

template <class K, class V>
typename BST<K, V>::RevIterator BST<K, V>::rbegin() {
	RevIterator beg(*this);
	return beg;
}

template <class K, class V>
typename BST<K, V>::RevIterator BST<K, V>::rend() {
	RevIterator end(*this);
	end.cur = nullptr;
	return end;
}