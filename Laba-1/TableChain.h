#pragma once
#include "TableForm.h"
template <class K, class D>
class TableChain : public TableForm <K, D>
{
protected:
	class Node {
	public:
		K key;
		D data;
		Node* next;
		Node(K newkey, D newdata) {
			key = newkey;
			data = newdata;
		}
	};
	Node** Table;
public:
	TableChain(unsigned int size) {
		TableForm<K, D>::Capacity = pow(2., (int)log(size / 2.) / log(2.));
		Table = new Node * [TableForm<K, D>::Capacity];
		for (unsigned int i = 0; i < TableForm<K, D>::Capacity; i++) {
			Table[i] = nullptr;
		}
	}

	D& Data(K key) {
		Node* curr;
		unsigned int index = TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key));
		while (curr != nullptr) {
			if (curr->key == key)
				return curr->data;
			curr = curr->next;
		}
		throw (-1);
	}

};