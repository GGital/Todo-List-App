#pragma once
#include <iostream>
#include <string>
#include <Task.h>
#include <UserCollections.h>
#include <Doubly-Linked-List.h>
#include <Queue.h>
using namespace std;

class GraphTask
{
public:
    DoublyLinkedList<Task> *edgeList[1005]; // Array of doubly linked lists to represent the graph
    int vertexCount;                        // Number of vertices in the graph
    int edgeCount;                          // Number of edges in the graph
    Task task[1005];
    Queue<Task> *TopologicalOrder; // Queue to store the topological order of tasks

    GraphTask()
    {
        vertexCount = 0;
        edgeCount = 0;
        for (int i = 0; i < 1005; i++)
        {
            edgeList[i] = nullptr; // Initialize the array of doubly linked lists
        }
    }
    ~GraphTask()
    {
        for (int i = 0; i < 1005; i++)
        {
            delete edgeList[i]; // Clean up the doubly linked lists
        }
    }

    int priorityToInt(string priority)
    {
        if (priority == "Low")
            return 1;
        else if (priority == "Medium")
            return 2;
        else if (priority == "High")
            return 3;
        else
            return 0; // Default case
    }

    bool earlierDueDate(Task &task1, Task &task2)
    {
        if (task1.dueDate.tm_year < task2.dueDate.tm_year)
            return true;
        else if (task1.dueDate.tm_year == task2.dueDate.tm_year && task1.dueDate.tm_mon < task2.dueDate.tm_mon)
            return true;
        else if (task1.dueDate.tm_year == task2.dueDate.tm_year && task1.dueDate.tm_mon == task2.dueDate.tm_mon && task1.dueDate.tm_mday < task2.dueDate.tm_mday)
            return true;
        return false;
    }

    void SyncwithUserCollections(UserCollections &userCollections)
    {
        for (int i = 0; i < userCollections.taskCount; i++)
        {
            task[i] = *userCollections.tasks[i];        // Copy tasks from UserCollections to the graph
            edgeList[i] = new DoublyLinkedList<Task>(); // Initialize the doubly linked list for each task
        }
    }

    void BuildGraph(UserCollections &userCollections)
    {
        SyncwithUserCollections(userCollections); // Sync tasks with UserCollections
        for (int i = 0; i < userCollections.taskCount; i++)
        {
            for (int j = 0; j < userCollections.taskCount; j++)
            {
                if (i == j)
                    continue; // Skip self-loops
                Task a = *userCollections.tasks[i];
                Task b = *userCollections.tasks[j];

                if (priorityToInt(a.priority) > priorityToInt(b.priority))
                {
                    AddEdge(a.taskID, b.taskID);
                }
                else if (priorityToInt(a.priority) == priorityToInt(b.priority))
                {
                    if (earlierDueDate(a, b))
                    {
                        AddEdge(a.taskID, b.taskID);
                    }
                    else if (a.category == b.category && a.status != b.status)
                    {
                        AddEdge(a.taskID, b.taskID);
                    }
                }
            }
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
        AddVertex(TaskIDsrc);                               // Ensure the source vertex exists
        AddVertex(TaskIDdest);                              // Ensure the destination vertex exists
        edgeList[TaskIDsrc]->insertAtEnd(task[TaskIDdest]); // Add the destination task to the source vertex's list
        edgeCount++;
    }

    void TopologicalSort()
    {
        int *inDegree = new int[1005](); // Array to store in-degrees of vertices
        for (int i = 0; i < 1005; i++)
        {
            DoublyLinkedList<Task> *list = edgeList[i];
            if (list != nullptr)
            {
                DoublyLinkedList<Task>::Node *current = list->head;
                while (current != nullptr)
                {
                    inDegree[current->data.taskID]++;
                    current = current->next;
                }
            }
        }
        Queue<int> *q = new Queue<int>(1005);     // Queue to store vertices with in-degree 0
        TopologicalOrder = new Queue<Task>(1005); // Queue to store the topological order of tasks
        for (int i = 0; i < 1005; i++)
        {
            if (inDegree[i] == 0 && edgeList[i] != nullptr)
            {
                q->enqueue(i); // Enqueue vertices with in-degree 0
            }
        }
        // cout << q.size << endl; // Print the size of the queue
        while (!q->isEmpty())
        {
            int u = q->dequeue();                                // Dequeue a vertex
            cout << "Processing task: " << task[u].name << endl; // Print the task being processed
            cout << "Size of queue: " << q->size << endl;        // Print the size of the queue
            TopologicalOrder->enqueue(task[u]);                  // Add it to the result queue
            DoublyLinkedList<Task> *list = edgeList[u];
            if (list != nullptr)
            {
                // cout << u << endl;
                DoublyLinkedList<Task>::Node *current = list->head;
                while (current != nullptr)
                {
                    // cout << "Check2" << endl;
                    inDegree[current->data.taskID]--; // Decrease in-degree of adjacent vertices
                    if (inDegree[current->data.taskID] == 0 && edgeList[current->data.taskID] != nullptr)
                    {
                        q->enqueue(current->data.taskID); // Enqueue vertices with in-degree 0
                    }
                    current = current->next;
                }
            }
        }
        // delete[] inDegree;                             // Clean up the in-degree array
        // delete q;                                      // Clean up the queue
        cout << "Check3" << endl;
        cout << "Topological Sort completed." << endl; // Print completion message
    }
};