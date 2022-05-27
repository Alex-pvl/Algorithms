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
		TableForm<K, D>::Capacity = pow(2., (int)log(size * 2.) / log(2.));
		Table = new Node * [TableForm<K, D>::Capacity];
		for (unsigned int i = 0; i < TableForm<K, D>::Capacity; i++) {
			Table[i] = nullptr;
		}
	}

	D& Data(K key) {
		this->counter = 0;
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
		this->counter = 0;
		this->Probes = 0;
		unsigned int index = TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key));
		Node * node = this->Table[index];
		if (node->key == key) {
			Table[index] = node->next;
			delete node;
			this->Size--;
			this->counter++;
			return true;
		}
		while (node != nullptr) {
			this->Probes++;
			this->counter++;
			if (node->next->key == key) {
				Node* tmp = node->next;
				node->next = tmp->next;
				delete tmp;
				this->Size--;
				return true;
			}
		}
	}

	bool Insert(K key, D data) {
		if (this->Size >= this->Capacity * 0.75) {
			this->Expand();
		}
		this->counter = 0;
		this->Probes = 0;
		Node* node = this->Table[TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key))];
		if (node == nullptr) {
			node = new Node(key, data);
			this->Table[TableForm<K, D>::Hash(TableForm<K, D>::toUnsign(key))] = node;
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

	void Expand() {
		Node** tmp = new Node * [this->Capacity];
		for (int i = 0; i < this->Capacity; i++) {
			tmp[i] = this->Table[i];
		}
		delete this->Table;
		unsigned int oldCap = this->Capacity;
		this->Capacity = pow(2., (int)log(this->Size * 2.) / log(2.));
		this->Table = new Node * [this->Capacity];
		for (int i = 0; i < oldCap; i++) {
			this->Table[i] = tmp[i];
		}
		delete tmp;
	}

	class Iterator {
	public:
		Iterator(TableChain& table) {
			this->table = table;
			this->index = 0;
			for (; this->table[this->index] == nullptr; this->index++) {
				if (this->index >= this->table.Capacity) {
					this->index = -1;
					this->node = nullptr;
				}
			}
			if (this->index != -1) {
				this->node = this->table[this->index];
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
			for (; this->table[this->index] == nullptr; this->index++) {
				if (this->index >= this->table.Capacity) {
					this->index = -1;
					this->node = nullptr;
					return *this;
				}
			}
			if (this->index != -1) {
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
	}
};