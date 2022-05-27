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
		TableForm<K, D>::Capacity = pow(2., (int)(log(size * 2.) / log(2.)));
		Table = new Node[TableForm<K, D>::Capacity];
	}

	D& Data(K key)
	{
		int i = 0;
		do {
			unsigned int index = h(key, i);
			if (this->Table[index]->state == 'b' && this->Table[index]->key == key) {
				return this->Table[index]->data;
			}
			this->counter++;
			i++;
		} while (i != this->Capacity && this->Table[index]->state != 'f');
		throw (-1);
	}

	void Clear() {
		for (int i = 0; i < capacity; i++) {
			this->Table[i]->state = 'f';
		}
		this->Size = 0;
	}

	bool Delete(K key) {
		int i = 0;
		do {
			unsigned int index = h(key, i);
			if (this->Table[index]->state == 'b' && this->Table[index]->key == key) {
				Table[pos]->state = 'd';
				this->Size--;
				return true;
			}
			this->counter++;
			i++;
		} while (i != this->Capacity && this->Table[index]->state != 'f');
		return false;
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
			this->counter++;
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
		this->Size++;
		return true;

	}

	void Print() {
		for (int i = 0; i < this->Capacity; i++) {
			cout << i << ": ";
			if (this->Table[i]->state == 'f') {
				cout << "FREE\n";
			}
			if (this->Table[i]->state == 'd') {
				cout << "DELETED\n";
			}
			if (this->Table[i]->state == 'b') {
				cout << "BUSY " << this->Table[i]->key << " " << this->Table[i]->data << endl;
			}
		}
	}

	unsigned int h(unsigned long long key, int i) {
		return (TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key)) + i) % this->Capacity;
	}
};

