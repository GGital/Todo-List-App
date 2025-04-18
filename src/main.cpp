#include <iostream>
#include <example.h>
#include "Doubly-Linked-List.h"
#include "Min-Priority-Queue.h"
#include "Max-Priority-Queue.h"
#include "File_Management.h"
#include "Task.h"
using namespace std;

int main()
{
    Example example;
    example.Greet();
    example.Farewell();

    DoublyLinkedList<int> dll;
    dll.insertAtEnd(10);
    dll.insertAtEnd(30);
    dll.display();

    DoublyLinkedList<double> dll2;
    dll2.insertAtEnd(10.5);
    dll2.insertAtEnd(30.5);
    dll2.display();

    MinPriorityQueue<int> minQueue;
    minQueue.insert(10, 1);
    minQueue.insert(20, 2);
    minQueue.insert(30, 3);

    MaxPriorityQueue<int> maxQueue;
    maxQueue.insert(10, 1);
    maxQueue.insert(20, 2);
    maxQueue.insert(30, 3);

    Task task1("Task 1", "Description 1", "In Progress", "High");
    WriteFile("./output/output.txt");
    dll.display();
    dll2.display();
    cout << minQueue.pop() << endl;
    cout << maxQueue.pop() << endl;
    cout << task1 << endl;
    CloseFile();

    cout << task1 << endl;

    return 0;
}