#include <UserCollections.h>
#include <Task.h>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

void UserCollections::ReadTasksFromFile()
{
    fileManager.ReadFile("./UserCollection/Tasks/" + to_string(userId) + ".csv");
    string line;
    while (getline(cin, line))
    {
        int pos = line.find(',');
        int taskID = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(',');
        string taskName = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        string taskDescription = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        string taskStatus = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        string taskPriority = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        string taskDueDate = line.substr(0, pos);
        tm tm = {};
        istringstream ss(taskDueDate);
        ss >> get_time(&tm, "%Y-%m-%d");
        time_t dueDate = mktime(&tm);
        tasks[taskCount++] = new Task(taskID, taskName, taskDescription, taskStatus, taskPriority, *localtime(&dueDate));
    }
    fileManager.CloseFile();
}

void UserCollections::ReadCategoriesFromFile()
{
    fileManager.ReadFile("./UserCollection/Categories/" + to_string(userId) + ".csv");
    string line;
    while (getline(cin, line))
    {
        categories[categoryCount++] = new string(line);
    }
    fileManager.CloseFile();
}

void UserCollections::AddTask(Task task)
{
    cout << "Trallalello Tralla" << endl;
}