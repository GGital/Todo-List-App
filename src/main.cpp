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
    loginmenu.showAuthMenu();
    int AuthChoice;
    cin >> AuthChoice;
    //cout << AuthChoice;
    string username,password;
    if (AuthChoice==1) {

        loginmenu.showRegisterMenu();
        cout <<"Username :";
        cin >> username;
        cout <<"Password :";
        cin >> password;

        if (!loginSystem.checkduplicate(username)) {

            loginSystem.RegisterUser(username,password);
            //cout << loginSystem.LoginUser(username,password);
            cout << "\nRegistration Successful. Please Login to continue.\n";
            return 0;

        } else {

            cout << "\nUsername is taken. Please try again later.\n";
            return 0;

        }

    } else if (AuthChoice==2) {
        
        loginmenu.showLoginMenu();
        cout <<"Username :";
        cin >> username;
        cout <<"Password :";
        cin >> password;
        
        if (loginSystem.LoginUser(username,password)==-1) {
            
            cout << "\nWrong Username or Password. Please try again later.\n";
            return 0;

        } else {

            cout << "\nLogin Successful. Entering the program.\n";
            //cout << loginSystem.LoginUser(username,password);
            mainmenu.showMainMenu();
            

        }
        
    } else if (AuthChoice==3) {

        return 0;

    } else {

        cout << "\nInvalid choice. Please try again later.\n";
        return 0;
    }

    //--------Main Menu--------

    DoublyLinkedList<Task> taskList;
    
    int MainChoice;
    int userID=loginSystem.LoginUser(username,password);

    UserCollections usercollection(userID, username, password);
    
    string name,desc,status,prior;

    while(true){

        mainmenu.showMainMenu();
        cin.clear();
        cin >> MainChoice;

        if (MainChoice==1) {

            //Add Task here

            cout << "Enter task name: ";
            cin.ignore();
            getline(cin,name);

            cout << "Enter task description: ";
            getline(cin,desc);

            cout << "Enter task status (e.g., Not started,In progress, Completed): ";
            getline(cin,status);

            cout << "Enter task priority (e.g., Low, Medium, High): ";
            getline(cin,prior);

            cout << "\n***************\n";
            Task task(name, desc, status, prior);
            //Due date input
            usercollection.AddTask(task);
            taskList.insertAtEnd(task); //dll connect insertatend

            //if the task name already add, cout in terminal not in file csv
            cout << "Task Add Successfully.\n";
            

        } else if (MainChoice==2) {

            while(true){
                
                //Delete Task here

                int removechoice;
                int removeTaskID;
                string removeName;

                RemoveMenuUI removemenuUI;
                removemenuUI.showRemoveMenu();
                cin.clear();
                cin >> removechoice;

                if(removechoice==1) {

                    //Delete by Task Name

                    cout << "Enter Task's Name To Remove: ";
                    cin >> removeName;
                    usercollection.RemoveTask(removeName);
                    //What if that name doesn't exist in file?
                    break;

                } else if(removechoice==2) {

                    //Delete by Task ID

                    cout << "Enter Task's ID To Remove: ";
                    cin >> removeTaskID;
                    usercollection.RemoveTask(removeTaskID);
                    break;


                } else if(removechoice==3) {

                    break;

                } else {

                    cout << "\nInvalid choice.\n";

                }
                
                //Show all tasks

                //No Task Testcase , no task at all, no task matched
            }
            

        } else if (MainChoice==3) { 
            
            while(true){
                Task task(name, desc, status, prior);
                
                //Modify Task here

                int modifychoice;
                int modifyTaskID;
                string modifyName;

                ModifyMenuUI modifymenuUI;
                modifymenuUI.showModifyMenu();
                cin.clear();
                cin >> modifychoice;

                if(modifychoice==1) {

                    //Modify by Task Name

                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;

                    if (modifyTaskORCategorychoice==1) {

                        //Show All tasks
                        cout << "Enter Task's Name To Edit: ";
                        cin >> modifyName;
                        usercollection.EditTask(modifyName,task);

                    } else if (modifyTaskORCategorychoice==2) {

                        //Show All tasks
                        //Assign Category Name and Task's Name

                    } else {

                        break;

                    }
                    
                    //HELPPPPPPPP

                    //What if that name doesn't exist in file?
                    break;

                } else if(modifychoice==2) {

                    //Modify by Task ID

                    int modifyTaskORCategorychoice;
                    modifymenuUI.ModifyTaskORCategoryMenu();
                    cin >> modifyTaskORCategorychoice;

                    if (modifyTaskORCategorychoice==1) {

                        //Show All tasks
                        cout << "Enter Task's ID To Edit: ";
                        cin >> modifyTaskID;
                        usercollection.EditTask(modifyTaskID,task);

                    } else if (modifyTaskORCategorychoice==2) {

                        //Show All tasks
                        //Assign Category Name and Task's ID

                    } else {

                        break;

                    }
                    
                    //HELPPPPPPPP

                    //What if that ID doesn't exist in file?
                    break;


                } else if(modifychoice==3) {

                    break;

                } else {

                    cout << "\nInvalid choice.\n";

                }
                
                //Show all tasks

                //No Task Testcase
            }


        } else if (MainChoice==4) {

            //View All Tasks here
            
            //View by Task ID order
            //usercollection.ReadTasksFromFile();
            //break;
            //No Task Testcase

        } else if (MainChoice==5) {

            //Search Task here

            //Search by Task Name

            //Search by Task ID

            //Search by Task Priority

            //No Task Testcase

        } else if (MainChoice==6) {

            //Topological Task here
            //Susu na 

        } else if (MainChoice==7) {

            //Add Category here

            CategoryUI categoryUI;
            categoryUI.AddCategoryMenu();
            string categoryname;
            cin >> categoryname;
            usercollection.AddCategory(categoryname);

        } else if (MainChoice==8) {

            //Delete Category here

            CategoryUI categoryUI;
            categoryUI.DeleteCategoryMenu();
            string categoryname;
            cin >> categoryname;
            usercollection.RemoveCategory(categoryname);

        } else if (MainChoice==9) {

            //Logout here

            loginSystem.LogoutUser(userID);
            cout << "Logout Successfully.";
            break;

        } else {

            cout << "\nInvalid choice.\n";
            break;


            //Retry in loop lei
        }//new choice toposort
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
    DoublyLinkedList<Task> *list = hashMap.getList("Career");
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