#include <windows.h>
#include <iostream>
#include <example.h>
#include <File_Management.h>
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
    SetConsoleOutputCP(CP_UTF8);
    FileManagement fileManager;
    Example example;
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
            cout <<ANSI_COLOR_BABY_BLUE2 << "Username :"ANSI_COLOR_RESET;
            cin >> username;
            cout <<ANSI_COLOR_BABY_BLUE4 << "Password :"ANSI_COLOR_RESET;
            cin >> password;

            if (!loginSystem.checkduplicate(username))
            {

                loginSystem.RegisterUser(username, password);
                cout <<ANSI_COLOR_GREEN <<"\nRegistration Successful. Please Login to continue.\n"ANSI_COLOR_RESET;
                break;
            }
            else
            {

                cout <<ANSI_COLOR_RED <<"\nUsername is taken. Please try again later.\n"<<ANSI_COLOR_RESET;
                cin.clear();
                cin.ignore();
                continue;
            }
        }
        else if (AuthChoice == 2)
        {

            loginmenu.showLoginMenu();
            cout <<ANSI_COLOR_BABY_BLUE2 << "Username :"<<ANSI_COLOR_RESET;
            cin >> username;
            cout <<ANSI_COLOR_BABY_BLUE4 << "Password :"<<ANSI_COLOR_RESET;
            cin >> password;

            if (loginSystem.LoginUser(username, password) == -1)
            {

                cout << ANSI_COLOR_RED <<"\nWrong Username or Password. Please try again later.\n"<< ANSI_COLOR_RESET;
                cin.clear();
                cin.ignore();
                continue;
            }
            else
            {

                cout <<ANSI_COLOR_GREEN2 << "\nLogin Successful. Entering the program.\n"<< ANSI_COLOR_RESET;;
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

            cout <<ANSI_COLOR_RED "\nInvalid choice.\n"<< ANSI_COLOR_RESET;
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
            cout << ANSI_COLOR_RW4<<"╭────────────────────────────────────────────────────────────╮\n"<<ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW4<<"│                        Add Menu.                           │\n"<<ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW4<<"│                                                            │\n"<<ANSI_COLOR_RESET;
            cout <<ANSI_COLOR_RW4<< "   Enter task's name: "<<ANSI_COLOR_RESET;
            cin.ignore();
            getline(cin, name);

            cout <<ANSI_COLOR_RW4<< "   Enter task's description: "<<ANSI_COLOR_RESET;
            getline(cin, desc);

            cout <<ANSI_COLOR_RW1<< "   [0] Uncategorized\n\n"<<ANSI_COLOR_RESET;
            for (int i = 0; i < usercollection.categoryCount; i++)
            {
                cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
            }

            cout <<ANSI_COLOR_RW4<< "   Enter task's category: "<<ANSI_COLOR_RESET;
            int categoryIndex;
            cin >> categoryIndex;

            if (categoryIndex == 0)
            {
                category = "Uncategorized";
            }
            else if (categoryIndex > 0 && categoryIndex < usercollection.categoryCount)
            {
                category = *usercollection.categories[categoryIndex - 1];
            }
            else
            {
                cout <<ANSI_COLOR_RED<< "Invalid category index.\n"<<ANSI_COLOR_RESET;
                continue;
            }

            cout <<ANSI_COLOR_RW4<< "\n   Enter task's status: "<<ANSI_COLOR_RESET;
            cout <<ANSI_COLOR_RW1<< "\n   [0] Not started\n"<<ANSI_COLOR_RESET
                 <<ANSI_COLOR_RW2<< "   [1] In progress\n"<<ANSI_COLOR_RESET
                 <<ANSI_COLOR_RW3<< "   [2] Completed\n"<<ANSI_COLOR_RESET;
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
                cout <<ANSI_COLOR_RED "Invalid status index.\n"<<ANSI_COLOR_RESET;
                continue;
            }

            cout << ANSI_COLOR_RW4<<"\n   Enter task's priority (e.g., Low, Medium, High): "<<ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW1<<"\n   [0] Low\n"<<ANSI_COLOR_RESET
                 << ANSI_COLOR_RW2<<"   [1] Medium\n"<<ANSI_COLOR_RESET
                 << ANSI_COLOR_RW3<<"   [2] High\n"<<ANSI_COLOR_RESET;
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
                cout <<ANSI_COLOR_RED<< "Invalid priority index.\n"<<ANSI_COLOR_RESET;
                continue;
            }

            cout << ANSI_COLOR_RW4<< "   Enter task's due date (YYYY-MM-DD): "<<ANSI_COLOR_RESET;
            getline(cin, duedate);
            // if(duedate) input check task add fail


            Task task(name, desc, status, prior, duedate);

            usercollection.AddTask(task);
            taskList.insertAtEnd(task); // dll connect insertatend

            // task add fail? task add success if else
            //  due date testcase without -, as alphabet char, future time
            // remind task where?

            // Priority Testcase ONLY: LOW MEDIUM HIGH. otherwise: invalid
            cout << ANSI_COLOR_RW4<<"\n│                                                            │\n"<<ANSI_COLOR_RESET;
            cout << ANSI_COLOR_RW4<<"╰────────────────────────────────────────────────────────────╯\n"<<ANSI_COLOR_RESET;
            cout << ANSI_COLOR_GREEN2<< "Task Add Successfully.\n"<<ANSI_COLOR_RESET;
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
                    cout <<"\n";

                    cout <<ANSI_COLOR_RW5<< "  Enter Task's Name To Remove: "<<ANSI_COLOR_RESET;
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
                    cout << "\n";

                    cout <<ANSI_COLOR_RW5<< "  Enter Task's ID To Remove: "<<ANSI_COLOR_RESET;
                    cin >> removeTaskID;
                    usercollection.RemoveTask(removeTaskID);

                }
                else if (removechoice == 3)
                {

                    // Exit
                    break;
                }
                else
                {

                    // Invalid Input
                    cout <<ANSI_COLOR_RED <<"\nInvalid choice.\n"<<ANSI_COLOR_RESET;
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

                    while (true)
                    {
                        if (modifyTaskORCategorychoice == 1)
                        {

                            // Modify Task

                            // Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "\n";

                            cout <<ANSI_COLOR_RW7<<"  Enter Task's Name To Edit: "<<ANSI_COLOR_RESET;
                            cin.ignore();
                            getline(cin, modifyName);

                            cout <<ANSI_COLOR_RW7<< "  Enter task name: "<<ANSI_COLOR_RESET;
                            getline(cin, newname);

                            cout <<ANSI_COLOR_RW7<< "  Enter task description: "<<ANSI_COLOR_RESET;
                            getline(cin, newdesc);

                            cout <<ANSI_COLOR_RW6<< "  [0] Uncategorized\n\n"<<ANSI_COLOR_RESET;
                            for (int i = 0; i < usercollection.categoryCount; i++)
                            {
                                cout << "[" << i + 1 << "] " << *usercollection.categories[i] << endl;
                            }
                            cout <<ANSI_COLOR_RW7<< "  Enter task's category: "<<ANSI_COLOR_RESET;
                            int categoryIndex;
                            cin >> categoryIndex;
                            if (categoryIndex == 0)
                            {
                                category = "Uncategorized";
                            }
                            else if (categoryIndex > 0 && categoryIndex < usercollection.categoryCount)
                            {
                                category = *usercollection.categories[categoryIndex - 1];
                            }
                            else
                            {
                                cout <<ANSI_COLOR_RED<< "Invalid category index.\n"<<ANSI_COLOR_RESET;
                                continue;
                            }

                            cout <<ANSI_COLOR_RW7<< "\n  Enter task's status: "<<ANSI_COLOR_RESET;
                            cout <<ANSI_COLOR_BABY_BLUE <<"\n  [0] Not started\n"<<ANSI_COLOR_RESET
                                 <<ANSI_COLOR_BABY_BLUE2 <<"  [1] In progress\n"<<ANSI_COLOR_RESET
                                 <<ANSI_COLOR_RW6<<"  [2] Completed\n"<<ANSI_COLOR_RESET;
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
                                cout <<ANSI_COLOR_RED<< "Invalid status index.\n"<<ANSI_COLOR_RESET;
                                continue;
                            }

                            cout <<ANSI_COLOR_RW7<< "\n  Enter task priority (e.g., Low, Medium, High): "<<ANSI_COLOR_RESET;
                            cout <<ANSI_COLOR_BABY_BLUE<< "\n  [0] Low\n"<<ANSI_COLOR_RESET
                                 <<ANSI_COLOR_BABY_BLUE2<< "  [1] Medium\n"<<ANSI_COLOR_RESET
                                 <<ANSI_COLOR_RW6<< "  [2] High\n"<<ANSI_COLOR_RESET;
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
                                cout <<ANSI_COLOR_RED<< "Invalid priority index.\n"<<ANSI_COLOR_RESET;
                                continue;
                            }

                            cout <<ANSI_COLOR_RW7<< "\n  Enter task's due date (YYYY-MM-DD): "<<ANSI_COLOR_RESET;
                            getline(cin, newduedate);

                            Task newtask(newname, newdesc, newstatus, newprior, newduedate);

                            cout << "\n\n";
                            usercollection.EditTask(modifyName, newtask);
                            break;
                        }
                        else if (modifyTaskORCategorychoice == 2)
                        {

                            // Assign Category Name and Task's Name

                            // Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "\n";
                        }
                        else
                        {

                            // Invalid Input
                            cout <<ANSI_COLOR_RED<< "\nInvalid choice.\n"<<ANSI_COLOR_RESET;
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
                            cout << "\n";
                            cout <<ANSI_COLOR_RW7<< "  Enter Task's ID To Edit: "<<ANSI_COLOR_RESET;
                            cin.ignore();
                            cin >> modifyTaskID;

                            cout <<ANSI_COLOR_RW7<< "  Enter task name: "<<ANSI_COLOR_RESET;
                            cin.ignore();
                            getline(cin, newname);

                            cout <<ANSI_COLOR_RW7<< "\n  Enter task description: "<<ANSI_COLOR_RESET;
                            getline(cin, newdesc);

                            cout <<ANSI_COLOR_RW7<< "\n  Enter task status (e.g., Not started,In progress, Completed): "<<ANSI_COLOR_RESET;
                            getline(cin, newstatus);

                            cout <<ANSI_COLOR_RW7<< "\n  Enter task priority (e.g., Low, Medium, High): "<<ANSI_COLOR_RESET;
                            getline(cin, newprior);

                            cout <<ANSI_COLOR_RW7<< "\n  Enter task's due date (YYYY-MM-DD): "<<ANSI_COLOR_RESET;
                            getline(cin, newduedate);

                            Task newtask(newname, newdesc, newstatus, newprior, newduedate);

                            cout << "\n\n";
                            usercollection.EditTask(modifyTaskID, newtask);
                            break;
                        }
                        else if (modifyTaskORCategorychoice == 2)
                        {

                            // Assign Category Name and Task's ID

                            // Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "\n";

                            string category;

                            cout <<ANSI_COLOR_RW7<< "  Enter the category: "<<ANSI_COLOR_RESET;
                            cin >> category;
                            cout <<ANSI_COLOR_RW7<< "  Enter the task ID: "<<ANSI_COLOR_RESET;
                            cin >> modifyTaskID;

                            Task task(name, desc, status, prior, duedate);

                            hashMap.insert(category, task);
                            DoublyLinkedList<Task> *list = hashMap.getList(category);
                            fileManager.WriteFile("./UserCollections/Categories/" + to_string(userID) + ".csv");
                            list->display();
                            fileManager.CloseFile();

                            // Category Name view, Testcase category name to task
                        }
                        else
                        {

                            // Invalid Input
                            cout <<ANSI_COLOR_RED<< "\nInvalid choice.\n"<<ANSI_COLOR_RESET;
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
                    cout <<ANSI_COLOR_RED<< "\nInvalid choice.\n"<<ANSI_COLOR_RESET;
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
                    getline(cin, searchName);
                }
                else if (searchchoice == 2)
                {

                    // Search by Task ID
                    searchUI.SearchIDUI();
                    int searchID;
                    cin >> searchID;
                }
                else if (searchchoice == 3)
                {

                    // Search by Task Priority
                    searchUI.SearchPriorUI();
                    string searchPrior;
                    getline(cin, searchPrior);
                }
                else if (searchchoice == 4)
                {

                    // Exit
                    break;
                }
                else
                {

                    // Invalid Input
                    cout <<ANSI_COLOR_RED<< "\nInvalid choice.\n"<<ANSI_COLOR_RESET;
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
            cout <<ANSI_COLOR_GREEN2<< "Logout Successfully."<<ANSI_COLOR_RESET;
            break;
        }
        else
        {

            // Invalid Input
            cout <<ANSI_COLOR_RED<< "\nInvalid choice.\n"<<ANSI_COLOR_RESET;
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    return 0;
}