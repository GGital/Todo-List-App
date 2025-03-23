#include <iostream>
#include "Doubly-Linked-List.h"
using namespace std;

void DoublyLinkedList::insertAtEnd(int data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = NULL;
    if (head == NULL)
    {
        newNode->prev = NULL;
        head = newNode;
    }
    else
    {
        Node *last = head;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = newNode;
        newNode->prev = last;
    }
}

void DoublyLinkedList::insertAtBeginning(int data)
{
    Node *newNode = new Node();
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

void DoublyLinkedList::deleteAtEnd()
{
    if (head == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    Node *last = head;
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

void DoublyLinkedList::deleteAtBeginning()
{
    if (head == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    Node *temp = head;
    head = head->next;
    head->prev = NULL;
    delete temp;
}

void DoublyLinkedList::display()
{
    if (head == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    Node *current = head;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
