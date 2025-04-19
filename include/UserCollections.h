#include <iostream>
#include <string>
#include <Task.h>
using namespace std;

class UserCollections
{
private:
    int userId;
    string username;
    string password;
    Task *tasks;
    string *categories;
    int categoryCount;
    int taskCount;

public:
    UserCollections(int userId, string u, string p) : userId(userId), username(u), password(p), tasks(nullptr), categories(nullptr), categoryCount(0), taskCount(0)
    {
        tasks = new Task[0];        // Initialize tasks to an empty array
        categories = new string[0]; // Initialize categories to an empty array
        ReadTasksFromFile();        // Read tasks from file
        ReadCategoriesFromFile();   // Read categories from file
    }

    // Destructor to clean up dynamically allocated memory
    ~UserCollections()
    {
        delete[] tasks;
        delete[] categories;
    }

    ReadTasksFromFile();
    ReadCategoriesFromFile();
    AddTask(Task task);
};