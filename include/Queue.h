#pragma once
#include <iostream>
#include <string>
#include <Task.h>
#include <Doubly-Linked-List.h>
using namespace std;

template <typename T>
class Queue
{
public:
    DoublyLinkedList<T> list;
    int capacity;
    int size;
    int front;
    int rear;
    Queue(int c) : capacity(c)
    {
        list = DoublyLinkedList<T>();
        size = 0;
        front = 0;
        rear = -1;
    }

    ~Queue()
    {
        delete &list;
    }

    void enqueue(T data)
    {
        if (size == capacity)
        {
            // cout << "Queue is full" << endl;
            return;
        }
        list.insertAtEnd(data);
        size++;
        rear = (rear + 1) % capacity;
    }

    T dequeue()
    {
        if (size <= 0)
        {
            // cout << "Queue is empty" << endl;
            return T(); // Return default value of T
        }
        T data = list.head->data;
        list.head = list.head->next;
        size--;
        front = (front + 1) % capacity;
        return data;
    }

    T peek()
    {
        if (size <= 0)
        {
            // cout << "Queue is empty" << endl;
            return T(); // Return default value of T
        }
        return list.head->data;
    }

    bool isEmpty()
    {
        return size <= 0;
    }

    bool isFull()
    {
        return size == capacity;
    }

    void display()
    {
        list.display();
    }
};