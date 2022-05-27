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
		Node() { this->state = 'f'; }
		Node(K newkey, D newdata)
		{
			key = newkey;
			data = newdata;
		}
		~Node() {}
	};
	Node* Table;
public:
	TableOpen(unsigned int size) {
		TableForm<K, D>::Capacity = pow(2., (int)(log(size * 2.) / log(2.)));
		Table = new Node[TableForm<K, D>::Capacity];
	}

	D& Data(K key) {
		this->counter = 0;
		this->Probes = 0;
		int i = 0;
		unsigned int index;
		do {
			index = h(key, i);
			if (this->Table[index].state == 'b' && this->Table[index].key == key) {
				return this->Table[index].data;
			}
			this->counter++;
			this->Probes++;
			i++;
		} while (i != this->Capacity && this->Table[index].state != 'f');
		throw (-1);
	}

	void Clear() {
		for (int i = 0; i < this->Capacity; i++) {
			this->Table[i].state = 'f';
		}
		this->Size = 0;
	}

	bool Delete(K key) {
		this->counter = 0;
		this->Probes = 0;
		int i = 0;
		unsigned int index;
		do {
			index = h(key, i);
			if (this->Table[index].state == 'b' && this->Table[index].key == key) {
				Table[index].state = 'd';
				this->Size--;
				return true;
			}
			this->counter++;
			this->Probes++;
			i++;
		} while (i != this->Capacity && this->Table[index].state != 'f');
		return false;
	}

	bool Insert(K key, D data) {
		if (this->Size >= this->Capacity * 0.75) {
			this->Expand();
		}
		this->counter = 0;
		this->Probes = 0;
		int i = 0, pos = -1;
		unsigned int index;
		do {
			index = h(key, i);
			if (this->Table[index].state == 'd' && pos == -1) {
				pos = index;
			}
			if (this->Table[index].state == 'b' && this->Table[index].key == key) {
				return false;
			}
			this->counter++;
			this->Probes++;
			i++;
		} while (i != this->Capacity && this->Table[index].state != 'f');
		if (i == this->Capacity && pos == -1) {
			return false;
		}
		if (pos == -1) {
			pos = index;
		}
		Table[pos].key = key;
		Table[pos].data = data;
		Table[pos].state = 'b';
		this->Size++;
		return true;

	}

	void Print() {
		for (int i = 0; i < this->Capacity; i++) {
			cout << i << ": ";
			if (this->Table[i].state == 'f') {
				cout << "FREE\n";
			}
			if (this->Table[i].state == 'd') {
				cout << "DELETED\n";
			}
			if (this->Table[i].state == 'b') {
				cout << "BUSY " << this->Table[i].key << " " << this->Table[i].data << endl;
			}
		}
	}

	unsigned int h(K key, int i) {
		return (TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key)) + i) % this->Capacity;
	}

	void Expand() {
		Node* tmp = new Node[this->Capacity];
		for (int i = 0; i < this->Capacity; i++) {
			tmp[i].state = this->Table[i].state;
			tmp[i].key = this->Table[i].key;
			tmp[i].data = this->Table[i].data;
		}
		delete this->Table;
		unsigned int oldCap = this->Capacity;
		this->Capacity = pow(2., (int)log(this->Size * 2.) / log(2.));
		this->Table = new Node[this->Capacity];
		for (int i = 0; i < oldCap; i++) {
			this->Table[i].state = tmp[i].state;
			this->Table[i].key = tmp[i].key;
			this->Table[i].data = tmp[i].data;
		}
		delete tmp;
	}

	class Iterator {
	public:
		Iterator(TableOpen& table) {
			this->table = table;
			this->index = 0;
			for (; this->table[this->index].state != 'b'; this->index++) {
				if (this->index >= table.Capacity) {
					this->index = -1;
				}
			}
		}

		D& operator *() {
			if (this->index == -1) {
				throw(-1);
			}
			return this->table[this->index]->data;
		}

		Iterator operator ++() {
			if (this->index == -1) {
				throw (-1);
			}
			for (; this->table[this->index].state != 'b'; this->index++) {
				if (this->index >= table.Capacity) {
					this->index = -1;
					return *this;
				}
			}
			return *this;
		}

		bool operator==(const Iterator& iter) {
			return (this->index == iter.index);
		}
		bool operator!=(const Iterator& iter) {
			return (this->index != iter.index);
		}
	private:
		int index;
		TableOpen table;
	};

	Iterator begin() {
		Iterator beg(*this);
		return beg;
	}
	
	Iterator end() {
		Iterator end(*this);
		end.index = -1;
	}
};

