#pragma once
#include <iostream>

using namespace std;

class Task
{
public:
    char title[100];
    char description[1000];
    char dueDate[20];
    int status;
    int priority;
};
