#pragma once
#include <iostream>

template <class T>
class Stack
{
private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node* prev;
        Node(T data = 0, Node* prev = NULL, Node* next = NULL)
        {
            this->data = data;
            this->prev = prev;
            this->next = next;
        };
        ~Node()
        {  }
    };
    Node* head; //head list
    Node* tail;  //tail list
    size_t size;  //list size
public:
    Stack(Node* head = NULL, Node* tail = NULL) {
        this->head = head;
        this->tail = tail;
        size = 0;
    };
    void push_el(T); // add element to end
    void Clear(); // clear list
    size_t Size(); // get list size
    T get_last(); // get last element
    T pop(); // delete last element
    bool isEmpty(); // test for emptiness
    ~Stack()
    {
        if (head != NULL)
        {
            while (head != NULL && head->next != NULL) //while we can go next
            {
                head = head->next;
                delete head->prev;
            }
            size = 0;
            if (head != NULL)
                delete head;
        }
    };
};
