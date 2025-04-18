#include <iostream>
#include <example.h>
#include <File_Management.h>
#include "Doubly-Linked-List.h"
#include "Min-Priority-Queue.h"
#include "Max-Priority-Queue.h"
#include "Task.h"
#include "LoginSystem.h"
using namespace std;

int main()
{
    FileManagement fileManager;
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

    DoublyLinkedList<Task> taskList;
    taskList.insertAtEnd(Task("Task 1", "Description 1", "In Progress", "High"));
    taskList.insertAtEnd(Task("Task 2", "Description 2", "Completed", "Medium"));

    fileManager.WriteFile("./output/output.txt");
    taskList.display();
    fileManager.CloseFile();

    LoginSystem loginSystem;
    loginSystem.RegisterUser("Gital", "Madiwa");
    cout << loginSystem.LoginUser("Gital", "Madiwa") << endl;
    return 0;
}