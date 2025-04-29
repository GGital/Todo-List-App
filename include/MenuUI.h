#pragma once
#include <iostream>
#include <LoginSystem.h>
#include <Task.h>
using namespace std;

class LoginSystemUI {
    /*private:
        LoginSystem loginsystem;*/

public:
    void showAuthMenu() {

        //LoginSystem authSystem;
        cout << "***************\n";
        cout << "Authentication Menu.\n\n";
        cout << "1.Register.\n2.Login.\n3.Exit\n\n";
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
        cout << "1.Add Task\n2.Delete Task\n3.Modify Task\n4.View All Tasks\n5.Seach Task\n6.Topological Task\n7.Add Category\n8.Delete Category\n9.Logout\n\n";
        cout << "Enter your choice: ";
        cin.clear();

    }
};

class ModifyMenuUI {
public:
    void showModifyMenu() {
        cout << "***************\n";
        cout << "Modify Menu.\n\n";
        cout << "1.Modify Task\n2.Modify Category\n\n";
        cout << "Enter your choice: ";
        cin.clear();
    }
};
