#pragma once
#include "BST.h"
#include <iostream>

template<class K, class V> 
class RandTree : public BST<K, V>
{
	// �������� ��������� n ��� ������
	void calcAll(typename BST<K, V>::Node*);
	// ��������� ������ � �������� ������
	typename BST<K, V>::Node* put(typename BST<K, V>::Node*, K, V, bool&);
	// �������� ������ � �������� ������
	typename BST<K, V>::Node* remove(typename BST<K, V>::Node*, K, bool&);
	// ������� �� ����������� �����������
	typename BST<K, V>::Node* join(typename BST<K, V>::Node*, typename BST<K, V>::Node*);

	// --------- ��� ������ ----------
	//int getN(typename BST<K, V>::Node*);
	
public:
	// ��������������� BST::put
	bool put(K, V);
	// ��������������� BST::remove
	bool remove(K);
};
