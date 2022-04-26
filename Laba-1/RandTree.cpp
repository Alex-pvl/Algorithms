#pragma once
#include "RandTree.h"
#include <ctime>


// ס size קעמ-עמ הוכאעü םאהמ, סועעונ לב

template<class K, class V>
void RandTree<K, V>::calcAll(Node* node) {
	// ÒÓÄÓ
}

template<class K, class V>
bool RandTree<K, V>::put(K key, V value) {
	bool ins;
	this->put(this->root, key, value, ins);
	return ins;
}

template<class K, class V>
typename RandTree<K, V>::Node* RandTree<K, V>::put(Node* t, K key, V value, bool& inserted) {
	if (t == nullptr) {
		
		t = new Node(key, value);
		t->n = 1;
		inserted = true;
		return t;
	}
	bool ins;
	srand(clock());
	if (rand() < 1 / (t->n + 1)) {
		t = insertRoot(t, key, value, ins);
		inserted = ins;
		return t;
	}
	if (t->key == key) {
		inserted = false;
		return t;
	}
	if (key < t->key) {
		t->left = put(t->left, key, value, ins);
	}
	else {
		t->right = put(t->right, key, value, ins);
	}
	inserted = ins;
	if (inserted) {
		t->n++;
	}
	return t;
}

template<class K, class V>
bool RandTree<K, V>::remove(K key) {
	bool del;
	this->remove(this->root, key, del);
	return del;
}

template<class K, class V>
typename RandTree<K, V>::Node* RandTree<K, V>::remove(Node* t, K key, bool &deleted) {
	if (t == nullptr) {
		deleted = false;
		return t;
	}
	bool del;
	if (key < t->key) {
		t->left = remove(t->left, key, del);
	}
	else if (key > t->key) {
		t->right = remove(t->right, key, del);
	}
	else {
		Node* x = join(t->left, t->right);
		delete t;
		t = x;
		del = true;
	}
	deleted = del;
	if (deleted) {
		calcAll(t);
	}
	return t;
}

template<class K, class V>
typename RandTree<K, V>::Node* RandTree<K, V>::join(Node* a, Node* b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;
	srand(clock());
	if (rand() / (1 / (a->n + b->n + 1)) < a->n) {
		a->right = join(a->right, b);
	}
	else {
		b->left = join(a, b->left);
	}
	return b;
}