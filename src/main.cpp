#include <iostream>
#include <example.h>
#include <File_Management.h>
#include <regex>
#include "Doubly-Linked-List.h"
#include "Min-Priority-Queue.h"
#include "Max-Priority-Queue.h"
#include "Task.h"
#include "LoginSystem.h"
#include "HashMapWithDLL.h"
#include "UserCollections.h"
#include <UI.h>
#include "MenuUI.h"
using namespace std;

int main()
{
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

        if (AuthChoice == 1)
        {

            loginmenu.showRegisterMenu();
            cout << "Username :";
            cin >> username;
            cout << "Password :";
            cin >> password;

            if (!loginSystem.checkduplicate(username))
            {

                loginSystem.RegisterUser(username, password);
                cout << "\nRegistration Successful. Please Login to continue.\n";
                break;
            }
            else
            {

                cout << "\nUsername is taken. Please try again later.\n";
                cin.clear();
                cin.ignore();
                continue;
            }
        }
        else if (AuthChoice == 2)
        {

            loginmenu.showLoginMenu();
            cout << "Username :";
            cin >> username;
            cout << "Password :";
            cin >> password;

            if (loginSystem.LoginUser(username, password) == -1)
            {

                cout << "\nWrong Username or Password. Please try again later.\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            else
            {

                cout << "\nLogin Successful. Entering the program.\n";
                // cout << loginSystem.LoginUser(username,password);
                mainmenu.showMainMenu();
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
            cin.clear();
            cin.ignore();
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
        cin.clear();
        cin >> MainChoice;

        if (MainChoice == 1)
        {

            //--------Add Task Menu--------

            cout << "Enter task's name: ";
            cin.ignore();
            getline(cin, name);

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

                if (modifychoice == 1)
                {

                    // Modify by Task Name

                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;
                    cin.clear();
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
                    else
                    {
                        cout << "Task not found.\n";
                    }
                }
                else if (searchchoice == 2)
                {

                    // Search by Task ID
                    searchUI.SearchIDUI();
                    int searchID;
                    cin >> searchID;
                    Task *temp = usercollection.SearchTask(searchID);
                    if (temp != nullptr)
                    {
                        cout << *temp << endl;
                    }
                    else
                    {
                        cout << "Task not found.\n";
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
                    if (temp != nullptr)
                    {
                        temp->display();
                    }
                    else
                    {
                        cout << "Task not found.\n";
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
                    if (temp != nullptr)
                    {
                        temp->display();
                    }
                    else
                    {
                        cout << "Task not found.\n";
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
            // Susu na Teerak <3
        }
        else if (MainChoice == 7)
        {

            //--------Add Category Menu--------

            CategoryUI categoryUI;
            categoryUI.AddCategoryMenu();
            string categoryname;
            cin >> categoryname;
            usercollection.AddCategory(categoryname);
        }
        else if (MainChoice == 8)
        {

            //--------Delete Category Menu--------

            CategoryUI categoryUI;
            categoryUI.DeleteCategoryMenu();
            string categoryname;
            cin >> categoryname;
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
            cin.ignore();
            continue;
        }
    }
    return 0;
}