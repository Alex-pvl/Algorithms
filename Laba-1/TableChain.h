#pragma once
#include <iostream>
#include "TableForm.h"
using namespace std;
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
	TableChain() {}
	TableChain(unsigned int size) {
		TableForm<K, D>::Capacity = pow(2., (int)log(size / 2.) / log(2.));
		Table = new Node * [TableForm<K, D>::Capacity];
		for (unsigned int i = 0; i < TableForm<K, D>::Capacity; i++) {
			Table[i] = nullptr;
		}
	}

	D& Data(K key) {
		this->counter = 1;
		this->Probes = 0;
		unsigned int index = TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key));
		Node* curr = this->Table[index];
		while (curr != nullptr) {
			this->counter++;
			this->Probes++;
			if (curr->key == key)
				return curr->data;
			curr = curr->next;
		}
		throw (-1);
	}

	void Clear() {
		for (int i = 0; i < this->Capacity; i++) {
			Node* node = Table[i];
			while (node != nullptr) {
				Node* tmp = node;
				node = node->next;
				delete tmp;
			}
		}
		this->Size = 0;
	}

	bool Delete(K key) {
		this->counter = 1;
		this->Probes = 0;
		unsigned int index = TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key));
		Node * node = this->Table[index];
		Node* prev = nullptr;
		while (node != nullptr) {
			this->Probes++;
			this->counter++;
			if (node->key == key) {
				break;
			}
			prev = node;
			node = node->next;
		}
		if (node == nullptr) {
			return false;
		}
		if (Table[index] == node) {
			Table[index] = node->next;
			delete node;
			this->Size--;
			return true;
		}
		prev->next = node->next;
		delete node;
		this->Size--;

		return true;
	}

	bool Insert(K key, D data) {
		this->counter = 1;
		this->Probes = 0;
		unsigned int hash = TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key));
		Node* node = this->Table[hash];
		if (node == nullptr) {
			node = new Node(key, data);
			node->next = nullptr;
			this->Table[hash] = node;
			this->counter++;
			this->Size++;
			return true;
		}
		while (node->next != nullptr) {
			this->Probes++;
			this->counter++;
			if (node->key == key) {
				return false;
			}
			node = node->next;
		}
		this->counter++;
		Node* tmp = new Node(key, data);
		tmp->next = nullptr;
		node->next = tmp;
		this->Size++;
		return true;
	}

	void Print() {
		for (int i = 0; i < this->Capacity; i++) {
			cout << i << ": ";
			Node* ptr = Table[i];
			while (ptr != nullptr) {
				cout << ptr->key << ':' << ptr->data << '\t';
				ptr = ptr->next;
			}
			cout << '\n';
		}
	}

	class Iterator {
	public:
		Iterator(TableChain<K, D>& table) {
			this->table = table;
			this->index = 0;
			for (; this->table.Table[this->index] == nullptr; this->index++) {
				if (this->index >= this->table.Capacity) {
					this->index = -1;
					this->node = nullptr;
					break;
				}
			}
			if (this->index != -1) {
				this->node = this->table.Table[this->index];
			}
		}

		D& operator *() {
			if (this->index == -1) {
				throw(-1);
			}
			return this->node->data;
		}

		Iterator operator ++() {
			if (this->index == -1) {
				throw (-1);
			}
			if (this->node->next != nullptr) {
				this->node = this->node->next;
				return *this;
			}
			for (; this->table.Table[++this->index] == nullptr;) {
				if (this->index >= this->table.Capacity) {
					this->index = -1;
					this->node = nullptr;
					return *this;
				}
			}
			if (this->index != -1) {
				this->node = this->table.Table[this->index];
			}
			return *this;
		}

		bool operator==(const Iterator& iter) {
			return (this->node == iter.node);
		}
		bool operator!=(const Iterator& iter) {
			return (this->node != iter.node);
		}
		int index;
	private:
		
		TableChain table;
		Node* node;
	};

	Iterator begin() {
		Iterator beg(*this);
		return beg;
	}

	Iterator end() {
		Iterator end(*this);
		end.index = -1;
		return end;
	}
};