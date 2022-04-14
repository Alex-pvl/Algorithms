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
		// �������� ������� �� ������ � ������ � ������ �������� ����
		V& operator*();
		// �������� �������� � ���������� �� ����� ���� � ������
		Iterator operator++();
		// �������� ��������� ���������� ����������
		bool operator==(Iterator&);
		// �������� ����������� ���������� ����������
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
		// �������� ������� �� ������ � ������ � ������ �������� ����
		V& operator*();
		// �������� �������� � ����������� �� ����� ���� � ������
		RevIterator operator++();
		// �������� ��������� ���������� ����������
		bool operator==(RevIterator&);
		// �������� ����������� ���������� ����������
		bool operator!=(RevIterator&);
		Node* nextNode(Node*);
	};
	friend class Node;
	
	// �����������
	BST();
	// ����������� �����������
	BST(const BST&);
	// ����������
	~BST();
	// ����� ������� ������
	int getSize();
	// ������� ������
	void clear();
	// �������� ������ �� �������
	bool isEmpty();
	// ��������� ������ � �������� ������
	bool put(K, V);
	// �������� ������ � �������� ������
	bool remove(K);
	// ������ �� ������/������ � ������ �� �����
	V& get(K);
	// ������������ ������ ������ � ������ � ������� ������ ����� �� �����
	void print();
	// ����������� ���� BST-��������
	BST& join(BST&);
	// ������ ������� ���������, �������������� �� ���� ������ � ����������� ������
	Iterator begin();
	// ������ ����������������� ������� ���������
	Iterator end();
	// ������ ��������� ���������, �������������� �� ���� ������ � ������������ ������
	RevIterator rbegin();
	// ������ ����������������� ��������� ���������
	RevIterator rend();

	// -------------- ��� ������ --------------
	void printNode(Node*);
	void deleteNode(Node*);
	void copyNode(Node*);
	Node* insertRoot(Node*, K, V, bool&);
	Node* L(Node*);
	Node* R(Node*);
	Node* joinNodes(Node*, Node*);
	int countNodes();
	void clearCount();

	// -------------- ��� �����, ����� ����� --
	void printVertical(Node*, int);

private:
	Node* root;
	int size;
	int count;
};
