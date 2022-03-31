#pragma once

template <class T>
class List
{
public:
	
	List();
	List(const List<T>&);
	~List();
	int getSize();
	void clear();
	bool isEmpty();
	bool hasObject(T);
	T getObject(int);
	bool editObject(T, int);
	int getPosition(T);
	void add(T);
	bool add(T, int);
	bool remove(T);
	bool removeAt(int);

	void print();

	class Node {
	public:
		Node();
		Node(T);
		~Node();
		T object;
		Node* next;
	};

	class Iterator {
	public:
		Iterator(List&);
		T& operator *();
		Iterator operator++();
		bool operator==(Iterator&);
		bool operator!=(Iterator&);
		List* l;
		Node* cur;
	};
	Iterator begin();
	Iterator end();

	friend class Node;
	friend class Iterator;
private:
	Node* head;
	int size;
};

