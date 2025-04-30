#include <iostream>
#include <example.h>
#include <File_Management.h>
#include "Doubly-Linked-List.h"
#include "Min-Priority-Queue.h"
#include "Max-Priority-Queue.h"
#include "Task.h"
#include "LoginSystem.h"
#include "HashMapWithDLL.h"
#include "UserCollections.h"
#include "UI.h"
using namespace std;

int main()
{
    FileManagement fileManager;
    Example example;
    // enable_ansi_colors();
    example.Greet();
    example.Farewell();

    /*DoublyLinkedList<int> dll;
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
    */

    HashMapDLL<string, Task> hashMap(1000);
    Task task1("Task 1", "Description 1", "In Progress", "High");
    Task task2("Task 2", "Description 2", "Completed", "Medium");
    hashMap.insert("Daily Work", task1);
    hashMap.insert("Career", task2);
    DoublyLinkedList<Task> *list = hashMap.getList("Career");
    fileManager.WriteFile("./output/output.txt");
    list->display();
    fileManager.CloseFile();

    LoginSystem loginSystem;
    loginSystem.RegisterUser("Test", "GG");
    cout << loginSystem.LoginUser("Test", "GG") << endl;

    UserCollections userCollection(3058, "Test", "GG");

    cout << ANSI_COLOR_RED << "Hello World!" << ANSI_COLOR_RESET << endl;

    // userCollection.TestRemoveFunction();

    userCollection.TestAddFunction();

    /*
    userCollection.TestEditFunction();
    userCollection.RemindTask();
    userCollection.RemoveAllTasks();
    userCollection.RemoveAllCategories();
    */

    return 0;
}