#include "Stack.h"
using namespace std;

template <typename T>
void Stack<T>::push_el(T add)
{
	if (size == 0) //if list is empty
	{
		head = new Node(add); //create head
		tail = head;
	}
	else
	{
		Node* current = new Node(add);
		current->prev = tail;
		tail->next = current;
		tail = current;  //set new tail
	}
	size++;
}

template <typename T>
T Stack<T>::pop()
{
	T conter = nullptr;
	if (size == 1)
	{
		size = 0;
		conter = tail->data;
		head = NULL;
		tail = NULL;

	}
	else if (size > 1) //if list is not empty
	{
		conter = tail->data;
		tail = tail->prev; //set new tail
		delete tail->next;
		tail->next = NULL;
		size--;
	}

	return conter;
}

template <typename T>
void Stack<T>::Clear()
{
	if (head != NULL)
	{
		while (head->next != NULL)  //delete all elements
		{
			head = head->next;
			delete head->prev;
		}
		size = 0;
		head = NULL;
		tail = NULL;
	}
}

template <typename T>
size_t Stack<T>::Size()
{
	return size;
}

template <class T>
T Stack<T>::get_last() {
	return tail->data;
}

template <typename T>
bool Stack<T>::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}