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

public:
	class Iterator {
		BST* tree;
		Node* cur;
		friend class BST;
	public:
		Iterator();
		Iterator(BST&);
		// операция доступа по чтению и записи к данным текущего узла
		V& operator*();
		// операция перехода к следующему по ключу узлу в дереве
		Iterator operator++();
		// проверка равенства однотипных итераторов
		bool operator==(Iterator&);
		// проверка неравенства однотипных итераторов
		bool operator!=(Iterator&);
		Node* nextNode(Node*);
		
	};

	class RevIterator {
		BST* tree;
		Node* cur;
		friend class BST;
	public:
		RevIterator();
		RevIterator(BST&);
		// операция доступа по чтению и записи к данным текущего узла
		V& operator*();
		// операция перехода к предыдущему по ключу узлу в дереве
		RevIterator operator++();
		// проверка равенства однотипных итераторов
		bool operator==(RevIterator&);
		// проверка неравенства однотипных итераторов
		bool operator!=(RevIterator&);
		Node* nextNode(Node*);
	};
	friend class Node;
	
	// конструктор
	BST();
	// конструктор копирования
	BST(const BST&);
	// деструктор
	~BST();
	// опрос размера дерева
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
	V& get(K);
	// формирование списка ключей в дереве в порядке обхода узлов по схеме
	void print();
	// объединение двух BST-деревьев
	BST& join(BST&);
	// запрос прямого итератора, установленного на узел дерева с минимальным ключом
	Iterator begin();
	// запрос «неустановленного» прямого итератора
	Iterator end();
	// запрос обратного итератора, установленного на узел дерева с максимальным ключом
	RevIterator rbegin();
	// запрос «неустановленного» обратного итератора
	RevIterator rend();

	// -------------- Доп методы --------------
	void printNode(Node*);
	void deleteNode(Node*);
	void copyNode(Node*);
	Node* insertRoot(Node*, K, V, bool&);
	Node* L(Node*);
	Node* R(Node*);
	Node* joinNodes(Node*, Node*);
	int countNodes();
	void clearCount();

	// -------------- для теста, потом удалю --
	void printVertical(Node*, int);

private:
	Node* root;
	int size;
	int count;
};
