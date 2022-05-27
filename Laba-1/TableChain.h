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
		unsigned int index = TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key);
		Node* node = this->Table[index];
		if (node->key == key) {
			Table[index] = node->next;
			delete node;
			this->Size--;
			this->counter++;
			return true;
		}
		while (node != nullptr) {
			this->counter++;
			if (node->next->key == key) {
				Node* tmp = node->next;
				node->next = tmp->next;
				delete tmp;
				this->Size--;
				return true;
			}
		}
		return false;
	}

	bool Insert(K key, D data) {
		Node* node = this->Table[TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key)];
		if (node == nullptr) {
			node = new Node(key, data);
			this->counter++;
			this->Size++;
		}
		while (node->next != nullptr) {
			this->counter++;
			if (node->key == key) {
				return false;
			}
			node = node->next;
		}
		this->counter++;
		Node* tmp = new Node(key, data);
		node->next = tmp;
		this->Size++;
		return true;
	}

	void Print() {
		for (int i = 0; i < capacity; ++i) {
			cout << i << ". ";
			Node* ptr = Table[i];
			while (ptr != 0) {
				cout << ptr->key << ':' << ptr->data << '\t';
				ptr = ptr->next;
			}
			cout << '\n';
		}
	}

	class Iterator {
	public:
		Iterator(TableChain& table) {
			this->table = table;
			this->index = 0;
			this->end = false;
			for (; this->table[this->index] == nullptr; this->index++) {
				if (this->index >= this->table.Capacity) {
					this->end = true;
					this->index = -1;
					this->node = nullptr;
				}
			}
			if (!end) {
				this->node = this->table[this->index];
			}
		}

		D& operator *() {
			if (end) {
				throw(-1);
			}
			return this->node->data;
		}

		Iterator operator ++() {
			if (end) {
				throw (-1);
			}
			if (this->node->next != nullptr) {
				this->node = this->node->next;
				return *this;
			}
			for (; this->table[this->index] == nullptr; this->index++) {
				if (this->index >= this->table.Capacity) {
					this->end = true;
					this->index = -1;
					this->node = nullptr;
					return *this;
				}
			}
			if (!end) {
				this->node = this->table[this->index];
			}
			return *this;
		}

		bool operator==(const Iterator& iter) {
			return (this->node == iter.node);
		}
		bool operator!=(const Iterator& iter) {
			return (this->node != iter.node);
		}
	private:
		int index;
		bool end;
		TableChain table;
		Node* node;
	};
};