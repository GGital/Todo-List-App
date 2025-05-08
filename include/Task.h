#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <UI.h>
#include <sstream>
using namespace std;

struct Task
{
    int taskID;
    string name;
    string description;
    string category;
    string status;
    string priority;
    struct tm dueDate;

    // Constructor to initialize a task
    Task(int id, string n, string d, string c, string s, string p) : taskID(id), name(n), description(d), category(c), status(s), priority(p)
    {
        time_t now = time(0);
        dueDate = *localtime(&now); // Initialize dueDate to current date and time
    }

    Task(int id, string n, string d, string s, string p) : taskID(id), name(n), description(d), status(s), priority(p)
    {
        category = "General";
        time_t now = time(0);
        dueDate = *localtime(&now); // Initialize dueDate to current date and time
    }

    Task(string n, string d, string s, string p) : name(n), description(d), status(s), priority(p)
    {
        taskID = 0;
        category = "General";
        time_t now = time(0);
        dueDate = *localtime(&now); // Initialize dueDate to current date and time
    }

    Task() : taskID(0), name(""), description(""), category("Uncategorized"), status("Not started"), priority("")
    {
        time_t now = time(0);
        dueDate = *localtime(&now); // Initialize dueDate to current date and time
    }

    Task(string n, string d, string s, string p, struct tm dd) : name(n), description(d), status(s), priority(p), dueDate(dd) {}

    Task(int id, string n, string d, string s, string p, struct tm dd) : taskID(id), name(n), description(d), status(s), priority(p), dueDate(dd) {}

    Task(string n, string d, string s, string p, string dd)
    {
        name = n;
        description = d;
        status = s;
        priority = p;
        struct tm dateTime = {};
        istringstream ss(dd);
        ss >> get_time(&dateTime, "%Y-%m-%d");
        time_t time = mktime(&dateTime);
        dueDate = *localtime(&time);
    }

    Task(string n, string d, string c, string s, string p, string dd)
    {
        name = n;
        description = d;
        category = c;
        status = s;
        priority = p;
        struct tm dateTime = {};
        istringstream ss(dd);
        ss >> get_time(&dateTime, "%Y-%m-%d");
        time_t time = mktime(&dateTime);
        dueDate = *localtime(&time);
    }

    Task(int id, string n, string d, string c, string s, string p, string dd)
    {
        taskID = id;
        name = n;
        description = d;
        category = c;
        status = s;
        priority = p;
        struct tm dateTime = {};
        istringstream ss(dd);
        ss >> get_time(&dateTime, "%Y-%m-%d");
        time_t time = mktime(&dateTime);
        dueDate = *localtime(&time);
    }

    // Overloading the << operator for easy printing of Task objects
    friend ostream &operator<<(ostream &os, const Task &task)
    {
        os << "=========================================================\n";
        os << "Task ID: " << task.taskID << "\n";
        os << "Task Name: " << task.name << "\n";
        os << "Task Description: " << task.description << "\n";
        os << "Task Category: " << task.category << "\n";
        os << "Task Status: " << task.status << "\n";
        os << "Task Priority: " << task.priority << "\n";
        os << "Task Due Date: " << put_time(&task.dueDate, "%Y-%m-%d") << "\n";
        os << "=========================================================\n";
        return os;
    }

    int priorityValue() const
    {
        if (priority == "High")
            return 3;
        else if (priority == "Medium")
            return 2;
        else if (priority == "Low")
            return 1;
        else
            return 0; // Default value for invalid priority
    }

    // Comparator for sorting tasks by priority
    bool operator<(const Task &other) const
    {
        if (priorityValue() != other.priorityValue())
            return priorityValue() < other.priorityValue();

        // Earlier due date first
        if (dueDate.tm_year != other.dueDate.tm_year)
            return dueDate.tm_year > other.dueDate.tm_year; // Earlier year first
        if (dueDate.tm_mon != other.dueDate.tm_mon)
            return dueDate.tm_mon > other.dueDate.tm_mon; // Earlier month first
        if (dueDate.tm_mday != other.dueDate.tm_mday)
            return dueDate.tm_mday > other.dueDate.tm_mday; // Earlier day first

        // Tie-breaking: Compare by task name (alphabetical order)
        return name < other.name;
    }
};