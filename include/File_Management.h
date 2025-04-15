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

void CloseFile()
{
    fclose(stdin);  // Close the file
    fclose(stdout); // Close the file
}
