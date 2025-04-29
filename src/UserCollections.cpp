#include <UserCollections.h>
#include <Task.h>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

void UserCollections::ReadTasksFromFile()
{
    fileManager.ReadFile("./UserCollections/Tasks/" + to_string(userId) + ".csv");
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
        struct tm t = ParseStringtoDateTime(taskDueDate);
        tasks[taskCount++] = new Task(taskID, taskName, taskDescription, taskStatus, taskPriority, t);
    }
    fileManager.CloseFile();
}

void UserCollections::ReadCategoriesFromFile()
{
    fileManager.ReadFile("./UserCollections/Categories/" + to_string(userId) + ".csv");
    string line;
    while (getline(cin, line))
    {
        categories[categoryCount++] = new string(line);
    }
    fileManager.CloseFile();
}

void UserCollections::AddTask(Task task)
{
    fileManager.AppendFile("./UserCollections/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->name == task.name)
        {
            cout << "Task name already exists." << endl;
            fileManager.CloseFile();
            return;
        }
    }
    tasks[taskCount++] = new Task(task);
    cout << task.taskID << "," << task.name << "," << task.description << "," << task.status << "," << task.priority << ",";
    cout << put_time(&task.dueDate, "%Y-%m-%d") << endl;
    fileManager.CloseFile();
}

void UserCollections::AddCategory(string category)
{
    fileManager.AppendFile("./UserCollections/Categories/" + to_string(userId) + ".csv");
    for (int i = 0; i < categoryCount; i++)
    {
        if (*categories[i] == category)
        {
            cout << "Category name already exists." << endl;
            fileManager.CloseFile();
            return;
        }
    }
    categories[categoryCount++] = new string(category);
    cout << category << endl;
    fileManager.CloseFile();
}

void UserCollections::RemoveCategory(string category)
{
    bool found = false;
    for (int i = 0; i < categoryCount; i++)
    {
        if (*categories[i] == category)
        {
            delete categories[i];
            found = true;
            for (int j = i; j < categoryCount - 1; j++)
            {
                categories[j] = categories[j + 1];
            }
            categories[--categoryCount] = nullptr;
            break;
        }
    }
    if (!found)
    {
        cout << "Category not found." << endl;
        return;
    }
    fileManager.WriteFile("./UserCollections/Categories/" + to_string(userId) + ".csv");
    for (int i = 0; i < categoryCount; i++)
    {
        cout << *categories[i] << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::RemoveTask(int taskID)
{
    bool found = false;
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->taskID == taskID)
        {
            delete tasks[i];
            found = true;
            for (int j = i; j < taskCount - 1; j++)
            {
                tasks[j] = tasks[j + 1];
            }
            tasks[--taskCount] = nullptr;
            break;
        }
    }
    if (!found)
    {
        cout << "Task not found." << endl;
        return;
    }
    fileManager.WriteFile("./UserCollections/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        cout << tasks[i]->taskID << "," << tasks[i]->name << "," << tasks[i]->description << "," << tasks[i]->status << "," << tasks[i]->priority << ",";
        cout << put_time(&tasks[i]->dueDate, "%Y-%m-%d") << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::RemoveTask(string taskName)
{
    bool found = false;
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->name == taskName)
        {
            delete tasks[i];
            found = true;
            for (int j = i; j < taskCount - 1; j++)
            {
                tasks[j] = tasks[j + 1];
            }
            tasks[--taskCount] = nullptr;
            break;
        }
    }
    if (!found)
    {
        cout << "Task not found." << endl;
        return;
    }
    fileManager.WriteFile("./UserCollections/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        cout << tasks[i]->taskID << "," << tasks[i]->name << "," << tasks[i]->description << "," << tasks[i]->status << "," << tasks[i]->priority << ",";
        cout << put_time(&tasks[i]->dueDate, "%Y-%m-%d") << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::EditTask(int taskID, Task newTask)
{
    bool found = false;
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->taskID == taskID)
        {
            delete tasks[i];
            found = true;
            tasks[i] = new Task(newTask);
            break;
        }
    }
    if (!found)
    {
        cout << "Task not found." << endl;
        return;
    }
    fileManager.WriteFile("./UserCollections/Tasks/" + to_string(userId) + ".csv");
    for (int i = 0; i < taskCount; i++)
    {
        cout << tasks[i]->taskID << "," << tasks[i]->name << "," << tasks[i]->description << "," << tasks[i]->status << "," << tasks[i]->priority << ",";
        cout << put_time(&tasks[i]->dueDate, "%Y-%m-%d") << endl;
    }
    fileManager.CloseFile();
}

void UserCollections::EditTask(string taskName, Task newTask)
{
    bool found = false;
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i]->name == taskName)
        {
            delete tasks[i];
            found = true;
            tasks[i] = new Task(newTask);
            break;
        }
    }
    if (!found)
    {
        cout << "Task not found." << endl;
        return;
    }
    fileManager.WriteFile("./UserCollections/Tasks/" + to_string(userId) + ".csv");
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