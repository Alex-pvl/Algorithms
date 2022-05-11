#pragma once
#include "TableForm.h"
#include <iostream>
using namespace std;
template <class K, class D>
class TableOpen : public TableForm <K, D>
{
protected:
	class Node
	{
	public:
		K key;
		D data;
		char state;
		Node* next;
		Node(K newkey, D newdata)
		{
			key = newkey;
			data = newdata;
		}
	};
	Node* Table;
public:
	TableOpen(unsigned int size)
	{
		TableForm<K, D>::Capacity = pow(2., (int)log(size / 2.) / log(2.));
		Table = new Node[TableForm<K, D>::Capacity*TableForm<K, D>::Capacity];
	}

	D& Data(K key)
	{
		Node* curr;
		unsigned int index = TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key));
		while (curr != NULL)
		{
			if (curr->key == key)
				return curr->data;
			curr = curr->next;
		}
		throw (-1);
	}

	void Clear() {

	}

	bool Delete(K key) {

	}

	bool Insert(K key, D data) {
		int i = 0, pos = -1;
		do {
			unsigned int index = h(key, i);
			if (this->Table[index]->state == 'd' && pos == -1) {
				pos = index;
			}
			if (this->Table[index]->state == 'b' && this->Table[index]->key == key) {
				return false;
			}
			i++;
		} while (i != this->Capacity && this->Table[index]->state != 'f');
		if (i == this->Capacity && pos == -1) {
			return false;
		}
		if (pos == -1) {
			pos = i;
		}
		Table[pos]->key = key;
		Table[pos]->data = data;
		Table[pos]->state = 'b';
		return true;

	}

	void Print() {

	}

	unsigned int h(unsigned long long key, int i) {
		return (TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key)) + i) % this->Capacity;
	}
};

