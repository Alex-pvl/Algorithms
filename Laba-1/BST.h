#pragma once

template <class K, class V>
class BST {
protected:
	class Node {
	public:
		Node(K, V);
		K key;
		V value;
		Node* left;
		Node* right;
	};

	class Iterator {
		BST* tree;
		Node* cur;
	public:
		Iterator();
		Iterator(Node*);
		V& operator*();
		Iterator operator++();
		bool operator==(Iterator&);
		bool operator!=(Iterator&);
	};

	class RevIterator {
		BST* tree;
		Node* cur;
	public:
		RevIterator();
		RevIterator(Node*);
		V& operator*();
		RevIterator operator++();
		bool operator==(RevIterator&);
		bool operator!=(RevIterator&);
	};
	friend class Node;
	friend class Iterator;
	friend class RevIterator;

public:
	// конструктор
	BST();
	// конструктор копирования
	BST(const BST&);
	// деструктор
	~BST();
	// опрос размера списка
	int getSize();
	// очистка дерева
	void clear();
	// проверка дерева на пустоту
	bool isEmpty();
	// включение данных с заданным ключом
	bool put(K, V);
	// удаление данных с заданным ключом
	bool remove(K);
	// доступ по чтению/записи к данным по ключу
	V* get(K);
	// формирование списка ключей в дереве в порядке обхода узлов по схеме
	void print();
	// дополнительная операция, заданная в варианте задания
	BST join(BST&);
	// запрос прямого итератора, установленного на узел дерева с минимальным ключом
	Iterator begin();
	// запрос «неустановленного» прямого итератора
	Iterator end();
	// запрос обратного итератора, установленного на узел дерева с максимальным ключом
	RevIterator rbegin();
	// запрос «неустановленного» обратного итератора
	RevIterator rend();

private:
	Node* root;
	int size;
};

