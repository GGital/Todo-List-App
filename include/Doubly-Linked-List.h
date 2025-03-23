#pragma once
#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *prev;
};

class DoublyLinkedList
{
public:
    Node *head;
    DoublyLinkedList()
    {
        head = NULL;
    }

    void insertAtEnd(int data);

    void insertAtBeginning(int data);

    void deleteAtEnd();

    void deleteAtBeginning();

    void display();
};