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
	this->count = 0;
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
	this->count = 0;
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
	if (node->left != nullptr) {
		deleteNode(node->left);
	}
	if (node->right != nullptr) {
		deleteNode(node->right);
	}
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
		this->count++;
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
		this->count++;
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
		this->count++;
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
	//cout << "R -> t -> L(горизонт):" << endl;
	//this->printVertical(this->root, 0);
	//cout << "L -> R -> t:" << endl;
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
BST<K, V>& BST<K, V>::join(BST& tree) {
	this->size += tree.size;
	this->root = joinNodes(this->root, tree.root);
	tree.root = nullptr;
	tree.size = 0;
	return *this;
}

template<class K, class V>
typename BST<K, V>::Node* BST<K, V>::insertRoot(Node* node, K key, V value, bool &ins) {
	bool inserted;
	if (node == nullptr) {
		inserted = true;
		return new Node(key, value);
	}
	if (key == node->key) {
		inserted = false;
		return node;
	}
	if (key < node->key) {
		node->left = insertRoot(node->left, key, value, inserted);
		inserted = ins;
		if (ins) {
			return R(node);
		}
		else {
			return node;
		}
	}
	else {
		node->right = insertRoot(node->right, key, value, inserted);
		inserted = ins;
		if (ins) {
			return L(node);
		}
		else {
			return node;
		}
	}
}

template<class K, class V>
typename BST<K, V>::Node* BST<K, V>::L(Node* node) {
	if (node == nullptr) {
		return nullptr;
	}
	else {
		Node* x = node->right;
		node->right = x->left;
		x->left = node;
		return x;
	}
}

template<class K, class V>
typename BST<K, V>::Node* BST<K, V>::R(Node* node) {
	if (node == nullptr) {
		return nullptr;
	}
	else {
		Node* x = node->left;
		node->left = x->right;
		x->right = node;
		return x;
	}
}

template<class K, class V>
typename BST<K, V>::Node* BST<K, V>::joinNodes(Node* a, Node* b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;
	Node* left = a->left;
	Node* right = a->right;
	K key = a->key;
	V value = a->value;
	a->left = nullptr;
	a->right = nullptr;
	if (a->key == b->key) {
		delete a;
		this->size--;
	}
	bool inserted;
	b = insertRoot(b, key, value, inserted);
	b->left = joinNodes(left, b->left);
	b->right = joinNodes(right, b->right);
	return b;
}

template<class K, class V>
int BST<K, V>::countNodes() {
	int k = this->count;
	this->count = 0;
	return k;
}

template<class K, class V>
void BST<K, V>::clearCount() {
	this->count = 0;
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