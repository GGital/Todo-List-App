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

    LoginSystem loginSystem;
    LoginSystemUI loginmenu;
    MainMenuUI mainmenu;

    string username, password;

    while (true)
    {
        ui.ClearScreen();
        loginmenu.showAuthMenu();
        int AuthChoice;
        cin.clear();
        cin >> AuthChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            Sleep(1500);
            continue;
        }
        if (AuthChoice == 1)
        {
            ui.ClearScreen();
            loginmenu.showRegisterMenu();
            cout << ANSI_COLOR_BABY_BLUE2 << "Username :" ANSI_COLOR_RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, username);
            cout << ANSI_COLOR_BABY_BLUE4 << "Password :" ANSI_COLOR_RESET;
            getline(cin, password);

            if (username.find(' ') != string::npos || password.find(' ') != string::npos || username.find(',') != string::npos || password.find(',') != string::npos)
            {
                cout << ANSI_COLOR_RED << "\nUsername and Password cannot contain spaces or comma.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }

            if (!loginSystem.checkduplicate(username))
            {
                loginSystem.RegisterUser(username, password);
                cout << ANSI_COLOR_GREEN << "\nRegistration Successful. Please Login to continue.\n" ANSI_COLOR_RESET;
                Sleep(1500);
                break;
            }
            else
            {
                cout << ANSI_COLOR_RED << "\nUsername is taken. Please try again later.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }
        }
        else if (AuthChoice == 2)
        {
            ui.ClearScreen();
            loginmenu.showLoginMenu();
            cout << ANSI_COLOR_BABY_BLUE2 << "Username :" << ANSI_COLOR_RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, username);
            cout << ANSI_COLOR_BABY_BLUE4 << "Password :" << ANSI_COLOR_RESET;
            getline(cin, password);
            if (username.find(' ') != string::npos || password.find(' ') != string::npos || username.find(',') != string::npos || password.find(',') != string::npos)
            {
                cout << ANSI_COLOR_RED << "\nUsername and Password cannot contain spaces or comma.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }
            if (loginSystem.LoginUser(username, password) == -1)
            {
                cout << ANSI_COLOR_RED << "\nWrong Username or Password. Please try again later.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }
            else
            {
                cout << ANSI_COLOR_GREEN2 << "\nLogin Successful. Entering the program.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                break;
            }
        }
        else if (AuthChoice == 3)
        {
            cout << ANSI_COLOR_BABY_BLUE2 << "\nExiting the program...\n" ANSI_COLOR_RESET;
            Sleep(1500);
            return 0;
        }
        else
        {
            cout << ANSI_COLOR_RED "\nInvalid choice.\n"
                 << ANSI_COLOR_RESET;
            Sleep(1500);
            continue;
        }
    }

    DoublyLinkedList<Task> taskList;

    int MainChoice;

    int userID = loginSystem.LoginUser(username, password);

    UserCollections usercollection(userID, username, password);

    string name, category, desc, status, prior, duedate;

    while (true)
    {
        ui.ClearScreen();
        usercollection.RemindTask();
        mainmenu.showMainMenu();
        cin >> MainChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                 << ANSI_COLOR_RESET;
            Sleep(1500);
            continue;
        }
        if (MainChoice == 1)
        {
            ui.ClearScreen();
            cout << ANSI_COLOR_RW4 << "╭────────────────────────────────────────────────────────────╮\n"
                 << ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW4 << "│                        Add Menu.                           │\n"
                 << ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW4 << "│                                                            │\n"
                 << ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW4 << "   Enter task's name: " << ANSI_COLOR_RESET;
            cin.ignore();
            getline(cin, name);

            if (name.find(' ') != string::npos || name.find(',') != string::npos)
            {
                cout << ANSI_COLOR_RED << "\nTask name cannot contain spaces or comma.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }
            if (usercollection.CheckDuplicate(name))
            {
                cout << ANSI_COLOR_RED << "\nTask name already exists.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }

            cout << ANSI_COLOR_RW4 << "   Enter task's description: " << ANSI_COLOR_RESET;
            getline(cin, desc);
            if (desc.find(' ') != string::npos || desc.find(',') != string::npos)
            {
                cout << ANSI_COLOR_RED << "\nTask description cannot contain spaces or comma.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }
            cout << ANSI_COLOR_RW1 << "   [0] Uncategorized\n"
                 << ANSI_COLOR_RESET;
            for (int i = 0; i < usercollection.categoryCount; i++)
            {
                cout << ANSI_COLOR_RW1 << "   [" << i + 1 << "] " << *usercollection.categories[i] << ANSI_COLOR_RESET << endl;
            }

            cout << ANSI_COLOR_RW4 << "   Enter task's category: " << ANSI_COLOR_RESET;
            int categoryIndex;
            cin >> categoryIndex;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ANSI_COLOR_RED << "  Invalid input. Please enter a number.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
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
                cout << ANSI_COLOR_RED << "Invalid category index.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }

            cout << ANSI_COLOR_RW4 << "\n   Enter task's status: " << ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW1 << "\n   [0] Not started\n"
                 << ANSI_COLOR_RESET
                 << ANSI_COLOR_RW2 << "   [1] In progress\n"
                 << ANSI_COLOR_RESET
                 << ANSI_COLOR_RW3 << "   [2] Completed\n"
                 << ANSI_COLOR_RESET;
            int statusIndex;
            cin >> statusIndex;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
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
                cout << ANSI_COLOR_RED "Invalid status index.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }

            cout << ANSI_COLOR_RW4 << "\n   Enter task's priority (e.g., Low, Medium, High): "
                 << ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW1 << "\n   [0] Low\n"
                 << ANSI_COLOR_RESET
                 << ANSI_COLOR_RW2 << "   [1] Medium\n"
                 << ANSI_COLOR_RESET
                 << ANSI_COLOR_RW3 << "   [2] High\n"
                 << ANSI_COLOR_RESET;
            int priorIndex;
            cin >> priorIndex;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
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
                cout << ANSI_COLOR_RED << "Invalid priority index.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }

            cout << ANSI_COLOR_RW4 << "   Enter task's due date (YYYY-MM-DD): " << ANSI_COLOR_RESET;
            cin.ignore();
            getline(cin, duedate);

            if (!regex_match(duedate, datePattern))
            {
                cout << ANSI_COLOR_RED << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n"
                     << ANSI_COLOR_RED;
                Sleep(1500);
                continue;
            }

            Task task(name, desc, category, status, prior, duedate);

            usercollection.AddTask(task);
            taskList.insertAtEnd(task);

            cout << ANSI_COLOR_RW4 << "\n│                                                            │\n"
                 << ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW4 << "╰────────────────────────────────────────────────────────────╯\n"
                 << ANSI_COLOR_RESET;
            cout << ANSI_COLOR_GREEN2 << "Task Add Successfully.\n"
                 << ANSI_COLOR_RESET;
            Sleep(1500);
        }
        else if (MainChoice == 2)
        {
            while (true)
            {
                ui.ClearScreen();
                int removechoice;
                int removeTaskID;
                string removeName;
                RemoveMenuUI removemenuUI;
                removemenuUI.showRemoveMenu();
                cin.clear();
                cin >> removechoice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                         << ANSI_COLOR_RESET;
                    Sleep(1500);
                    continue;
                }
                if (removechoice == 1)
                {
                    usercollection.DisplayTasks();
                    Sleep(1500);
                    cout << ANSI_COLOR_RW5 << "  Enter Task's Name To Remove: " << ANSI_COLOR_RESET;
                    cin >> removeName;
                    usercollection.RemoveTask(removeName);
                    break;
                }
                else if (removechoice == 2)
                {
                    usercollection.DisplayTasks();
                    cout << "\n";
                    Sleep(1500);
                    cout << ANSI_COLOR_RW5 << "  Enter Task's ID To Remove: " << ANSI_COLOR_RESET;
                    cin >> removeTaskID;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n" ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
                    }
                    usercollection.RemoveTask(removeTaskID);
                }
                else if (removechoice == 3)
                {
                    break;
                }
                else
                {
                    cout << ANSI_COLOR_RED << "\nInvalid choice.\n"
                         << ANSI_COLOR_RESET;
                    cin.clear();
                    cin.ignore();
                    Sleep(1500);
                    continue;
                }
            }
        }
        else if (MainChoice == 3)
        {
            while (true)
            {
                ui.ClearScreen();
                string newname, newdesc, newstatus, newprior, newduedate;
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
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                         << ANSI_COLOR_RESET;
                    Sleep(1500);
                    continue;
                }
                if (modifychoice == 1)
                {
                    int modifyTaskORCategorychoice;
                    ui.ClearScreen();
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                             << ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
                    }
                    while (true)
                    {
                        if (modifyTaskORCategorychoice == 1)
                        {
                            ui.ClearScreen();
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "\n";

                            cout << ANSI_COLOR_RW7 << "  Enter Task's Name To Edit: " << ANSI_COLOR_RESET;
                            cin.ignore();
                            getline(cin, modifyName);

                            Task *task = usercollection.SearchTask(modifyName);
                            if (task == nullptr)
                            {
                                cout << ANSI_COLOR_RED << "Task not found.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "  Enter task name: " << ANSI_COLOR_RESET;
                            getline(cin, newname);

                            if (newname.find(' ') != string::npos || newname.find(',') != string::npos)
                            {
                                cout << ANSI_COLOR_RED << "\nTask name cannot contain spaces or comma.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }
                            if (usercollection.CheckDuplicate(newname))
                            {
                                cout << ANSI_COLOR_RED << "\nTask name already exists.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "  Enter task description: " << ANSI_COLOR_RESET;
                            getline(cin, newdesc);

                            if (newdesc.find(' ') != string::npos || newdesc.find(',') != string::npos)
                            {
                                cout << ANSI_COLOR_RED << "\nTask description cannot contain spaces or comma.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW6 << "  [0] Uncategorized\n\n"
                                 << ANSI_COLOR_RESET;
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << ANSI_COLOR_RW6 << "  [" << i + 1 << "] " << ANSI_COLOR_RESET << *usercollection.categories[i] << endl;
                            }
                            cout << ANSI_COLOR_RW7 << "  Enter task's category: " << ANSI_COLOR_RESET;
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid category index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "\n  Enter task's status: " << ANSI_COLOR_RESET;
                            cout << ANSI_COLOR_BABY_BLUE << "\n  [0] Not started\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_BABY_BLUE2 << "  [1] In progress\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_RW6 << "  [2] Completed\n"
                                 << ANSI_COLOR_RESET;
                            int statusIndex;
                            cin >> statusIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid status index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "\n  Enter task priority (e.g., Low, Medium, High): " << ANSI_COLOR_RESET;
                            cout << ANSI_COLOR_BABY_BLUE << "\n  [0] Low\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_BABY_BLUE2 << "  [1] Medium\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_RW6 << "  [2] High\n"
                                 << ANSI_COLOR_RESET;
                            int priorIndex;
                            cin >> priorIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid priority index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "\n  Enter task's due date (YYYY-MM-DD): " << ANSI_COLOR_RESET;
                            cin.ignore();
                            getline(cin, newduedate);

                            if (!regex_match(newduedate, datePattern))
                            {
                                cout << ANSI_COLOR_RED << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            Task newtask(newname, newdesc, category, newstatus, newprior, newduedate);

                            cout << "\n\n";
                            usercollection.EditTask(modifyName, newtask);
                            break;
                        }
                        else if (modifyTaskORCategorychoice == 2)
                        {
                            cout << "\n\n";
                            usercollection.DisplayTasks();

                            string category;

                            cout << ANSI_COLOR_RW6 << "  [0] Uncategorized\n"
                                 << ANSI_COLOR_RESET;
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << ANSI_COLOR_RW6 << "  [" << i + 1 << "] " << *usercollection.categories[i] << ANSI_COLOR_RESET << endl;
                            }
                            cout << ANSI_COLOR_RW7 << "  Enter task's category: " << ANSI_COLOR_RESET;
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid category index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }
                            cout << ANSI_COLOR_RW7 << "  Enter the task name: " << ANSI_COLOR_RESET;
                            cin.ignore();
                            getline(cin, modifyName);

                            usercollection.EditTaskCategory(modifyName, category);

                            break;
                        }
                        else if (modifyTaskORCategorychoice == 3)
                        {
                            break;
                        }
                        else
                        {
                            cout << ANSI_COLOR_RED << "\nInvalid choice.\n"
                                 << ANSI_COLOR_RESET;
                            cin.clear();
                            cin.ignore();
                            Sleep(1500);
                            continue;
                        }
                    }
                }
                else if (modifychoice == 2)
                {
                    ui.ClearScreen();
                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                             << ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
                    }
                    while (true)
                    {
                        if (modifyTaskORCategorychoice == 1)
                        {
                            ui.ClearScreen();
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "\n";
                            cout << ANSI_COLOR_RW7 << "  Enter Task's ID To Edit: " << ANSI_COLOR_RESET;
                            cin >> modifyTaskID;

                            cout << ANSI_COLOR_RW7 << "  Enter task name: " << ANSI_COLOR_RESET;
                            cin.ignore();
                            getline(cin, newname);

                            if (newname.find(' ') != string::npos || newname.find(',') != string::npos)
                            {
                                cout << ANSI_COLOR_RED << "\nTask name cannot contain spaces or comma.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "\n  Enter task description: " << ANSI_COLOR_RESET;
                            getline(cin, newdesc);

                            if (newdesc.find(' ') != string::npos || newdesc.find(',') != string::npos)
                            {
                                cout << ANSI_COLOR_RED << "\nTask description cannot contain spaces or comma.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW6 << "  [0] Uncategorized\n"
                                 << ANSI_COLOR_RESET;
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << ANSI_COLOR_RW6 << "  [" << i + 1 << "] " << *usercollection.categories[i] << ANSI_COLOR_RESET << endl;
                            }
                            cout << ANSI_COLOR_RW7 << "  Enter task's category: " << ANSI_COLOR_RESET;
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid category index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "  Enter task's status: \n"
                                 << ANSI_COLOR_RESET;
                            cout << ANSI_COLOR_BABY_BLUE << "  [0] Not started\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_BABY_BLUE2 << "  [1] In progress\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_RW6 << "  [2] Completed\n"
                                 << ANSI_COLOR_RESET;
                            int statusIndex;
                            cin >> statusIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid status index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "  Enter task priority (e.g., Low, Medium, High): \n"
                                 << ANSI_COLOR_RESET;
                            cout << ANSI_COLOR_BABY_BLUE << "  [0] Low\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_BABY_BLUE2 << "  [1] Medium\n"
                                 << ANSI_COLOR_RESET
                                 << ANSI_COLOR_RW6 << "  [2] High\n"
                                 << ANSI_COLOR_RESET;
                            int priorIndex;
                            cin >> priorIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid priority index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            cout << ANSI_COLOR_RW7 << "\n  Enter task's due date (YYYY-MM-DD): " << ANSI_COLOR_RESET;
                            cin.ignore();
                            getline(cin, newduedate);

                            if (!regex_match(newduedate, datePattern))
                            {
                                cout << ANSI_COLOR_RED << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }

                            Task newtask(newname, newdesc, category, newstatus, newprior, newduedate);

                            cout << "\n\n";
                            usercollection.EditTask(modifyTaskID, newtask);
                            break;
                        }
                        else if (modifyTaskORCategorychoice == 2)
                        {
                            ui.ClearScreen();
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "\n";

                            string category;

                            cout << ANSI_COLOR_RW6 << "  [0] Uncategorized\n"
                                 << ANSI_COLOR_RESET;
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << ANSI_COLOR_RW6 << "  [" << i + 1 << "] " << *usercollection.categories[i] << ANSI_COLOR_RESET << endl;
                            }
                            cout << ANSI_COLOR_RW7 << "  Enter task's category: " << ANSI_COLOR_RESET;
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RED;
                                Sleep(1500);
                                continue;
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
                                cout << ANSI_COLOR_RED << "Invalid category index.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }
                            cout << ANSI_COLOR_RW7 << "  Enter the task ID: " << ANSI_COLOR_RESET;
                            cin >> modifyTaskID;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                                     << ANSI_COLOR_RESET;
                                Sleep(1500);
                                continue;
                            }
                            usercollection.EditTaskCategory(modifyTaskID, category);

                            break;
                        }
                        else if (modifyTaskORCategorychoice == 3)
                        {
                            break;
                        }
                        else
                        {
                            cout << ANSI_COLOR_RED << "\nInvalid choice.\n"
                                 << ANSI_COLOR_RESET;
                            cin.clear();
                            cin.ignore();
                            Sleep(1500);
                            continue;
                        }
                    }
                }
                else if (modifychoice == 3)
                {
                    break;
                }
                else
                {
                    cout << ANSI_COLOR_RED << "\nInvalid choice.\n"
                         << ANSI_COLOR_RESET;
                    cin.clear();
                    cin.ignore();
                    Sleep(1500);
                    continue;
                }
            }
        }
        else if (MainChoice == 4)
        {
            ui.ClearScreen();
            cout << "\n\n";
            usercollection.DisplayTasks();
            cout << "Press enter to continue...\n";
            cin.ignore();
            cin.get();
        }
        else if (MainChoice == 5)
        {
            SearchUI searchUI;
            usercollection.InitializeHashMap();
            while (true)
            {
                int searchchoice;
                ui.ClearScreen();
                searchUI.SearchMainUI();
                cin >> searchchoice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                         << ANSI_COLOR_RESET;
                    Sleep(1500);
                    continue;
                }
                if (searchchoice == 1)
                {
                    ui.ClearScreen();
                    usercollection.DisplayTasks();
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
                    ui.ClearScreen();
                    usercollection.DisplayTasks();
                    searchUI.SearchIDUI();
                    int searchID;
                    cin >> searchID;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                             << ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
                    }
                    Task *temp = usercollection.SearchTask(searchID);
                    if (temp != nullptr)
                    {
                        cout << *temp << endl;
                    }
                }
                else if (searchchoice == 3)
                {
                    ui.ClearScreen();
                    searchUI.SearchPriorUI();
                    cout << ANSI_COLOR_GREENFAINT << "\n  [0] Low\n"
                         << ANSI_COLOR_RESET
                         << ANSI_COLOR_GREENLIGHTER2 << "  [1] Medium\n"
                         << ANSI_COLOR_RESET
                         << ANSI_COLOR_GREENLIGHTER1 << "  [2] High\n"
                         << ANSI_COLOR_RESET;
                    int searchPriorIndex;
                    cin >> searchPriorIndex;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                             << ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
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
                        cout << ANSI_COLOR_RED << "Invalid priority index.\n"
                             << ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
                    }
                    DoublyLinkedList<Task> *temp = usercollection.SearchPriority(prior);
                    DoublyLinkedList<Task>::Node *current = temp->head;
                    while (current != nullptr)
                    {
                        ui.ClearScreen();
                        cout << current->data << endl;
                        if (current->next)
                            cout << ANSI_COLOR_PASTEL_ORANGE << "Press n to go next\n"
                                 << ANSI_COLOR_RESET;
                        if (current->prev)
                            cout << ANSI_COLOR_ORANGE << "Press p to go previous\n"
                                 << ANSI_COLOR_RESET;
                        cout << ANSI_COLOR_ORANGE2 << "Press any other key to exit\n"
                             << ANSI_COLOR_RESET;
                        char choice;
                        cin >> choice;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << ANSI_COLOR_RED << "Invalid input. Please enter a character.\n"
                                 << ANSI_COLOR_RESET;
                            Sleep(1500);
                            continue;
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
                            break;
                        }
                    }
                }
                else if (searchchoice == 4)
                {
                    ui.ClearScreen();
                    searchUI.SearchCategoryUI();
                    for (int i = 0; i < usercollection.categoryCount; i++)
                    {
                        cout << ANSI_COLOR_GREENLIGHTER1 << "  [" << i + 1 << "] " << *usercollection.categories[i] << ANSI_COLOR_RESET << endl;
                    }
                    cout << ANSI_COLOR_RW9 << "  Enter task's category: " << ANSI_COLOR_RESET;
                    int categoryIndex;
                    cin >> categoryIndex;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << ANSI_COLOR_RED << "Invalid input. Please enter a number.\n"
                             << ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
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
                        cout << ANSI_COLOR_RED << "Invalid category index.\n"
                             << ANSI_COLOR_RESET;
                        Sleep(1500);
                        continue;
                    }
                    DoublyLinkedList<Task> *temp = usercollection.SearchCategory(category);
                    DoublyLinkedList<Task>::Node *current = temp->head;
                    while (current != nullptr)
                    {
                        ui.ClearScreen();
                        cout << current->data << endl;
                        if (current->next)
                            cout << ANSI_COLOR_PASTEL_ORANGE << "Press n to go next\n"
                                 << ANSI_COLOR_RESET;
                        if (current->prev)
                            cout << ANSI_COLOR_ORANGE << "Press p to go previous\n"
                                 << ANSI_COLOR_RESET;
                        cout << ANSI_COLOR_ORANGE2 << "Press any other key to exit\n"
                             << ANSI_COLOR_RESET;
                        char choice;
                        cin >> choice;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << ANSI_COLOR_RED << "Invalid input. Please enter a character.\n"
                                 << ANSI_COLOR_RESET;
                            Sleep(1500);
                            continue;
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
                            break;
                        }
                    }
                }
                else if (searchchoice == 5)
                {
                    break;
                }
                else
                {
                    cout << ANSI_COLOR_RED << "\nInvalid choice.\n"
                         << ANSI_COLOR_RESET;
                    cin.clear();
                    cin.ignore();
                    Sleep(1500);
                    continue;
                }
            }
        }
        else if (MainChoice == 6)
        {
            ui.ClearScreen();
            GraphTask graphTask;
            graphTask.BuildGraph(usercollection);
            graphTask.TopologicalSort();
            Queue<Task> *topologicalOrder = graphTask.TopologicalOrder;
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
                            view.zoom(0.9f);
                        else
                            view.zoom(1.1f);
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
                    if (event.type == sf::Event::Resized)
                    {
                        view.setSize(event.size.width, event.size.height);
                    }

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
            ui.ClearScreen();
            CategoryUI categoryUI;
            categoryUI.AddCategoryMenu();
            string categoryname;
            cin.ignore();
            getline(cin, categoryname);
            if (categoryname.find(' ') != string::npos || categoryname.find(',') != string::npos)
            {
                cout << ANSI_COLOR_RED << "\nCategory name cannot contain spaces or commas.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }
            usercollection.AddCategory(categoryname);
        }
        else if (MainChoice == 8)
        {
            ui.ClearScreen();
            CategoryUI categoryUI;
            usercollection.DisplayCategories();
            categoryUI.DeleteCategoryMenu();
            string categoryname;
            cin.ignore();
            cin.clear();
            getline(cin, categoryname);
            if (categoryname.find(' ') != string::npos || categoryname.find(',') != string::npos)
            {
                cout << ANSI_COLOR_RED << "\nCategory name cannot contain spaces or commas.\n"
                     << ANSI_COLOR_RESET;
                Sleep(1500);
                continue;
            }
            for (int i = 0; i < usercollection.taskCount; i++)
            {
                if (usercollection.tasks[i]->category == categoryname)
                {
                    usercollection.tasks[i]->category = "Uncategorized";
                }
            }
            usercollection.RemoveCategory(categoryname);
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
            ui.ClearScreen();
            cout << "\n\n";
            usercollection.DisplayCategories();
            cout << "Press enter to continue...\n";
            cin.ignore();
            cin.get();
        }
        else if (MainChoice == 0)
        {
            ui.ClearScreen();
            loginSystem.LogoutUser(userID);
            cout << ANSI_COLOR_GREEN2 << "Logout Successfully." << ANSI_COLOR_RESET;
            Sleep(1500);
            break;
        }
        else
        {
            cout << ANSI_COLOR_RED << "\nInvalid choice.\n"
                 << ANSI_COLOR_RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(1500);
            continue;
        }
    }
    return 0;
}