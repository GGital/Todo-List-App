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
    FileManagement fileManager;
    Example example;
    // enable_ansi_colors();
    //example.Greet();
    //example.Farewell();

    //--------Authentication Menu--------

    LoginSystem loginSystem;
    LoginSystemUI loginmenu;
    MainMenuUI mainmenu;

    string username,password;

    while(true){

        loginmenu.showAuthMenu();
        int AuthChoice;
        cin.clear();
        cin >> AuthChoice;
        
        if (AuthChoice==1) {

            loginmenu.showRegisterMenu();
            cout <<"Username :"; 
            cin >> username;
            cout <<"Password :";
            cin >> password;

            if (!loginSystem.checkduplicate(username)) {

                loginSystem.RegisterUser(username,password);
                cout << "\nRegistration Successful. Please Login to continue.\n";
                break;

            } else {

                cout << "\nUsername is taken. Please try again later.\n";
                cin.clear();
                cin.ignore();
                continue;

            }

        } else if (AuthChoice==2) {
            
            loginmenu.showLoginMenu();
            cout <<"Username :";
            cin >> username;
            cout <<"Password :";
            cin >> password;
            
            if (loginSystem.LoginUser(username,password)==-1) {
                
                cout << "\nWrong Username or Password. Please try again later.\n";
                cin.clear();
                cin.ignore();
                continue;

            } else {

                cout << "\nLogin Successful. Entering the program.\n";
                //cout << loginSystem.LoginUser(username,password);
                mainmenu.showMainMenu();
                break;
                

            }
            
        } else if (AuthChoice==3) {

            return 0;

        } else {

            cout << "\nInvalid choice.\n";
            cin.clear();
            cin.ignore();
            continue;

        }
    }

    //--------Main Menu--------

    DoublyLinkedList<Task> taskList;
    
    int MainChoice;
    int userID=loginSystem.LoginUser(username,password);

    UserCollections usercollection(userID, username, password);
    
    string name,desc,status,prior,duedate;

    while(true){

        mainmenu.showMainMenu();
        cin.clear();
        cin >> MainChoice;
        
        if (MainChoice==1) {

            //--------Add Task Menu--------

            cout << "Enter task's name: ";
            cin.ignore();
            getline(cin,name);

            cout << "Enter task's description: ";
            getline(cin,desc);

            cout << "Enter task's status (e.g., Not started,In progress, Completed): ";
            getline(cin,status);

            cout << "Enter task's priority (e.g., Low, Medium, High): ";
            getline(cin,prior);

            cout << "Enter task's due date (YYYY-MM-DD): ";
            getline(cin,duedate);
            // if(duedate) input check task add fail

            cout << "\n***************\n";
            Task task(name, desc, status, prior,duedate);

            usercollection.AddTask(task);
            taskList.insertAtEnd(task); //dll connect insertatend
            

            //task add fail? task add success if else
            // due date testcase without -, as alphabet char, future time
            //remind task where?

            //Priority Testcase ONLY: LOW MEDIUM HIGH. otherwise: invalid
            cout << "Task Add Successfully.\n";
            

        } else if (MainChoice==2) {

            while(true){
                
                //--------Delete Task Menu--------

                int removechoice;
                int removeTaskID;
                string removeName;

                RemoveMenuUI removemenuUI;
                removemenuUI.showRemoveMenu();
                cin.clear();
                cin >> removechoice;

                if(removechoice==1) {

                    //Delete by Task Name

                    //Task Viewing First
                    cout << "\n\n";
                    usercollection.DisplayTasks();
                    cout << "***************\n";

                    cout << "Enter Task's Name To Remove: ";
                    cin >> removeName;
                    usercollection.RemoveTask(removeName);
                    //What if that name doesn't exist in file?
                    break;

                } else if(removechoice==2) {

                    //Delete by Task ID

                    //Task Viewing First
                    cout << "\n\n";
                    usercollection.DisplayTasks();
                    cout << "***************\n";

                    cout << "Enter Task's ID To Remove: ";
                    cin >> removeTaskID;
                    usercollection.RemoveTask(removeTaskID);
                    break;


                } else if(removechoice==3) {

                    //Exit
                    break;

                } else {

                    //Invalid Input
                    cout << "\nInvalid choice.\n";
                    cin.clear();
                    cin.ignore();
                    continue;

                }
                
                //Show all tasks

            }
            

        } else if (MainChoice==3) { 
            
            while(true){

                string newname,newdesc,newstatus,newprior,newduedate;
                
                //--------Modify Task Menu--------

                int modifychoice;
                int modifyTaskID;
                string modifyName;
                HashMapDLL<string, Task> hashMap(1000);

                ModifyMenuUI modifymenuUI;
                modifymenuUI.showModifyMenu();
                cin.clear();
                cin >> modifychoice;

                if(modifychoice==1) {

                    //Modify by Task Name

                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;

                    while(true){
                        if (modifyTaskORCategorychoice==1) {

                            //Modify Task

                            //Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";

                            cout << "Enter Task's Name To Edit: ";
                            cin.ignore();
                            getline(cin,modifyName);

                            cout << "Enter task name: ";
                            getline(cin,newname);

                            cout << "Enter task description: ";
                            getline(cin,newdesc);

                            cout << "Enter task status (e.g., Not started,In progress, Completed): ";
                            getline(cin,newstatus);

                            cout << "Enter task priority (e.g., Low, Medium, High): ";
                            getline(cin,newprior);

                            cout << "Enter task's due date (YYYY-MM-DD): ";
                            getline(cin,newduedate);

                            Task newtask(newname, newdesc, newstatus, newprior,newduedate);

                            cout << "\n***************\n";
                            usercollection.EditTask(modifyName, newtask);
                            break;

                        } else if (modifyTaskORCategorychoice==2) {

                            //Assign Category Name and Task's Name

                            //Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";

                        } else {

                            //Invalid Input
                            cout << "\nInvalid choice.\n";
                            cin.clear();
                            cin.ignore();
                            continue;

                        }
                        
                    }

                } else if(modifychoice==2) {

                    //Modify by Task ID

                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;

                    while(true){
                        if (modifyTaskORCategorychoice==1) {

                            //Modify Task

                            //Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";
                            cout << "Enter Task's ID To Edit: ";
                            cin >> modifyTaskID;
                            //usercollection.EditTask(modifyTaskID,newtask);

                            cout << "Enter task name: ";
                            getline(cin,newname);

                            cout << "Enter task description: ";
                            getline(cin,newdesc);

                            cout << "Enter task status (e.g., Not started,In progress, Completed): ";
                            getline(cin,newstatus);

                            cout << "Enter task priority (e.g., Low, Medium, High): ";
                            getline(cin,newprior);

                            cout << "Enter task's due date (YYYY-MM-DD): ";
                            getline(cin,newduedate);

                            Task newtask(newname, newdesc, newstatus, newprior,newduedate);

                            cout << "\n***************\n";
                            usercollection.EditTask(modifyTaskID, newtask);

                        } else if (modifyTaskORCategorychoice==2) {

                            //Assign Category Name and Task's ID

                            //Task Viewing First
                            cout << "\n\n";
                            usercollection.DisplayTasks();
                            cout << "***************\n";
                            
                            string category;
                            
                            cout << "Enter the category: ";
                            cin >> category;
                            cout << "Enter the task ID: ";
                            cin >> modifyTaskID;

                            Task task(name,desc,status,prior,duedate);

                            hashMap.insert(category, task);
                            DoublyLinkedList<Task> *list = hashMap.getList(category);
                            fileManager.WriteFile("./UserCollections/Categories/" + to_string(userID) + ".csv");
                            list->display();
                            fileManager.CloseFile();
                            
                            

                            // Category Name view, Testcase category name to task

                        } else {

                            //Invalid Input
                            cout << "\nInvalid choice.\n";
                            cin.clear();
                            cin.ignore();
                            continue;

                        }
                        
                    }

                } else if(modifychoice==3) {

                    //Exit
                    break;

                } else {

                    //Invalid Input
                    cout << "\nInvalid choice.\n";
                    cin.clear();
                    cin.ignore();
                    continue;

                }
                
                //Show all tasks
            }


        } else if (MainChoice==4) {

            //--------View Task Menu[By Task ID]--------
            
            cout << "\n\n";
            usercollection.DisplayTasks();
            //break;
            //No Task Testcase

        } else if (MainChoice==5) {

            //Search Task here
            SearchUI searchUI;

            while(true) {

                int searchchoice;
                searchUI.SearchMainUI();
                cin >> searchchoice;
                
                if (searchchoice==1) {
                    
                    //Search by Task Name
                    searchUI.SearchNameUI();
                    string searchName;
                    getline(cin,searchName);

                } else if (searchchoice==2) {

                    //Search by Task ID
                    searchUI.SearchIDUI();
                    int searchID;
                    cin >> searchID;

                } else if (searchchoice==3) {

                    //Search by Task Priority
                    searchUI.SearchPriorUI();
                    string searchPrior;
                    getline(cin,searchPrior);
                    
                } else if (searchchoice==4) {

                    //Exit
                    break;

                } else {

                    //Invalid Input
                    cout << "\nInvalid choice.\n";
                    cin.clear();
                    cin.ignore();
                    continue;

                }
            
            }

            //No Task Testcase

        } else if (MainChoice==6) {

            //--------Topological Task Menu--------
            //Susu na 

        } else if (MainChoice==7) {

            //--------Add Category Menu--------

            CategoryUI categoryUI;
            categoryUI.AddCategoryMenu();
            string categoryname;
            cin >> categoryname;
            usercollection.AddCategory(categoryname);

        } else if (MainChoice==8) {

            //--------Delete Category Menu--------

            CategoryUI categoryUI;
            categoryUI.DeleteCategoryMenu();
            string categoryname;
            cin >> categoryname;
            usercollection.RemoveCategory(categoryname);

        } else if (MainChoice==9) {

            //--------Logout Menu--------

            loginSystem.LogoutUser(userID);
            cout << "Logout Successfully.";
            break;

        } else {

            //Invalid Input 
            cout << "\nInvalid choice.\n";
            cin.clear();
            cin.ignore();
            continue;

        }
    }
    /*DoublyLinkedList<int> dll;
    dll.insertAtEnd(10);
    dll.insertAtEnd(30);
    dll.display();

    DoublyLinkedList<double> dll2;
    dll2.insertAtEnd(10.5);
    dll2.insertAtEnd(30.5);
    dll2.display();

    MinPriorityQueue<int> minQueue;
    minQueue.insert(10, 1);
    minQueue.insert(20, 2);
    minQueue.insert(30, 3);

    MaxPriorityQueue<int> maxQueue;
    maxQueue.insert(10, 1);
    maxQueue.insert(20, 2);
    maxQueue.insert(30, 3);

    DoublyLinkedList<Task> taskList;
    taskList.insertAtEnd(Task("Task 1", "Description 1", "In Progress", "High"));
    taskList.insertAtEnd(Task("Task 2", "Description 2", "Completed", "Medium"));

    fileManager.WriteFile("./output/output.txt");
    taskList.display();
    fileManager.CloseFile();

    LoginSystem loginSystem;
    loginSystem.RegisterUser("Gital", "Madiwa");
    cout << loginSystem.LoginUser("Gital", "Madiwa") << endl;
    */

    /*HashMapDLL<string, Task> hashMap(1000);
    Task task1("Task 1", "Description 1", "In Progress", "High");
    Task task2("Task 2", "Description 2", "Completed", "Medium");
    hashMap.insert("Daily Work", task1);
    hashMap.insert("Career", task2);
    DoublyLinkedList<Task> *list = hashMap.getList("Daily Work");
    //DoublyLinkedList<Task> *list = hashMap.getList("Career");
    fileManager.WriteFile("./output/output.txt");
    list->display();
    fileManager.CloseFile();

    LoginSystem loginSystem;
    loginSystem.RegisterUser("Test", "GG");
    cout << loginSystem.LoginUser("Test", "GG") << endl;

    UserCollections userCollection(1, "Test", "GG");

    cout << ANSI_COLOR_RED << "Hello World!" << ANSI_COLOR_RESET << endl;*/
    return 0;
}