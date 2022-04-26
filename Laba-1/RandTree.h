#pragma once
#include "BST.h"
#include <iostream>

template<class K, class V> 
class RandTree : public BST<K, V>
{
	class Node : public BST<K, V>::Node{
	public:
		// ���������� ����� � ��������� ������� ������
		int n;
	};
	// �������� ��������� n ��� ������
	void calcAll(Node*);
	// ��������� ������ � �������� ������
	Node* put(Node*, K, V, bool&);
	// �������� ������ � �������� ������
	Node* remove(Node*, K, bool&);
	// ������� �� ����������� �����������
	Node* join(Node*, Node*);
	
public:
	// ��������������� BST::put
	bool put(K, V);
	// ��������������� BST::remove
	bool remove(K);
};
