#pragma once
#include <iostream>
#include <string>
using namespace std;

template <class K, class D>
class TableForm
{
public:
	unsigned int Size;
	unsigned int Capacity;
	unsigned int Probes;
	unsigned int counter;
	double A;
	TableForm() { 
		Size = Probes = 0;
		A = 0.6180339887;
	}
	int getCounter() {
		int k = this->counter;
		this->counter = 0;
		return k;
	}
	unsigned int Hash(unsigned long long key) { 
		return (unsigned int) (Capacity * fmodl(key * A, 1.));
	}
	unsigned long long toUnsign(K key) { 
		unsigned long long res = 0;
		for (int i = 0; i < key.length(); i++) {
			res += key[key.length() - i - 1] * pow(26, i);
		}
		return res; 
	}
	unsigned int getSize() { 
		return Size; 
	}
	unsigned int getCapacity() { 
		return Capacity; 
	}
	bool IsEmpty() { 
		return (Size == 0); 
	}
	unsigned int NumOfProbes() { 
		return Probes; 
	}

protected: 
	virtual D& Data(K key) = 0;
	virtual void Clear() = 0;
	virtual bool Insert(K key, D data)=0;
	virtual bool Delete(K key)=0; 
	virtual void Print()=0; 
};
