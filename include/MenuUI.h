#pragma once
#include <iostream>
#include <LoginSystem.h>
#include <Task.h>
using namespace std;

class LoginSystemUI {
public:
    void showAuthMenu() {

        //LoginSystem authSystem;
        cout << "***************\n";
        cout << "Authentication Menu.\n\n";
        cout << "1.Register.\n2.Login.\n3.Exit.\n\n";
        cout << "Enter your choice: ";
        cin.clear();

    }
    void showRegisterMenu() {

        cout << "***************\n";
        cout << "Register Menu.\n\n";

    }
    void showLoginMenu() {

        cout << "***************\n";
        cout << "Login Menu.\n\n";
        
    }
};

class MainMenuUI {
public:
    void showMainMenu() {
        cout << "***************\n";
        cout << "Main Menu.\n\n";
        cout << "1.Add Task\n";
        cout << "2.Delete Task\n";
        cout << "3.Modify Task\n";
        cout << "4.View All Tasks\n";
        cout << "5.Search Task\n";
        cout << "6.Topological Task\n";
        cout << "7.Add Category\n";
        cout << "8.Delete Category\n";
        cout << "9.Logout\n\n";
        cout << "Enter your choice: ";
        cin.clear();

    }
};

class RemoveMenuUI {
public:
    void showRemoveMenu() {

        cout << "***************\n";
        cout << "Remove Menu.\n\n";
        cout << "1.Remove By Name\n2.Remove By Task ID\n3.Exit\n\n";
        cout << "Enter your choice: ";
        cin.clear();

    }
};

class ModifyMenuUI {
public:
    void showModifyMenu() {
        
        cout << "***************\n";
        cout << "Modify Menu.\n\n";
        cout << "1.Modify By Name\n2.Modify By Task ID\n3.Exit\n\n";
        cout << "Enter your choice: ";
        cin.clear();
    }
};
