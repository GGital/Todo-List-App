#include <windows.h>
#include <iostream>
#include <example.h>
#include <File_Management.h>
#include <regex>
#include <limits>
#include "Doubly-Linked-List.h"
#include "Min-Priority-Queue.h"
#include "Max-Priority-Queue.h"
#include "Task.h"
#include "GraphTask.h"
#include "LoginSystem.h"
#include "HashMapWithDLL.h"
#include "UserCollections.h"
#include "Edge.h"
#include "Node.h"
#include <UI.h>
#include "MenuUI.h"
#include <SFML/Graphics.hpp>

void enable_ansi_colors()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, dwMode);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    enable_ansi_colors();
    UI ui;
    FileManagement fileManager;
    Example example;
    regex datePattern(R"(\d{4}-\d{2}-\d{2})"); // Matches YYYY-MM-DD format
    // enable_ansi_colors();
    // example.Greet();
    // example.Farewell();

    //--------Authentication Menu--------

    LoginSystem loginSystem;
    LoginSystemUI loginmenu;
    MainMenuUI mainmenu;

    string username, password;

    while (true)
    {

        loginmenu.showAuthMenu();
        int AuthChoice;
        cin.clear();
        cin >> AuthChoice;

        if (cin.fail())
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue; // Ask for input again
        }
        if (AuthChoice == 1)
        {

            loginmenu.showRegisterMenu();
            cout << "Username :";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            getline(cin, username);                              // Use getline to allow spaces in username
            cout << "Password :";
            getline(cin, password); // Use getline to allow spaces in password

            // Check if there is whitespace in username and password
            if (username.find(' ') != string::npos || password.find(' ') != string::npos)
            {
                cout << "\nUsername and Password cannot contain spaces.\n";
                continue;
            }

            if (!loginSystem.checkduplicate(username))
            {

                loginSystem.RegisterUser(username, password);
                cout << "\nRegistration Successful. Please Login to continue.\n";
                break;
            }
            else
            {

                cout << "\nUsername is taken. Please try again later.\n";
                continue;
            }
        }
        else if (AuthChoice == 2)
        {

            loginmenu.showLoginMenu();
            cout << "Username :";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            getline(cin, username);                              // Use getline to allow spaces in username
            cout << "Password :";
            getline(cin, password); // Use getline to allow spaces in password
            if (username.find(' ') != string::npos || password.find(' ') != string::npos)
            {
                cout << "\nUsername and Password cannot contain spaces.\n";
                continue;
            }
            if (loginSystem.LoginUser(username, password) == -1)
            {

                cout << "\nWrong Username or Password. Please try again later.\n";

                continue;
            }
            else
            {

                cout << "\nLogin Successful. Entering the program.\n";
                // cout << loginSystem.LoginUser(username,password);
                break;
            }
        }
        else if (AuthChoice == 3)
        {

            return 0;
        }
        else
        {

            cout << "\nInvalid choice.\n";
            continue;
        }
    }

    //--------Main Menu--------

    DoublyLinkedList<Task> taskList;

    int MainChoice;

    int userID = loginSystem.LoginUser(username, password);

    UserCollections usercollection(userID, username, password);

    string name, category, desc, status, prior, duedate;

    while (true)
    {

        mainmenu.showMainMenu();
        cin >> MainChoice;

        if (cin.fail())
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue; // Ask for input again
        }
        if (MainChoice == 1)
        {

            //--------Add Task Menu--------

            cout << "Enter task's name: ";
            cin.ignore();
            getline(cin, name);

            if (name.find(' ') != string::npos)
            {
                cout << "\nTask name cannot contain spaces.\n";
                continue;
            }
            if (usercollection.CheckDuplicate(name))
            {
                cout << "\nTask name already exists.\n";
                continue;
            }

            cout << "Enter task's description: ";
            getline(cin, desc);

            cout << "[0] Uncategorized\n";
            for (int i = 0; i < usercollection.categoryCount; i++)
            {
                cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
            }

            cout << "Enter task's category: ";
            int categoryIndex;
            cin >> categoryIndex;

            if (cin.fail())
            {
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue; // Ask for input again
            }
            if (categoryIndex == 0)
            {
                category = "Uncategorized";
            }
            else if (categoryIndex > 0 && categoryIndex <= usercollection.categoryCount)
            {
                category = *usercollection.categories[categoryIndex - 1];
            }
            else
            {
                cout << "Invalid category index.\n";
                continue;
            }

            cout << "Enter task's status:\n";
            cout << "[0] Not started\n"
                 << "[1] In progress\n"
                 << "[2] Completed\n";
            int statusIndex;
            cin >> statusIndex;
            if (cin.fail())
            {
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue; // Ask for input again
            }
            if (statusIndex == 0)
            {
                status = "Not started";
            }
            else if (statusIndex == 1)
            {
                status = "In progress";
            }
            else if (statusIndex == 2)
            {
                status = "Completed";
            }
            else
            {
                cout << "Invalid status index.\n";
                continue;
            }

            cout << "Enter task's priority (e.g., Low, Medium, High): \n";
            cout << "[0] Low\n"
                 << "[1] Medium\n"
                 << "[2] High\n";
            int priorIndex;
            cin >> priorIndex;
            if (cin.fail())
            {
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue; // Ask for input again
            }
            if (priorIndex == 0)
            {
                prior = "Low";
            }
            else if (priorIndex == 1)
            {
                prior = "Medium";
            }
            else if (priorIndex == 2)
            {
                prior = "High";
            }
            else
            {
                cout << "Invalid priority index.\n";
                continue;
            }

            cout << "Enter task's due date (YYYY-MM-DD): ";
            cin.ignore();
            getline(cin, duedate);

            // if(duedate) input check task add fail
            if (!regex_match(duedate, datePattern))
            {
                cout << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n";
                continue; // Ask the user to re-enter the date
            }

            cout << "\n***************\n";
            Task task(name, desc, category, status, prior, duedate);

            usercollection.AddTask(task);
            taskList.insertAtEnd(task); // dll connect insertatend

            // task add fail? task add success if else
            //  due date testcase without -, as alphabet char, future time
            // remind task where?

            // Priority Testcase ONLY: LOW MEDIUM HIGH. otherwise: invalid
            cout << "Task Add Successfully.\n";
        }
        else if (MainChoice == 2)
        {

            while (true)
            {

                //--------Delete Task Menu--------

                int removechoice;
                int removeTaskID;
                string removeName;

                RemoveMenuUI removemenuUI;
                removemenuUI.showRemoveMenu();
                cin.clear();
                cin >> removechoice;
                if (cin.fail())
                {
                    cin.clear();                                         // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input. Please enter a number.\n";
                    continue; // Ask for input again
                }
                if (removechoice == 1)
                {

                    // Delete by Task Name

                    // Task Viewing First
                    cout << "\n\n";
                    usercollection.DisplayTasks();
                    cout << "***************\n";

                    cout << "Enter Task's Name To Remove: ";
                    cin >> removeName;
                    usercollection.RemoveTask(removeName);
                    // What if that name doesn't exist in file?
                    break;
                }
                else if (removechoice == 2)
                {

                    // Delete by Task ID

                    // Task Viewing First
                    cout << "\n\n";
                    usercollection.DisplayTasks();
                    cout << "***************\n";

                    cout << "Enter Task's ID To Remove: ";
                    cin >> removeTaskID;
                    if (cin.fail())
                    {
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number.\n";
                        continue; // Ask for input again
                    }
                    usercollection.RemoveTask(removeTaskID);
                    break;
                }
                else if (removechoice == 3)
                {

                    // Exit
                    break;
                }
                else
                {

                    // Invalid Input
                    cout << "\nInvalid choice.\n";
                    cin.clear();
                    cin.ignore();
                    continue;
                }

                // Show all tasks
            }
        }
        else if (MainChoice == 3)
        {

            while (true)
            {

                string newname, newdesc, newstatus, newprior, newduedate;

                //--------Modify Task Menu--------

                int modifychoice;
                int modifyTaskID;
                string modifyName;
                HashMapDLL<string, Task> hashMap(1000);

                ModifyMenuUI modifymenuUI;
                modifymenuUI.showModifyMenu();
                cin.clear();
                cin >> modifychoice;
                if (cin.fail())
                {
                    cin.clear();                                         // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input. Please enter a number.\n";
                    continue; // Ask for input again
                }
                if (modifychoice == 1)
                {

                    // Modify by Task Name

                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;
                    if (cin.fail())
                    {
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number.\n";
                        continue; // Ask for input again
                    }
                    while (true)
                    {
                        if (modifyTaskORCategorychoice == 1)
                        {

                            // Modify Task

                            // Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";

                            cout << "Enter Task's Name To Edit: ";
                            cin.ignore();
                            getline(cin, modifyName);

                            // Check if task exists
                            Task *task = usercollection.SearchTask(modifyName);
                            if (task == nullptr)
                            {
                                cout << "Task not found.\n";
                                continue;
                            }

                            cout << "Enter task name: ";
                            getline(cin, newname);

                            if (newname.find(' ') != string::npos)
                            {
                                cout << "\nTask name cannot contain spaces.\n";
                                continue;
                            }
                            if (usercollection.CheckDuplicate(newname))
                            {
                                cout << "\nTask name already exists.\n";
                                continue;
                            }

                            cout << "Enter task description: ";
                            getline(cin, newdesc);

                            cout << "[0] Uncategorized\n";
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
                            }
                            cout << "Enter task's category: ";
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            cout << categoryIndex << endl;
                            if (categoryIndex == 0)
                            {
                                category = "Uncategorized";
                            }
                            else if (categoryIndex > 0 && categoryIndex <= usercollection.categoryCount)
                            {
                                category = *usercollection.categories[categoryIndex - 1];
                            }
                            else
                            {
                                cout << "Invalid category index.\n";
                                continue;
                            }

                            cout << "Enter task's status: \n";
                            cout << "[0] Not started\n"
                                 << "[1] In progress\n"
                                 << "[2] Completed\n";
                            int statusIndex;
                            cin >> statusIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            if (statusIndex == 0)
                            {
                                newstatus = "Not started";
                            }
                            else if (statusIndex == 1)
                            {
                                newstatus = "In progress";
                            }
                            else if (statusIndex == 2)
                            {
                                newstatus = "Completed";
                            }
                            else
                            {
                                cout << "Invalid status index.\n";
                                continue;
                            }

                            cout << "Enter task priority (e.g., Low, Medium, High): \n";
                            cout << "[0] Low\n"
                                 << "[1] Medium\n"
                                 << "[2] High\n";
                            int priorIndex;
                            cin >> priorIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            if (priorIndex == 0)
                            {
                                newprior = "Low";
                            }
                            else if (priorIndex == 1)
                            {
                                newprior = "Medium";
                            }
                            else if (priorIndex == 2)
                            {
                                newprior = "High";
                            }
                            else
                            {
                                cout << "Invalid priority index.\n";
                                continue;
                            }

                            cout << "Enter task's due date (YYYY-MM-DD): ";
                            cin.ignore();
                            getline(cin, newduedate);

                            if (!regex_match(newduedate, datePattern))
                            {
                                cout << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n";
                                continue; // Ask the user to re-enter the date
                            }

                            Task newtask(newname, newdesc, category, newstatus, newprior, newduedate);

                            cout << "\n***************\n";
                            usercollection.EditTask(modifyName, newtask);
                            break;
                        }
                        else if (modifyTaskORCategorychoice == 2)
                        {

                            // Assign Category Name and Task's Name

                            // Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";

                            string category;

                            cout << "[0] Uncategorized\n";
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
                            }
                            cout << "Enter task's category: ";
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            // cout << categoryIndex << endl;
                            if (categoryIndex == 0)
                            {
                                category = "Uncategorized";
                            }
                            else if (categoryIndex > 0 && categoryIndex <= usercollection.categoryCount)
                            {
                                category = *usercollection.categories[categoryIndex - 1];
                            }
                            else
                            {
                                cout << "Invalid category index.\n";
                                continue;
                            }
                            cout << "Enter the task name: ";
                            cin.ignore();
                            getline(cin, modifyName);

                            usercollection.EditTaskCategory(modifyName, category);

                            break;
                        }
                        else
                        {

                            // Invalid Input
                            cout << "\nInvalid choice.\n";
                            cin.clear();
                            cin.ignore();
                            continue;
                        }
                    }
                }
                else if (modifychoice == 2)
                {

                    // Modify by Task ID

                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;
                    if (cin.fail())
                    {
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number.\n";
                        continue; // Ask for input again
                    }
                    while (true)
                    {
                        if (modifyTaskORCategorychoice == 1)
                        {

                            // Modify Task

                            // Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";
                            cout << "Enter Task's ID To Edit: ";
                            cin >> modifyTaskID;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            // Check if task exists
                            Task *task = usercollection.SearchTask(modifyTaskID);
                            if (task == nullptr)
                            {
                                cout << "Task not found.\n";
                                continue;
                            }

                            cout << "Enter task name: ";
                            cin.ignore();
                            getline(cin, newname);

                            cout << "Enter task description: ";
                            getline(cin, newdesc);

                            cout << "[0] Uncategorized\n";
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
                            }
                            cout << "Enter task's category: ";
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            // cout << categoryIndex << endl;
                            if (categoryIndex == 0)
                            {
                                category = "Uncategorized";
                            }
                            else if (categoryIndex > 0 && categoryIndex <= usercollection.categoryCount)
                            {
                                category = *usercollection.categories[categoryIndex - 1];
                            }
                            else
                            {
                                cout << "Invalid category index.\n";
                                continue;
                            }

                            cout << "Enter task's status: \n";
                            cout << "[0] Not started\n"
                                 << "[1] In progress\n"
                                 << "[2] Completed\n";
                            int statusIndex;
                            cin >> statusIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            if (statusIndex == 0)
                            {
                                newstatus = "Not started";
                            }
                            else if (statusIndex == 1)
                            {
                                newstatus = "In progress";
                            }
                            else if (statusIndex == 2)
                            {
                                newstatus = "Completed";
                            }
                            else
                            {
                                cout << "Invalid status index.\n";
                                continue;
                            }

                            cout << "Enter task priority (e.g., Low, Medium, High): \n";
                            cout << "[0] Low\n"
                                 << "[1] Medium\n"
                                 << "[2] High\n";
                            int priorIndex;
                            cin >> priorIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            if (priorIndex == 0)
                            {
                                newprior = "Low";
                            }
                            else if (priorIndex == 1)
                            {
                                newprior = "Medium";
                            }
                            else if (priorIndex == 2)
                            {
                                newprior = "High";
                            }
                            else
                            {
                                cout << "Invalid priority index.\n";
                                continue;
                            }

                            cout << "Enter task's due date (YYYY-MM-DD): ";
                            cin.ignore();
                            getline(cin, newduedate);

                            if (!regex_match(newduedate, datePattern))
                            {
                                cout << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n";
                                continue; // Ask the user to re-enter the date
                            }

                            Task newtask(newname, newdesc, category, newstatus, newprior, newduedate);

                            cout << "\n***************\n";
                            usercollection.EditTask(modifyTaskID, newtask);
                            break;
                        }
                        else if (modifyTaskORCategorychoice == 2)
                        {

                            // Assign Category Name and Task's ID

                            // Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";

                            string category;

                            cout << "[0] Uncategorized\n";
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
                            }
                            cout << "Enter task's category: ";
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            // cout << categoryIndex << endl;
                            if (categoryIndex == 0)
                            {
                                category = "Uncategorized";
                            }
                            else if (categoryIndex > 0 && categoryIndex <= usercollection.categoryCount)
                            {
                                category = *usercollection.categories[categoryIndex - 1];
                            }
                            else
                            {
                                cout << "Invalid category index.\n";
                                continue;
                            }
                            cout << "Enter the task ID: ";
                            cin >> modifyTaskID;
                            if (cin.fail())
                            {
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "Invalid input. Please enter a number.\n";
                                continue; // Ask for input again
                            }
                            usercollection.EditTaskCategory(modifyTaskID, category);

                            break;
                            // Category Name view, Testcase category name to task
                        }
                        else
                        {

                            // Invalid Input
                            cout << "\nInvalid choice.\n";
                            cin.clear();
                            cin.ignore();
                            continue;
                        }
                    }
                }
                else if (modifychoice == 3)
                {

                    // Exit
                    break;
                }
                else
                {

                    // Invalid Input
                    cout << "\nInvalid choice.\n";
                    cin.clear();
                    cin.ignore();
                    continue;
                }

                // Show all tasks
            }
        }
        else if (MainChoice == 4)
        {

            //--------View Task Menu[By Task ID]--------

            cout << "\n\n";
            usercollection.DisplayTasks();
            // break;
            // No Task Testcase
        }
        else if (MainChoice == 5)
        {

            // Search Task here
            SearchUI searchUI;
            usercollection.InitializeHashMap();
            while (true)
            {

                int searchchoice;
                searchUI.SearchMainUI();
                cin >> searchchoice;
                if (cin.fail())
                {
                    cin.clear();                                         // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input. Please enter a number.\n";
                    continue; // Ask for input again
                }
                if (searchchoice == 1)
                {

                    // Search by Task Name
                    searchUI.SearchNameUI();
                    string searchName;
                    cin.ignore();
                    getline(cin, searchName);
                    Task *temp = usercollection.SearchTask(searchName);
                    if (temp != nullptr)
                    {
                        cout << *temp << endl;
                    }
                }
                else if (searchchoice == 2)
                {

                    // Search by Task ID
                    searchUI.SearchIDUI();
                    int searchID;
                    cin >> searchID;
                    if (cin.fail())
                    {
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number.\n";
                        continue; // Ask for input again
                    }
                    Task *temp = usercollection.SearchTask(searchID);
                    if (temp != nullptr)
                    {
                        cout << *temp << endl;
                    }
                }
                else if (searchchoice == 3)
                {

                    // Search by Task Priority
                    searchUI.SearchPriorUI();
                    cout << "[0] Low\n"
                         << "[1] Medium\n"
                         << "[2] High\n";
                    int searchPriorIndex;
                    cin >> searchPriorIndex;
                    if (cin.fail())
                    {
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number.\n";
                        continue; // Ask for input again
                    }
                    if (searchPriorIndex == 0)
                    {
                        prior = "Low";
                    }
                    else if (searchPriorIndex == 1)
                    {
                        prior = "Medium";
                    }
                    else if (searchPriorIndex == 2)
                    {
                        prior = "High";
                    }
                    else
                    {
                        cout << "Invalid priority index.\n";
                        continue;
                    }
                    DoublyLinkedList<Task> *temp = usercollection.SearchPriority(prior);
                    DoublyLinkedList<Task>::Node *current = temp->head;
                    while (current != nullptr)
                    {
                        ui.ClearScreen();
                        cout << current->data << endl;
                        if (current->next)
                            cout << "Press n to go next\n";
                        if (current->prev)
                            cout << "Press p to go previous\n";
                        cout << "Press any other key to exit\n";
                        char choice;
                        cin >> choice;
                        if (cin.fail())
                        {
                            cin.clear();                                         // Clear the error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            cout << "Invalid input. Please enter a character.\n";
                            continue; // Ask for input again
                        }
                        if (choice == 'n' && current->next != nullptr)
                        {
                            current = current->next;
                        }
                        else if (choice == 'p' && current->prev != nullptr)
                        {
                            current = current->prev;
                        }
                        else
                        {
                            break; // Exit the loop
                        }
                    }
                }
                else if (searchchoice == 4)
                {
                    // Search by Category
                    searchUI.SearchCategoryUI();
                    for (int i = 0; i < usercollection.categoryCount; i++)
                    {
                        cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
                    }
                    cout << "Enter task's category: ";
                    int categoryIndex;
                    cin >> categoryIndex;
                    if (cin.fail())
                    {
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a number.\n";
                        continue; // Ask for input again
                    }
                    if (categoryIndex == 0)
                    {
                        category = "Uncategorized";
                    }
                    else if (categoryIndex > 0 && categoryIndex <= usercollection.categoryCount)
                    {
                        category = *usercollection.categories[categoryIndex - 1];
                    }
                    else
                    {
                        cout << "Invalid category index.\n";
                        continue;
                    }
                    DoublyLinkedList<Task> *temp = usercollection.SearchCategory(category);
                    // Displaying task one by one using n & p to go next and previous
                    DoublyLinkedList<Task>::Node *current = temp->head;
                    while (current != nullptr)
                    {
                        ui.ClearScreen();
                        cout << current->data << endl;
                        if (current->next)
                            cout << "Press n to go next\n";
                        if (current->prev)
                            cout << "Press p to go previous\n";
                        cout << "Press any other key to exit\n";
                        char choice;
                        cin >> choice;
                        if (cin.fail())
                        {
                            cin.clear();                                         // Clear the error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            cout << "Invalid input. Please enter a character.\n";
                            continue; // Ask for input again
                        }
                        if (choice == 'n' && current->next != nullptr)
                        {
                            current = current->next;
                        }
                        else if (choice == 'p' && current->prev != nullptr)
                        {
                            current = current->prev;
                        }
                        else
                        {
                            break; // Exit the loop
                        }
                    }
                }
                else if (searchchoice == 5)
                {

                    // Exit
                    break;
                }
                else
                {

                    // Invalid Input
                    cout << "\nInvalid choice.\n";
                    cin.clear();
                    cin.ignore();
                    continue;
                }
            }

            // No Task Testcase
        }
        else if (MainChoice == 6)
        {

            //--------Topological Task Menu--------
            GraphTask graphTask;
            graphTask.BuildGraph(usercollection);
            // cout << "Graph built successfully.\n";
            graphTask.TopologicalSort();
            Queue<Task> *topologicalOrder = graphTask.TopologicalOrder;
            /*
            cout << "Topological Order of Tasks:\n";
            while (!topologicalOrder->isEmpty())
            {
                Task task = topologicalOrder->dequeue();
                cout << task.taskID << " " << task.name << endl;
            }
            */
            sf::RenderWindow window(sf::VideoMode(1000, 800), "Topological Sort Visualization", sf::Style::Default);
            sf::View view = window.getDefaultView();
            window.setFramerateLimit(60);
            sf::Font font;
            if (!font.loadFromFile("arial.ttf"))
            {
                std::cerr << "Error loading font\n";
                return -1;
            }
            sf::Vector2f mouseDragStart;
            bool dragging = false;

            // Set up nodes and edges
            Node *nodes[1005];
            Edge *edges[1005];
            int cnt = 0;
            while (!topologicalOrder->isEmpty())
            {
                Task task = topologicalOrder->dequeue();
                int taskID = task.taskID;
                string labelText = "ID : " + to_string(taskID) + " " + task.name + "\nPriority : " + task.priority + "\nDue Date : " + to_string(task.dueDate.tm_year + 1900) + "-" + to_string(task.dueDate.tm_mon + 1) + "-" + to_string(task.dueDate.tm_mday);
                nodes[cnt++] = new Node(100 + cnt * 250, 100 + cnt * 250, labelText, font);
                nodes[cnt - 1]->setFillColor(task.status);
            }
            for (int i = 0; i < cnt - 1; i++)
            {
                edges[i] = new Edge(nodes[i], nodes[i + 1]);
            }

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::MouseWheelScrolled)
                    {
                        if (event.mouseWheelScroll.delta > 0)
                            view.zoom(0.9f); // zoom in
                        else
                            view.zoom(1.1f); // zoom out
                    }
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle)
                    {
                        dragging = true;
                        mouseDragStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    }
                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle)
                    {
                        dragging = false;
                    }
                    // Resize window
                    if (event.type == sf::Event::Resized)
                    {
                        view.setSize(event.size.width, event.size.height);
                    }

                    // Handle dragging movement
                    if (dragging)
                    {
                        sf::Vector2f newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        sf::Vector2f offset = mouseDragStart - newMousePos;
                        view.move(offset);
                        mouseDragStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    }
                }

                window.setView(view);
                window.clear(sf::Color(30, 30, 30));
                // Draw your graph here

                for (int i = 0; i < cnt - 1; i++)
                {
                    edges[i]->draw(window);
                }
                for (int i = 0; i < cnt; i++)
                {
                    nodes[i]->draw(window);
                }
                window.display();
            }
        }
        else if (MainChoice == 7)
        {

            //--------Add Category Menu--------

            CategoryUI categoryUI;
            categoryUI.AddCategoryMenu();
            string categoryname;
            cin.ignore();
            getline(cin, categoryname);
            if (categoryname.find(' ') != string::npos)
            {
                cout << "\nCategory name cannot contain spaces.\n";
                continue;
            }
            // Check if there is whitespace in the name

            usercollection.AddCategory(categoryname);
        }
        else if (MainChoice == 8)
        {

            //--------Delete Category Menu--------

            CategoryUI categoryUI;
            categoryUI.DeleteCategoryMenu();
            string categoryname;
            cin.ignore();
            cin.clear();
            getline(cin, categoryname);
            if (categoryname.find(' ') != string::npos)
            {
                cout << "\nCategory name cannot contain spaces.\n";
                continue;
            }
            usercollection.RemoveCategory(categoryname);
            for (int i = 0; i < usercollection.taskCount; i++)
            {
                if (usercollection.tasks[i]->category == categoryname)
                {
                    usercollection.tasks[i]->category = "Uncategorized";
                }
            }
            usercollection.fileManager.WriteFile("./UserCollections/Tasks/" + to_string(userID) + ".csv");
            for (int i = 0; i < usercollection.taskCount; i++)
            {
                cout << usercollection.tasks[i]->taskID << "," << usercollection.tasks[i]->name << "," << usercollection.tasks[i]->description << "," << usercollection.tasks[i]->category << "," << usercollection.tasks[i]->status << "," << usercollection.tasks[i]->priority << ",";
                cout << put_time(&usercollection.tasks[i]->dueDate, "%Y-%m-%d") << endl;
            }
            usercollection.fileManager.CloseFile();
        }
        else if (MainChoice == 9)
        {

            //--------View Category Menu--------

            cout << "\n\n";
            usercollection.DisplayCategories();
            // No Category Testcase
        }
        else if (MainChoice == 0)
        {

            //--------Logout Menu--------

            loginSystem.LogoutUser(userID);
            cout << "Logout Successfully.";
            break;
        }
        else
        {

            // Invalid Input
            cout << "\nInvalid choice.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
    return 0;
}