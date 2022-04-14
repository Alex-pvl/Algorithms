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
	copyNode(this->root);
}

template<class K, class V>
void BST<K, V>::copyNode(Node* cur) {
	if (cur != nullptr) {
		this->put(cur->key, cur->value);
	}
	copyNode(cur->left);
	copyNode(cur->right);
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
	this->deleteNode(this->root);
	this->root = nullptr;
	this->size = 0;
}

template<class K, class V>
void BST<K, V>::deleteNode(Node* node) {
	if (node == nullptr) return;
	deleteNode(node->left);
	deleteNode(node->right);
	delete node;
}

template<class K, class V>
bool BST<K, V>::isEmpty() {
	return this->root == nullptr;
}

template<class K, class V>
bool BST<K, V>::put(K key, V value) {
	if (this->root == nullptr) {
		this->root = new Node(key, value);
		this->size++;
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
		this->size++;
	}
	else {
		pred->right = new Node(key, value);
		this->size++;
	}
	return true;
}

template<class K, class V>
bool BST<K, V>::remove(K key) {
	Node* node = this->root, * pred = nullptr, * x = nullptr, * y = nullptr;
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
		y = node->right;
		while (y->left != nullptr) {
			y = y->left;
		}
		y->left = node->left;
		x = node->right;
	}
	if (pred == nullptr) {
		this->root = x;
	}
	else {
		if (node->key < pred->key) {
			pred->left = x;
		}
		else {
			pred->right = x;
		}
	}
	delete node;
	this->size--;
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
	cout << "R -> t -> L(горизонт):" << endl;
	this->printVertical(this->root, 0);
	cout << "L -> R -> t:" << endl;
	this->printNode(this->root);
}

template<class K, class V>
void BST<K, V>::printNode(Node* cur) {
	if (cur == nullptr) return;
	this->printNode(cur->left);
	this->printNode(cur->right);
	cout << cur->key << " ";
}

template<class K, class V>
void BST<K, V>::printVertical(Node* cur, int level) {
	if (cur == nullptr) return;
	this->printVertical(cur->right, level+1);
	for (int i = 0; i < level; i++) {
		cout << "\t";
	}
	cout << cur->key << "[" << cur->value << "]\n";
	this->printVertical(cur->left, level+1);
}

template<class K, class V>
BST<K, V> BST<K, V>::join(BST& tree) {

	if (tree->isEmpty()) return this;
	if (this->isEmpty()) return tree;

	return nullptr;
}

// --------------------- Итератор ------------------------------
template <class K, class V>
BST<K, V>::Iterator::Iterator() {
	this->tree = nullptr;
	this->cur = nullptr;
}

template <class K, class V>
BST<K, V>::Iterator::Iterator(BST& tree) {
	this->tree = &tree;
	this->cur = tree.root;
	if (this->cur != nullptr) {
		while (cur->left != nullptr) {
			cur = cur->left;
		}
	}
}

template <class K, class V>
V& BST<K, V>::Iterator::operator*() {
	if (this->cur != nullptr) {
		return this->cur->value;
	}
	else {
		throw exception("Исключение\n");
	}
}

template <class K, class V>
typename BST<K, V>::Iterator BST<K, V>::Iterator::operator++() {
	if (this->cur != nullptr) {
		this->cur = nextNode(this->tree->root);
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

template <class K, class V>
typename BST<K, V>::Node* BST<K, V>::Iterator::nextNode(Node* cur) {
	if (cur == nullptr) return nullptr;
	Node* node = nextNode(cur->left);
	if (node != nullptr) {
		return node;
	}
	if (cur->key > this->cur->key) {
		return cur;
	}
	node = nextNode(cur->right);
	if (node != nullptr) {
		return node;
	}
	return nullptr;
}

// --------------------- Обратный Итератор ------------------------------
template <class K, class V>
BST<K, V>::RevIterator::RevIterator() {
	this->tree = nullptr;
	this->cur = nullptr;
}

template <class K, class V>
BST<K, V>::RevIterator::RevIterator(BST& tree) {
	this->tree = &tree;
	this->cur = tree.root;
	if (this->cur != nullptr) {
		while (cur->right != nullptr) {
			cur = cur->right;
		}
	}
}

template <class K, class V>
V& BST<K, V>::RevIterator::operator*() {
	if (this->cur != nullptr) {
		return this->cur->value;
	}
	else {
		throw exception("Исключение\n");
	}
}

template <class K, class V>
typename BST<K, V>::RevIterator BST<K, V>::RevIterator::operator++() {
	if (this->cur != nullptr) {
		this->cur = nextNode(this->tree->root);
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

template <class K, class V>
typename BST<K, V>::Node* BST<K, V>::RevIterator::nextNode(Node* cur) {
	if (cur == nullptr) return nullptr;
	Node* node = nextNode(cur->right);
	if (node != nullptr) {
		return node;
	}
	if (cur->key < this->cur->key) {
		return cur;
	}
	node = nextNode(cur->left);
	if (node != nullptr) {
		return node;
	}
	return nullptr;
}