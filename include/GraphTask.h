#pragma once
#include <iostream>
#include <string>
#include <Task.h>
#include <ctime>
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
            task[i] = Task();
            task[i].taskID = -1; // Initialize task IDs
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
        // cout << userCollections.taskCount << endl;
        for (int i = 0; i < userCollections.taskCount; i++)
        {
            Task *temp = userCollections.tasks[i]; // Get the task from UserCollections
            task[temp->taskID] = *temp;
            AddVertex(userCollections.tasks[i]->taskID); // Add vertex for each task
            // cout << "Task ID: " << userCollections.tasks[i]->taskID << endl; // Print task ID
        }
    }

    void BuildGraph(UserCollections &userCollections)
    {
        SyncwithUserCollections(userCollections); // Sync tasks with UserCollections

        // Get the current date
        time_t now = time(0);
        tm *currentDate = localtime(&now);

        for (int i = 0; i < 1005; i++)
        {
            for (int j = 0; j < 1005; j++)
            {
                if (i == j)
                    continue; // Skip self-loops

                Task a = task[i]; // Get the task at index i
                Task b = task[j];

                if (a.status == "Completed" || b.status == "Completed")
                    continue; // Skip if either task is completed

                if (a.taskID == -1 || b.taskID == -1)
                    continue; // Skip if task ID is -1 (not assigned)

                // Calculate days until due date for task a and task b
                int daysUntilDueA = (a.dueDate.tm_year - currentDate->tm_year) * 365 +
                                    (a.dueDate.tm_mon - currentDate->tm_mon) * 30 +
                                    (a.dueDate.tm_mday - currentDate->tm_mday);

                int daysUntilDueB = (b.dueDate.tm_year - currentDate->tm_year) * 365 +
                                    (b.dueDate.tm_mon - currentDate->tm_mon) * 30 +
                                    (b.dueDate.tm_mday - currentDate->tm_mday);

                // Adjust priority dynamically based on due date proximity
                int adjustedPriorityA = priorityToInt(a.priority);
                int adjustedPriorityB = priorityToInt(b.priority);

                if (daysUntilDueA <= 2) // Very close to the deadline
                    adjustedPriorityA += 2;
                if (daysUntilDueB <= 2) // Very close to the deadline
                    adjustedPriorityB += 2;

                if (daysUntilDueA <= 1)
                    adjustedPriorityA += 3;
                if (daysUntilDueB <= 1)
                    adjustedPriorityB += 3;

                if (adjustedPriorityA > adjustedPriorityB)
                {
                    AddEdge(a.taskID, b.taskID);
                }
                else if (adjustedPriorityA == adjustedPriorityB)
                {
                    if (earlierDueDate(a, b))
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
            inDegree[i] = 0; // Initialize in-degrees to 0
        }
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
        /*for (int i = 0; i < 5; i++)
        {
            cout << "In-degree of task " << i << ": " << inDegree[i] << endl; // Print in-degrees for debugging
        }*/
        Queue<int> *q = new Queue<int>(1005);     // Queue to store vertices with in-degree 0
        TopologicalOrder = new Queue<Task>(1005); // Queue to store the topological order of tasks
        for (int i = 0; i < 1005; i++)
        {
            if (inDegree[i] == 0 && edgeList[i] != nullptr)
            {
                // cout << "Task ID: " << i << endl; // Print task ID with in-degree 0
                q->enqueue(i); // Enqueue vertices with in-degree 0
            }
        }
        // cout << q.size << endl; // Print the size of the queue
        while (!q->isEmpty())
        {
            int u = q->dequeue(); // Dequeue a vertex
            // cout << "Processing task: " << task[u].name << endl; // Print the task being processed
            // cout << "Size of queue: " << q->size << endl;        // Print the size of the queue
            TopologicalOrder->enqueue(task[u]); // Add it to the result queue
            DoublyLinkedList<Task> *list = edgeList[u];
            if (list != nullptr)
            {
                // cout << u << endl;
                DoublyLinkedList<Task>::Node *current = list->head;
                while (current != nullptr)
                {
                    inDegree[current->data.taskID]--; // Decrease in-degree of adjacent vertices
                    if (inDegree[current->data.taskID] == 0 && edgeList[current->data.taskID] != nullptr)
                    {
                        q->enqueue(current->data.taskID); // Enqueue vertices with in-degree 0
                    }
                    current = current->next;
                }
            }
        }
    }
};