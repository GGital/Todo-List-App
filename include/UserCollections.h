#include <iostream>
#include <File_Management.h>
#include <string>
#include <Task.h>
using namespace std;

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
        for (int i = 0; i < 1005; ++i)
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
        delete[] tasks;
        delete[] categories;
    }

    void ReadTasksFromFile();
    void ReadCategoriesFromFile();
    void AddTask(Task task);
};