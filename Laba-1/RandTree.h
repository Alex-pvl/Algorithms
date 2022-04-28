#pragma once
#include "BST.h"
#include <iostream>

template<class K, class V> 
class RandTree : public BST<K, V>
{
	// Пересчёт параметра n для дерева
	void fixN(typename BST<K, V>::Node*);
	// Левый поворот
	typename BST<K, V>::Node* L(typename BST<K, V>::Node*);
	// Правый поворот
	typename BST<K, V>::Node* R(typename BST<K, V>::Node*);
	// Вставка в корень дерева
	typename BST<K, V>::Node* insertRoot(typename BST<K, V>::Node* node, K key, V value, bool& inserted);
	// Включение данных с заданным ключом
	typename BST<K, V>::Node* put(typename BST<K, V>::Node*, K, V, bool&);
	// Удаление данных с заданным ключом
	typename BST<K, V>::Node* remove(typename BST<K, V>::Node*, K, bool&);
	// Решение об объединении поддеревьев
	typename BST<K, V>::Node* join(typename BST<K, V>::Node*, typename BST<K, V>::Node*);
	
	// --------- Доп методы ----------
	int getN(typename BST<K, V>::Node*);
	
public:
	// переопределение BST::put
	bool put(K, V);
	// переопределение BST::remove
	bool remove(K);

	
};
