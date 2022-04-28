#pragma once
#include "BST.h"
#include <iostream>

template<class K, class V> 
class RandTree : public BST<K, V>
{
	// �������� ��������� n ��� ������
	void fixN(typename BST<K, V>::Node*);
	// ����� �������
	typename BST<K, V>::Node* L(typename BST<K, V>::Node*);
	// ������ �������
	typename BST<K, V>::Node* R(typename BST<K, V>::Node*);
	// ������� � ������ ������
	typename BST<K, V>::Node* insertRoot(typename BST<K, V>::Node* node, K key, V value, bool& inserted);
	// ��������� ������ � �������� ������
	typename BST<K, V>::Node* put(typename BST<K, V>::Node*, K, V, bool&);
	// �������� ������ � �������� ������
	typename BST<K, V>::Node* remove(typename BST<K, V>::Node*, K, bool&);
	// ������� �� ����������� �����������
	typename BST<K, V>::Node* join(typename BST<K, V>::Node*, typename BST<K, V>::Node*);
	
	// --------- ��� ������ ----------
	int getN(typename BST<K, V>::Node*);
	
public:
	// ��������������� BST::put
	bool put(K, V);
	// ��������������� BST::remove
	bool remove(K);

	
};
