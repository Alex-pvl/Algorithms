#pragma once
#include <iostream>
using namespace std;
template < class K, class D>
class TableForm
{
public:
	unsigned int Size;
	unsigned int Capacity;
	unsigned int Probes;
	unsigned int counter;
	double A;//константа для хеш-функции
	TableForm() { 
		Size = Probes = 0;
		A = (sqrt(5.) - 1.0) / 2.0; 
	}
	unsigned int Hash(unsigned long long key) { 
		return (unsigned int) (Capacity * (A * key - int(A * key))); 
	}
	unsigned long long toUnsign(K key) { 
		char* k = key;
		int count = 0;
		int res;
		while (k[i] != '\0') {
			count++;
		}
		for (int i = 0; i <= count; i++) {
			res += k[count-i]*pow(32, i);
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

