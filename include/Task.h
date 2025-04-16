#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Task
{
    string name;
    string description;
    string status;
    string priority;
    string dueDate;

    // Constructor to initialize a task
    Task(string n, string d, string s, string p, string dd) : name(n), description(d), status(s), priority(p), dueDate(dd) {}

    friend ostream &operator<<(ostream &os, const Task &task)
    {
        os << "Task Name: " << task.name << "\n"
           << "Description: " << task.description << "\n"
           << "Status: " << task.status << "\n"
           << "Priority: " << task.priority << "\n"
           << "Due Date: " << task.dueDate << "\n";
        return os;
    }
};
