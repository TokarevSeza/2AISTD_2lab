#pragma once
#include"Stack.h"
#include "Stack.cpp"
using namespace std;

template <class Key, class Value>
class RBTree
{
private:
	class Node
	{
	public:

		Node* parent;
		Node* left;
		Node* right;
		Key key;
		Value value;
		bool color; //black=true , red=false
		Node(Key key, Value value, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, bool color = 0) {
			this->key = key;
			this->value = value;
			this->left = left;
			this->right = right;
			this->parent = parent;
			this->color = color;
		}
		~Node() {};
	};

	class DFT_Iterator
	{
	private:
		Stack<Node*> stack;
		Node* curr;
		Node* zero;
	public:
		DFT_Iterator(Node* Current, Node* nill)
		{
			curr = Current;
			zero = nill;
		};
		Node* next() {
			Node* temp = curr;
			if (curr->right != zero) //add right tree to stack
				stack.push_el(curr->right);
			if (curr->left != zero) //go left
			{
				curr = curr->left;
			}
			else {
				if (!stack.isEmpty()) // if can't
					curr = stack.pop();
				else curr = zero;
			}
			return temp;
		};
		bool Next()
		{
			if (curr != zero)
				return true;
			return false;
		};
		~DFT_Iterator() {}
	};

	Node* root;
	Node* zero;
	int size;
	void Left_Rotate(Node*); //movement on the left side
	void Right_Rotate(Node*); // movement on the right side
	void Fix(Node*); // fix after input

public:

	Key* Get_Keys(); //return all keys
	Value* Get_Values(); //return values
	Value Find_Element(Key); //find element by key
	void Insert(Key, Value); //add element with key and value
	void Remove(Key); //remove element by key
	void Clear(); //clear all
	void Print(); //print in console
	RBTree()
	{
		size = 0;
		zero = new Node(0, 0, nullptr, nullptr, nullptr, 1);
		root = zero;
	}
	~RBTree()
	{
		Clear();
		delete root;
	}
	int Size()
	{
		return size;
	}
};

template<class Key, class Value>
void RBTree<Key, Value>::Insert(Key key, Value value)
{
	Node* current = root, * parent;
	bool Right_Move;
	size++;
	if (root == zero)//Tree is empty 
	{
		root = new Node(key, value, zero, zero, zero, 1);
		return;
	}
	parent = current;
	while (current != zero)
	{
		parent = current;
		if (key > current->key) //right
		{
			current = current->right; Right_Move = true;
		} //
		else {//left
			current = current->left; Right_Move = false;
		}
	}
	if (Right_Move)
	{
		parent->right = new Node(key, value, zero, zero, parent, 0);
		Fix(parent->right);
	}
	else {
		parent->left = new Node(key, value, zero, zero, parent, 0);
		Fix(parent->left);
	}
}

template<class Key, class Value>
void RBTree<Key, Value>::Remove(Key key)
{
	if (root == zero)
		cout << "Tree is empty";
	Node* to_delete = root;
	Node* x, * min;
	bool Color = to_delete->color;
	while (to_delete->key != key)
	{
		if (key > to_delete->key)
			to_delete = to_delete->right;
		else to_delete = to_delete->left;
		if (to_delete == zero)
			cout << "There is no such element ";
	}
	if (to_delete->left == zero)
	{
		x = to_delete->right;
		if (to_delete->parent == zero)
			root = x;
		else if (to_delete->parent->left == to_delete)
			to_delete->parent->left = x;
		else to_delete->parent->right = x;
		x->parent = to_delete->parent;
	}
	else
		if (to_delete->right == zero)
		{
			x = to_delete->left;
			if (to_delete->parent == zero) root = x;
			else
				if (to_delete->parent->left == to_delete)
					to_delete->parent->left = x;
				else to_delete->parent->right = x;
			x->parent = to_delete->parent;
		}
		else
		{
			Node* temp = to_delete;
			min = to_delete->right;
			while (min->left != zero)
				min = min->left;
			Color = min->color;
			to_delete = min;
			x = to_delete->right;
			if (to_delete->parent == temp)
				x->parent = to_delete;
			else
			{
				if (to_delete->parent == zero) {
					root = x;
					to_delete->right->parent = zero;
				}
				else
					if (to_delete->parent->right == to_delete)
						to_delete->parent->right = x;
					else to_delete->parent->left = x;
				x->parent = to_delete->parent;
				to_delete->right = temp->right;
				to_delete->right->parent = to_delete;
			}
			if (temp->parent == zero)
				root = to_delete;
			else
				if (temp == temp->parent->left)
					temp->parent->left = to_delete;
				else temp->parent->right = to_delete;
			to_delete->parent = temp->parent;
			to_delete->left = temp->left;
			to_delete->left->parent = to_delete;
			to_delete->color = temp->color;
		}
	size--;
}

template<class Key, class Value>
Value RBTree<Key, Value>::Find_Element(Key findKey)
{
	Node* current = root;
	while (current->key != findKey) // find key to remove
	{
		if (findKey > current->key)
			current = current->right;
		else current = current->left;
		if (current == zero)
			cout << "There is no such element ";
	}
	return current->value;
}

template<class Key, class Value>
void RBTree<Key, Value>::Clear()
{
	while (root != zero) {
		Remove(root->key);
		cout << endl;
		Print();
	}
}

template<class Key, class Value>
Key* RBTree<Key, Value>::Get_Keys()
{
	Key* Array = new Key[size];
	int i = 0;
	DFT_Iterator iter(root, zero);
	while (iter.Next())
	{
		Array[i] = iter.next()->key;
		i++;
	}
	return Array;
}

template<class Key, class Value>
Value* RBTree<Key, Value>::Get_Values() {
	Value* arr = new Value[size]; int i = 0;
	DFT_Iterator iter(root, zero);
	while (iter.Next())
	{
		arr[i] = iter.next()->value; i++;
	}
	return arr;
}

template<class Key, class Value>
void RBTree<Key, Value>::Print() {
	DFT_Iterator iter(root, zero);
	Node* current;
	while (iter.Next())
	{
		current = iter.next();
		cout << "\nKey:" << current->key;
		cout << "Elements:" << current->left->key << " " << current->right->key;
	}
}

template<class Key, class Value>
void RBTree<Key, Value>::Left_Rotate(Node* CurX) {
	Node* CurY = CurX->right;
	if (CurX->right == zero)
		return;
	if (CurY->left != zero)
	{
		CurX->right = CurY->left;
		CurY->left->parent = CurX;
	}
	else CurX->right = zero;

	if (CurY != zero)
		CurY->parent = CurX->parent;
	if (CurX->parent != zero)
	{
		if (CurX == CurX->parent->left)
			CurX->parent->left = CurY;
		else
			CurX->parent->right = CurY;
	}
	else
	{
		CurY->parent = zero;
		root = CurY;
	}
	CurY->left = CurX;
	if (CurX != zero)
		CurX->parent = CurY;
}

template<class Key, class Value>
void RBTree<Key, Value>::Right_Rotate(Node* CurX) {
	Node* CurY = CurX->left;
	CurX->left = CurY->right;
	if (CurY->right != zero)
		CurY->right->parent = CurX;
	if (CurY != zero)
		CurY->parent = CurX->parent;
	if (CurX->parent != zero) {
		if (CurX == CurX->parent->right)
			CurX->parent->right = CurY;
		else
			CurX->parent->left = CurY;
	}
	else
	{
		root = CurY;
	}
	CurY->right = CurX;
	if (CurX != zero)
		CurX->parent = CurY;
}

template<class Key, class Value>
void RBTree<Key, Value>::Fix(Node* newNode) {
	Node* parent, * Grand_Parent;
	while (newNode->parent->color == 0)
	{
		parent = newNode->parent;
		Grand_Parent = parent->parent;
		if (Grand_Parent->left == parent)
		{
			if (Grand_Parent->right->color == 0)
			{
				Grand_Parent->right->color = 1;
				Grand_Parent->left->color = 1;
				Grand_Parent->color = 0;
				newNode = Grand_Parent;
			}
			else
			{
				if (parent->right == newNode)
				{
					newNode = parent;
					Left_Rotate(newNode);
				}
				newNode->parent->color = 1;
				newNode->parent->parent->color = 0;
				Right_Rotate(newNode->parent->parent);
			}
		}
		else
		{
			if (Grand_Parent->left->color == 0)
			{
				Grand_Parent->right->color = 1;
				Grand_Parent->left->color = 1;
				Grand_Parent->color = 0;
				newNode = Grand_Parent;
			}
			else
			{
				if (parent->left == newNode)
				{
					newNode = parent;
					Right_Rotate(newNode);
				}
				newNode->parent->color = 1;
				newNode->parent->parent->color = 0;
				Left_Rotate(newNode->parent->parent);
			}
		}
	}
	root->color = 1;
}

