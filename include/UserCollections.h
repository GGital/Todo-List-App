#pragma once
#include <iostream>
#include <File_Management.h>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <Task.h>
#include <Max-Priority-Queue.h>
#include <HashMapWithDLL.h>
using namespace std;

enum Priority
{
    Low,
    Medium,
    High
};

class UserCollections
{

public:
    int userId;
    string username;
    string password;
    Task *tasks[1005];
    string *categories[1005];
    int categoryCount;
    int taskCount;
    FileManagement fileManager;

    HashMapDLL<string, Task> taskHashMapCategory = HashMapDLL<string, Task>(1005); // HashMap for searching tasks by category
    HashMapDLL<string, Task> taskHashMapPriority = HashMapDLL<string, Task>(1005); // HashMap for searching tasks by priority

    MaxPriorityQueue<Task> taskQueue; // Max priority queue for tasks

    UserCollections(int id, string u, string p) : userId(id), username(u), password(p), categoryCount(0), taskCount(0)
    {
        for (int i = 0; i < 1005; i++)
        {
            tasks[i] = nullptr;
            categories[i] = nullptr;
        }

        taskQueue = MaxPriorityQueue<Task>(1005);

        // cout << "User ID: " << userId << endl;
        ReadTasksFromFile();
        ReadCategoriesFromFile();
        InitializeTaskQueue();
    }
    // Destructor to clean up dynamically allocated memory
    ~UserCollections()
    {
        for (int i = 0; i < taskCount; i++)
        {
            delete tasks[i];
        }
        for (int i = 0; i < categoryCount; i++)
        {
            delete categories[i];
        }
    }

    /* ReadTasksFromFile
    Parameter : None
    Description : This function reads tasks from the tasks.csv file and populates the tasks array.
    */
    void ReadTasksFromFile();
    /* ReadCategoriesFromFile
    Parameter : None
    Description : This function reads categories from the categories.csv file and populates the categories array.
    */
    void ReadCategoriesFromFile();

    /*DisplayTasks
    Parameter : None
    Desription : This function displays all tasks in the tasks array.
    */
    void DisplayTasks();

    /*DisplayCategories
    Parameter : None
    Description : This function displays all categories in the categories array.
    */
    void DisplayCategories()
    {
        for (int i = 0; i < categoryCount; i++)
        {
            cout << *categories[i] << endl;
        }
    }

    /* AddTask
    Parameter : (Task task)
    Description : This function adds a new task to the tasks array and appends it to the tasks.csv file.
    */
    void AddTask(Task task);

    /* AddCategory
    Parameter : (string category)
    Description : This function adds a new category to the categories array and appends it to the categories.csv file.
    */
    void AddCategory(string category);

    /* RemoveCategory
    Parameter : (string category)
    Desription : This function removes a category from the categories array and deletes it from the categories.csv file.
    */
    void RemoveCategory(string category);

    /* RemoveTask
     Parameter : (int taskID) OR (string taskName)
     Description : This function removes a task from the tasks array and deletes it from the tasks.csv file.
     */
    void RemoveTask(int taskID);
    void RemoveTask(string taskName);

    /* EditTask
    Parameter : (int taskID, Task newTask) OR (string taskName, Task newTask)
    Description : This function edits an existing task in the tasks array and updates it in the tasks.csv file.
    */
    void EditTask(int taskID, Task newTask);
    void EditTask(string taskName, Task newTask);

    /*EditTaskCategory
    Parameter : (int taskID, string category) OR (string taskName, string category)
    Description : This function edits the category of an existing task in the tasks array and updates it in the tasks.csv file.
    */
    void EditTaskCategory(int taskID, string category);
    void EditTaskCategory(string taskName, string category);
    /*TestAddFunction
    Parameter : None
    Description : This function is used for testing mandatory functions in the UserCollections class.
    */
    void TestAddFunction()
    {
        AddTask(Task(1, "Test Task", "Test Description", "In Progress", "High"));
        AddTask(Task(2, "Test Task 2", "Test Description 2", "Completed", "Medium"));
        AddCategory("Test Category");
        AddCategory("Test Category 2");
        AddTask(Task("Test Task 3", "Test Description 3", "In Progress", "Low", "2025-11-24"));
        AddTask(Task("Test Task 4", "Test Description 4", "Completed", "High", "2025-11-24"));
    }

    /*CheckDuplicate
    Parameter : (string taskName)
    Description : This function checks if a task with the same name already exists in the tasks array.
    */
    bool CheckDuplicate(string taskName);

    /*TestRemoveFunction
    Parameter : None
    Description : This function is used for testing mandatory functions in the UserCollections class.
    */
    void TestRemoveFunction()
    {
        RemoveTask(1);
        RemoveCategory("Test Category");
    }

    /*TestEditFunction
    Parameter : None
    Description : This function is used for testing mandatory functions in the UserCollections class.
    */
    void TestEditFunction()
    {
        EditTask(1, Task(1, "Updated Task", "Updated Description", "Completed", "Low"));
        EditTask("Test Task 2", Task(1, "Updated Task", "Updated Description", "Completed", "Low"));
    }

    /*ParseStringtoDateTime
    Parameter : (string dateString)
    Description : This function parses a string to a DateTime object.
    */
    struct tm ParseStringtoDateTime(string dateString)
    {
        struct tm dateTime = {};
        istringstream ss(dateString);
        ss >> get_time(&dateTime, "%Y-%m-%d");
        time_t time = mktime(&dateTime);
        return *localtime(&time);
    }

    /*RemindTask
    Parameter : None
    Description : This function checks if any tasks are due upcoming days and displays a reminder message.
    */
    void RemindTask();

    /*RemoveAllTasks
    Parameter : None
    Description : This function removes all tasks from the tasks array and deletes them from the tasks.csv file.
    */
    void RemoveAllTasks();

    /*RemoveAllCategories
     Parameter : None
     Description : This function removes all categories from the categories array and deletes them from the categories.csv file.
     */
    void RemoveAllCategories();

    /*SearchTask
    Parameter : (string taskName) OR (int taskID)
    Description : This function searches for a task by its name in the tasks array and returns the task if found.
    */
    Task *SearchTask(string taskName);
    Task *SearchTask(int taskID);

    /* InitializeHashMap
    Parameter : None
    Description : This function initializes the hash map for searching tasks by category and priority.
    */
    void InitializeHashMap();

    /*SearchCategory
    Parameter : (string categoryName)
    Description : This function searches for tasks by their category in the tasks array using the concept of hash table chaining with doubly linked list.
    */
    DoublyLinkedList<Task> *SearchCategory(string categoryName);

    /*SearchPriority
    Parameter : (string priorityName)
    Description : This function searches for tasks by their priority in the tasks array using the concept of hash table chaining with doubly linked list.
    */
    DoublyLinkedList<Task> *SearchPriority(string priorityName);

    /*
    InitializeTaskQueue
    Parameter : None
    Description : This function initializes the task queue with tasks from the tasks array.
    */
    void InitializeTaskQueue();
};