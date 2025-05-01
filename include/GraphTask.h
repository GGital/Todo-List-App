#pragma once
#include <iostream>
#include <string>
#include <Task.h>
#include <Doubly-Linked-List.h>
#include <Queue.h>
using namespace std;

class GraphTask
{
public:
    DoublyLinkedList<Task> *edgeList[1000]; // Array of doubly linked lists to represent the graph
    int vertexCount;                        // Number of vertices in the graph
    int edgeCount;                          // Number of edges in the graph
    Queue<int> queue;                       // Queue for BFS or DFS traversal

    GraphTask()
    {
        vertexCount = 0;
        edgeCount = 0;
        for (int i = 0; i < 1000; i++)
        {
            edgeList[i] = nullptr; // Initialize the array of doubly linked lists
        }
    }
    ~GraphTask()
    {
        for (int i = 0; i < vertexCount; i++)
        {
            delete edgeList[i]; // Clean up the doubly linked lists
        }
    }

    void AddVertex(int TaskID)
    {
        if (edgeList[TaskID] != nullptr)
        {
            // cout << "Vertex already exists." << endl;
            return;
        }
        edgeList[TaskID] = new DoublyLinkedList<Task>(); // Create a new doubly linked list for the vertex
        vertexCount++;                                   // Increment the vertex count
    }

    void AddEdge(int TaskIDsrc, int TaskIDdest)
    {
        AddVertex(TaskIDsrc);  // Ensure the source vertex exists
        AddVertex(TaskIDdest); // Ensure the destination vertex exists
        edgeList[TaskIDsrc]->insertAtEnd(task);
        edgeCount++;
    }
    void TopologicalSort()
    {
        int *inDegree = new int[vertexCount](); // Array to store in-degrees of vertices
        for (int i = 0; i < vertexCount; i++)
        {
            DoublyLinkedList<Task> *list = edgeList[i];
            if (list != nullptr)
            {
                Node<Task> *current = list->head;
                while (current != nullptr)
                {
                    inDegree[current->data.taskID]++;
                    current = current->next;
                }
            }
        }
        for (int i = 0; i < vertexCount; i++)
        {
            if (inDegree[i] == 0)
            {
                queue.enqueue(i); // Enqueue vertices with in-degree 0
            }
        }
    }
};