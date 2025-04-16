#pragma once
#include <iostream>
#include <string>
using namespace std;

void WriteFile(string fileName)
{
    freopen(fileName.c_str(), "w", stdout); // Open the file in write mode
}

void ReadFile(string fileName)
{
    freopen(fileName.c_str(), "r", stdin); // Open the file in read mode
}

bool isFileExist(string fileName)
{
    FILE *file = fopen(fileName.c_str(), "r");
    if (file)
    {
        fclose(file);
        return true; // File exists
    }
    return false; // File does not exist
}

void CloseFile()
{
    fclose(stdout); // Close the file
    fclose(stdin);  // Close the file
    // Reopen stdout and stdin to their original state (console)
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
}
