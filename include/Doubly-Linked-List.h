#pragma once
#include <iostream>
#include "Task.h"
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node<T> *prev;
};
template <typename T>
class DoublyLinkedList
{
public:
    Node<T> *head;
    DoublyLinkedList<T>() : head(NULL) {}

    void insertAtEnd(T data)
    {
        Node<T> *newNode = new Node<T>();
        newNode->data = data;
        newNode->next = NULL;
        if (head == NULL)
        {
            newNode->prev = NULL;
            head = newNode;
        }
        else
        {
            Node<T> *last = head;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = newNode;
            newNode->prev = last;
        }
    }

    void insertAtBeginning(T data)
    {
        Node<T> *newNode = new Node<T>();
        newNode->data = data;
        newNode->prev = NULL;
        if (head == NULL)
        {
            newNode->next = NULL;
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void deleteAtEnd()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node<T> *last = head;
        while (last->next != NULL)
        {
            last = last->next;
        }
        if (last->prev == NULL)
        {
            head = NULL;
        }
        else
        {
            last->prev->next = NULL;
        }
        delete last;
    }

    void deleteAtBeginning()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node<T> *temp = head;
        head = head->next;
        head->prev = NULL;
        delete temp;
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node<T> *current = head;
        while (current != NULL)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};
