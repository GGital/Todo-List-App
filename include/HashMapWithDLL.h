#pragma once
#include <iostream>
#include <string>
#include <Task.h>
#include <Doubly-Linked-List.h>
using namespace std;

template <typename T, typename U>
class HashMapDLL
{
public:
    DoublyLinkedList<U> *table; // Array of doubly linked lists
    int size;                   // Size of the hash table
    T *keyCheck;                // Array of keys
    HashMapDLL(int s) : size(s)
    {
        table = new DoublyLinkedList<U>[size]; // Initialize the array of doubly linked lists
        keyCheck = new T[size];                // Initialize the array of keys
        for (int i = 0; i < size; i++)
        {
            keyCheck[i] = T(); // Initialize keys to default value
        }
    }

    ~HashMapDLL()
    {
        delete[] table;    // Clean up the array of doubly linked lists
        delete[] keyCheck; // Clean up the array of keys
    }

    int hashFunction(T key)
    {
        if constexpr (is_same<T, string>::value)
        {
            int hash = 0;
            for (char c : key)
            {
                hash += c;
                hash *= 31;
                hash -= 7;
                hash %= size;
            }
            while (keyCheck[hash] != T() && keyCheck[hash] != key) // Check for collision
            {
                hash = (hash + 1) % size; // Linear probing for collision resolution
            }
            return hash % size;
        }
        else
        {
            int hash = (key * 2 + doubleHashFunction(key)) % size;
            while (keyCheck[hash] != T() && keyCheck[hash] != key) // Check for collision
            {
                hash = (hash + 1) % size; // Linear probing for collision resolution
            }
            return hash % size;
        }
    }

    int doubleHashFunction(T key)
    {
        if constexpr (is_same<T, string>::value)
        {
            int hash = 0;
            for (char c : key)
            {
                hash = (hash * 17 + c) % size;
            }
            return hash;
        }
        else
        {
            return (key * 103 / size) % size;
        }
    }

    void insert(T key, U value)
    {
        int index = hashFunction(key);
        table[index].insertAtEnd(value);
    }

    DoublyLinkedList<U> *getList(T key)
    {
        int index = hashFunction(key);
        return &table[index];
    }
};