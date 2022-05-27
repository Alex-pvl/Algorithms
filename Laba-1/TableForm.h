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
		A = (sqrt(5.) - 1.0) / 2.0; 
	}
	unsigned int Hash(unsigned long long key) { 
		return (unsigned int) (Capacity * (A * key - int(A * key))); 
	}
	unsigned long long toUnsign(K key) { 
		string k = key;
		unsigned long long res = 0;
		for (int i = 0; i < k.length(); i++) {
			res += k[k.length() - i] * pow(32, i);
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
