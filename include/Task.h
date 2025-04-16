#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Task
{
    string name;
    string description;
    string status;
    string priority;
    struct tm dueDate;

    // Constructor to initialize a task
    Task(string n, string d, string s, string p) : name(n), description(d), status(s), priority(p)
    {
        time_t now = time(0);
        dueDate = *localtime(&now); // Initialize dueDate to current date and time
    }

    Task(string n, string d, string s, string p, struct tm dd) : name(n), description(d), status(s), priority(p), dueDate(dd) {}

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
