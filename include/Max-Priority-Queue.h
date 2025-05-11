#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MaxPriorityQueue
{
private:
    T *heap;      // Array to store the heap elements
    int capacity; // Maximum capacity of the heap
    int size;     // Current number of elements in the heap

    // Helper function to get the parent index
    int parent(int i) { return (i - 1) / 2; }

    // Helper function to get the left child index
    int leftChild(int i) { return 2 * i + 1; }

    // Helper function to get the right child index
    int rightChild(int i) { return 2 * i + 2; }

    // Helper function to resize the heap when it exceeds capacity
    void resize()
    {
        int newCap = capacity * 2;
        auto *newHeap = new T[newCap];
        for (int i = 0; i < size; ++i)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCap;
    }

public:
    // Constructor to initialize the priority queue
    MaxPriorityQueue(int initialCapacity = 1005)
    {
        capacity = initialCapacity;
        size = 0;
        heap = new T[capacity];
    }

    // Destructor to clean up the dynamically allocated memory
    ~MaxPriorityQueue()
    {
        // delete[] heap;
    }

    // Insert a new element with a given priority
    void insert(const T &val)
    {
        if (size == capacity)
            resize();
        heap[size] = val;
        int i = size;
        while (i > 0)
        {
            int p = parent(i);
            if (heap[p] > heap[i])
                break;
            swap(heap[p], heap[i]);
            i = p;
        }
        ++size;
    }

    T pop()
    {
        if (size == 0)
            throw runtime_error("pop() on empty queue");
        T ret = heap[0];
        heap[0] = heap[size - 1];
        --size;
        int i = 0;
        while (true)
        {
            int left = leftChild(i);
            int right = rightChild(i);
            int largest = i;

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest == i)
                break;

            swap(heap[i], heap[largest]);
            i = largest;
        }
        return ret;
    }

    T peek() const
    {
        if (size == 0)
            throw runtime_error("peek() on empty queue");
        return heap[0];
    }

    bool isEmpty() const { return size == 0; }
    void clear() { size = 0; }

    // Get the array of sorted elements
    T *getSortedArray()
    {
        int tempSize = size; // store before modifying
        T *sortedArray = new T[tempSize];
        for (int i = 0; i < tempSize; i++)
        {
            sortedArray[i] = pop();
        }
        return sortedArray;
    }
};
