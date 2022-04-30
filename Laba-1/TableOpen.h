#pragma once
#include "TableForm.h"
template <class K, class D>
class TableOpen : public TableForm <K, D>
{
protected:
	class Node
	{
	public:
		K key;
		D data;
		Node* next;
		Node(K newkey, D newdata)
		{
			key = newkey;
			data = newdata;
		}
	};
	Node** Table;
public:
	TableOpen(unsigned int size)
	{
		TableForm<K, D>::Capacity = pow(2., (int)log(size / 2.) / log(2.));
		Table = new Node * [TableForm<K, D>::Capacity];
		for (unsigned int i = 0; i < TableForm<K, D>::Capacity; i++)
			Table[i] = NULL;
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

};

