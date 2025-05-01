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
    Queue(int c) : capacity(s)
    {
        list = DoublyLinkedList<T>();
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

    void dequeue()
    {
        if (size == 0)
        {
            // cout << "Queue is empty" << endl;
            return;
        }
        list.deleteAtStart();
        size--;
        front = (front + 1) % capacity;
    }

    T peek()
    {
        if (size == 0)
        {
            // cout << "Queue is empty" << endl;
            return T(); // Return default value of T
        }
        return list.head->data;
    }
}