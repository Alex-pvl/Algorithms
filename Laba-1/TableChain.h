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
	TableChain() {
		this->Capacity = 8;
	}
	TableChain(unsigned int size) {
		TableForm<K, D>::Capacity = pow(2., (int)(log(size / 2.) / log(2.)));
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
			this->Probes++;
			if (curr->key == key)
				return curr->data;
			curr = curr->next;
			this->counter++;
		}
		throw 1;
	}

	void Clear() {
		Node* ptr, * ptrNext;
		for (int i = 0; i < this->Capacity; i++) {
			ptr = this->Table[i];
			while (ptr != nullptr) {
				ptrNext = ptr->next;
				delete ptr;
				ptr = ptrNext;
			}
			this->Table[i] = 0;
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
		while (node != nullptr) {
			if (node->key == key) {
				return 0;
			}
			node = node->next;
			++this->counter;
			++this->Probes;
		}
		node = new Node(key, data);
		node->next = nullptr;
		node->next = Table[hash];
		Table[hash] = node;
		this->Size++;
		return true;
	}

	void Print() {
		Node* ptr;
		for (int i = 0; i < this->Capacity; i++) {
			cout << i << ": ";
			ptr = Table[i];
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
				if (this->index >= this->table.getCapacity()) {
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
				throw 1;
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
			/*if (this->index == -1) {
				throw new exception("Исключение\n"); new exception("Исключение");
			}
			if (this->node->next != nullptr) {
				this->node = this->node->next;
				return *this;
			}
			this->index++;
			while (this->table.Table[this->index] == nullptr) {
				if (this->index == this->table.getCapacity()) {
					this->index = -1;
					this->node = nullptr;
					break;
				}
				this->index++;
			}
			if (this->index != -1) {
				this->node = this->table.Table[this->index];
			}
			return *this;*/
		}


		bool operator==(const Iterator& iter) {
			return (this->node == iter.node);
		}
		bool operator!=(const Iterator& iter) {
			return (this->node != iter.node);
		}

		int index;
		Node* node;
	private:
		TableChain table;
		
	};

	Iterator begin() {
		Iterator beg(*this);
		return beg;
	}

	Iterator end() {
		Iterator end(*this);
		end.index = -1;
		end.node = nullptr;
		return end;
	}
};