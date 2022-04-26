#pragma once
#include "BST.h"
#include <iostream>

template<class K, class V> 
class RandTree : public BST<K, V>
{
	class Node : public BST<K, V>::Node{
	public:
		// количество узлов в поддереве данного дерева
		int n;
	};
	// Пересчёт параметра n для дерева
	void calcAll(Node*);
	// Включение данных с заданным ключом
	Node* put(Node*, K, V, bool&);
	// Удаление данных с заданным ключом
	Node* remove(Node*, K, bool&);
	// Решение об объединении поддеревьев
	Node* join(Node*, Node*);
	
public:
	// переопределение BST::put
	bool put(K, V);
	// переопределение BST::remove
	bool remove(K);
};
