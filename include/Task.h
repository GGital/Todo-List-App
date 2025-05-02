#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
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

    Task() : taskID(0), name(""), description(""), category("General"), status("Not started"), priority("Low")
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
        os << "Task Name: " << task.name << "\n"
           << "Description: " << task.description << "\n"
           << "Status: " << task.status << "\n"
           << "Priority: " << task.priority << "\n"
           << "Due Date: " << asctime(&task.dueDate) << "\n";
        return os;
    }
};