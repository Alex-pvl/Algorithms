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
	};

	class RevIterator {
		BST* tree;
		Node* cur;
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
	};

	friend class Node;
	friend class Iterator;
	friend class RevIterator;
	
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
	BST join(BST&);
	// ������ ������� ���������, �������������� �� ���� ������ � ����������� ������
	Iterator begin();
	// ������ ����������������� ������� ���������
	Iterator end();
	// ������ ��������� ���������, �������������� �� ���� ������ � ������������ ������
	RevIterator rbegin();
	// ������ ����������������� ��������� ���������
	RevIterator rend();

private:
	Node* root;
	int size;
};

