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
    fileManager.AppendFile("./UserCollection/Tasks/" + to_string(userId) + ".csv");
    tasks[taskCount++] = new Task(task);
    cout << task.taskID << "," << task.name << "," << task.description << "," << task.status << "," << task.priority << ",";
    cout << put_time(&task.dueDate, "%Y-%m-%d") << endl;
    fileManager.CloseFile();
}

void UserCollections::AddCategory(string category)
{
    fileManager.AppendFile("./UserCollection/Categories/" + to_string(userId) + ".csv");
    categories[categoryCount++] = new string(category);
    cout << category << endl;
    fileManager.CloseFile();
}

void UserCollections::RemoveCategory(string category)
{
    for (int i = 0; i < categoryCount; i++)
    {
        if (*categories[i] == category)
        {
            delete categories[i];
            for (int j = i; j < categoryCount - 1; j++)
            {
                categories[j] = categories[j + 1];
            }
            categories[--categoryCount] = nullptr;
            break;
        }
    }
    fileManager.WriteFile("./UserCollection/Categories/" + to_string(userId) + ".csv");
    for (int i = 0; i < categoryCount; i++)
    {
        cout << *categories[i] << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::RemoveTask(int taskID)
{
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->taskID == taskID)
        {
            delete tasks[i];
            for (int j = i; j < taskCount - 1; j++)
            {
                tasks[j] = tasks[j + 1];
            }
            tasks[--taskCount] = nullptr;
            break;
        }
    }
    fileManager.WriteFile("./UserCollection/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        cout << tasks[i]->taskID << "," << tasks[i]->name << "," << tasks[i]->description << "," << tasks[i]->status << "," << tasks[i]->priority << ",";
        cout << put_time(&tasks[i]->dueDate, "%Y-%m-%d") << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::RemoveTask(string taskName)
{
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->name == taskName)
        {
            delete tasks[i];
            for (int j = i; j < taskCount - 1; j++)
            {
                tasks[j] = tasks[j + 1];
            }
            tasks[--taskCount] = nullptr;
            break;
        }
    }
    fileManager.WriteFile("./UserCollection/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        cout << tasks[i]->taskID << "," << tasks[i]->name << "," << tasks[i]->description << "," << tasks[i]->status << "," << tasks[i]->priority << ",";
        cout << put_time(&tasks[i]->dueDate, "%Y-%m-%d") << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::EditTask(int taskID, Task newTask)
{
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->taskID == taskID)
        {
            delete tasks[i];
            tasks[i] = new Task(newTask);
            break;
        }
    }
    fileManager.WriteFile("./UserCollection/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        cout << tasks[i]->taskID << "," << tasks[i]->name << "," << tasks[i]->description << "," << tasks[i]->status << "," << tasks[i]->priority << ",";
        cout << put_time(&tasks[i]->dueDate, "%Y-%m-%d") << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::EditTask(string taskName, Task newTask)
{
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->name == taskName)
        {
            delete tasks[i];
            tasks[i] = new Task(newTask);
            break;
        }
    }
    fileManager.WriteFile("./UserCollection/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        cout << tasks[i]->taskID << "," << tasks[i]->name << "," << tasks[i]->description << "," << tasks[i]->status << "," << tasks[i]->priority << ",";
        cout << put_time(&tasks[i]->dueDate, "%Y-%m-%d") << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::DisplayTasks()
{
    for (int i = 0; i < taskCount; i++)
    {
        cout << *tasks[i] << endl;
    }
}