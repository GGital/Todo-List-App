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

    Task task1("Task 1", "Description 1", "In Progress", "High");
    fileManager.WriteFile("./output/output.txt");
    dll.display();
    dll2.display();
    cout << minQueue.pop() << endl;
    cout << maxQueue.pop() << endl;
    cout << task1 << endl;
    fileManager.CloseFile();
    fileManager.WriteFile("./output/output2.txt");
    dll.display();
    dll2.display();
    fileManager.CloseFile();

    cout << task1 << endl;

    LoginSystem loginSystem;
    loginSystem.RegisterUser("Gital", "Madiwa");
    cout << loginSystem.LoginUser("Gital", "Madiwa") << endl;
    return 0;
}