#include <iostream>
#include <File_Management.h>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <Task.h>
using namespace std;

enum Priority
{
    Low,
    Medium,
    High
};

class UserCollections
{
private:
    int userId;
    string username;
    string password;
    Task *tasks[1005];
    string *categories[1005];
    int categoryCount;
    int taskCount;
    FileManagement fileManager;

public:
    UserCollections(int id, string u, string p) : userId(id), username(u), password(p), categoryCount(0), taskCount(0)
    {
        for (int i = 0; i < 1005; i++)
        {
            tasks[i] = nullptr;
            categories[i] = nullptr;
        }
        ReadTasksFromFile();
        ReadCategoriesFromFile();
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

    /*TestAddFunction
    Parameter : None
    Description : This function is used for testing mandatory functions in the UserCollections class.
    */
    void TestAddFunction()
    {
        AddTask(Task(1, "Test Task", "Test Description", "In Progress", "High"));
        AddCategory("Test Category");
        EditTask(1, Task(1, "Updated Task", "Updated Description", "Completed", "Low"));
    }

    /*TestRemoveFunction
    Parameter : None
    Description : This function is used for testing mandatory functions in the UserCollections class.
    */
    void TestRemoveFunction()
    {
        RemoveTask(1);
        RemoveCategory("Test Category");
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
};