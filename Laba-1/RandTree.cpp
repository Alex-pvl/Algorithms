#pragma once
#include "RandTree.h"
#include <ctime>

template<class K, class V>
int RandTree<K, V>::getN(typename BST<K, V>::Node* node) {
	if (!node) return 0;
	return node->n;
}

template<class K, class V>
void RandTree<K, V>::fixN(typename BST<K, V>::Node* node) {
	node->n = getN(node->left) + getN(node->right) + 1;
}

template<class K, class V>
typename BST<K, V>::Node* RandTree<K, V>::R(typename BST<K, V>::Node* node) {
	typename BST<K, V>::Node* x = node->left;
	if (!x) return node;
	node->left = x->right;
	x->right = node;
	x->n = getN(node);
	fixN(node);
	fixN(x);
	return x;
}

template<class K, class V>
typename BST<K, V>::Node* RandTree<K, V>::L(typename BST<K, V>::Node* node) {
	typename BST<K, V>::Node* x = node->right;
	if (!x) return node;
	node->right = x->left;
	x->left = node;
	x->n = getN(node);
	fixN(node);
	fixN(x);
	return x;
}

template<class K, class V>
typename BST<K, V>::Node* RandTree<K, V>::insertRoot(typename BST<K, V>::Node* node, K key, V value, bool& inserted) {
	if (!node) {
		inserted = true;
		return new typename BST<K, V>::Node(key, value);
	}
	this->count++;
	bool ins;
	if (key == node->key) {
		inserted = false;
		return node;
	}
	if (key < node->key) {
		node->left = RandTree<K, V>::insertRoot(node->left, key, value, ins);
		inserted = ins;
		return RandTree<K, V>::R(node);
	}
	else {
		node->right = RandTree<K, V>::insertRoot(node->right, key, value, ins);
		inserted = ins;
		return RandTree<K, V>::L(node);
	}
}

template<class K, class V>
bool RandTree<K, V>::put(K key, V value) {
	bool ins;
	this->root = put(this->root, key, value, ins);
	if (ins) this->size++;
	return ins;
}

template<class K, class V>
typename BST<K, V>::Node* RandTree<K, V>::put(typename BST<K, V>::Node* node, K key, V value, bool &inserted) {
	if (!node) {
		typename BST<K, V>::Node* t = new typename BST<K, V>::Node(key, value);
		t->n = 1;
		inserted = true;
		return t;
	}
	this->count++;
	srand(clock());
	bool ins;
	if (rand() % (node->n + 1) == 0) {
		node = RandTree<K, V>::insertRoot(node, key, value, ins);
		inserted = ins;
		return node;
	}
	if (key == node->key) {
		inserted = false;
		return node;
	}
	if (node->key > key) {
		node->left = RandTree<K, V>::put(node->left, key, value, ins);
	}
	else {
		node->right = RandTree<K, V>::put(node->right, key, value, ins);
	}
	inserted = ins;
	if (inserted) {
		node->n++;
	}
	return node;
}

template<class K, class V>
bool RandTree<K, V>::remove(K key) {
	bool del;
	this->root = RandTree::remove(this->root, key, del);
	if (del) this->size--;
	return del;
}

template<class K, class V>
typename BST<K, V>::Node* RandTree<K, V>::remove(typename BST<K, V>::Node* node, K key, bool &deleted) {
	if (!node) {
		deleted = false;
		return node;
	}
	this->count++;
	bool del;
	if (key < node->key) {
		node->left = RandTree::remove(node->left, key, del);
	}
	else if (key > node->key) {
		node->right = RandTree::remove(node->right, key, del);
	}
	else {
		del = true;
		typename BST<K, V>::Node* tmp = RandTree::join(node->left, node->right);
		delete node;
		node = tmp;
	}
	deleted = del;
	if (deleted) {
		if (node) {
			if (node->left) {
				node->n = 1 + getN(node->left);
			}
			else {
				node->n = 1;
			}
			if (node->right) {
				node->n += getN(node->right);
			}
		}
	}
	return node;
}

template<class K, class V>
typename BST<K, V>::Node* RandTree<K, V>::join(typename BST<K, V>::Node* a, typename BST<K, V>::Node* b) {
	if (!a) return b;
	if (!b) return a;
	this->count++;
	srand(clock());
	if (rand() % (getN(a) + getN(b)) < getN(a)) {
		a->right = RandTree::join(a->right, b);

		fixN(a);
		return a;
	}
	else {
		b->left = RandTree::join(a, b->left);
		fixN(b);
		return b;
	}
}