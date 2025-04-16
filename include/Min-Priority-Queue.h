#pragma once
#include <iostream>
#include <string>
#include <Task.h>
using namespace std;

template <typename T>
class MinPriorityQueue
{
public:
    class Node
    {
    public:
        T data;
        int priority;
        Node *next;
        Node *prev;
        Node(T data, int priority) : data(data), priority(priority), next(nullptr), prev(nullptr) {}
    };
    Node *head;
    Node *tail;

    // Constructor to initialize the queue
    MinPriorityQueue() : head(nullptr), tail(nullptr) {}

    void insert(T data, int priority)
    {
        Node *newNode = new Node(data, priority);
        if (head == nullptr || head->priority > priority)
        {
            newNode->next = head;
            if (head != nullptr)
                head->prev = newNode;
            head = newNode;
            if (tail == nullptr)
                tail = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr && current->next->priority <= priority)
            {
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next != nullptr)
                current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
            if (newNode->next == nullptr)
                tail = newNode;
        }
    }
    T pop()
    {
        if (head == nullptr)
        {

            cout << "Queue is empty" << endl;
            return T(); // Return default value of T
        }
        Node *minNode = head;
        T minData = minNode->data;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete minNode;
        return minData;
    }
    bool isEmpty()
    {
        return head == nullptr;
    }
};
