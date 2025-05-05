#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MaxPriorityQueue
{
private:
    pair<T, int> *heap; // Dynamically allocated array for the heap
    int capacity;       // Maximum capacity of the heap
    int size;           // Current number of elements in the heap

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
        auto *newHeap = new pair<T, int>[newCap];
        for (int i = 0; i < size; ++i)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCap;
    }

    void heapifyUp(int idx)
    {
        while (idx > 0)
        {
            int p = parent(idx);
            if (heap[p].second >= heap[idx].second)
                break;
            swap(heap[p], heap[idx]);
            idx = p;
        }
    }

    void heapifyDown(int idx)
    {
        while (true)
        {
            int l = leftChild(idx), r = rightChild(idx), largest = idx;
            if (l < size && heap[l].second > heap[largest].second)
                largest = l;
            if (r < size && heap[r].second > heap[largest].second)
                largest = r;
            if (largest == idx)
                break;
            swap(heap[idx], heap[largest]);
            idx = largest;
        }
    }

public:
    // Constructor to initialize the priority queue
    MaxPriorityQueue(int initialCapacity = 1005)
    {
        capacity = initialCapacity;
        size = 0;
        heap = new pair<T, int>[capacity];
    }

    // Destructor to clean up the dynamically allocated memory
    ~MaxPriorityQueue()
    {
        // delete[] heap;
    }

    // Insert a new element with a given priority
    void insert(const T &val, int prio)
    {
        if (size == capacity)
            resize();
        heap[size] = {val, prio};
        ++size;
        heapifyUp(size - 1); // Fix is here
    }

    T pop()
    {
        if (size == 0)
            throw runtime_error("pop() on empty queue");
        T ret = heap[0].first;
        heap[0] = heap[size - 1];
        --size;
        if (size > 0)
            heapifyDown(0);
        return ret;
    }

    T peek() const
    {
        if (size == 0)
            throw runtime_error("peek() on empty queue");
        return heap[0].first;
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
