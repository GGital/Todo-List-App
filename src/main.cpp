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
            loginSystem.LoginUser(username,password);
            //cout << loginSystem.LoginUser(username,password);
            cout << "\nRegister Successfully.\n";
            mainmenu.showMainMenu();

        } else {

            cout << "\nUsername is taken. Please try again later.\n";

        }

    } else if (AuthChoice==2) {

        loginmenu.showLoginMenu();
        cout <<"Username :";
        cin >> username;
        cout <<"Password :";
        cin >> password;

        if (loginSystem.LoginUser(username,password)) {

            cout << "\nLogin Successfully.\n";
            //cout << loginSystem.LoginUser(username,password);
            mainmenu.showMainMenu();

        } else {

            cout << "\nWrong Username or Password. Please try again later.\n";

        }
        
    } else if (AuthChoice==3) {

        return 0;

    } else {

        cout << "\nInvalid choice. Please try again later.\n";
        return 0;
    }

    //--------Main Menu--------

    //Error, I should sleep now D:. Don't forget to get the UserID to be able to logout, also connect all the other choices.
    DoublyLinkedList<Task> taskList;
    
    int MainChoice;
    int userID=loginSystem.LoginUser(username,password);

    UserCollections usercollection(userID, username, password);
    //Task task;

    cin.clear();
    cin >> MainChoice;
    
    while(true){
        if (MainChoice==1) {

            //Add Task here
            string name,desc,status,prior;
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
            Task task(userID, name, desc, status, prior);
            usercollection.AddTask(task);
            taskList.insertAtEnd(task);


            fileManager.WriteFile("./output/output.txt");
            taskList.display();
            fileManager.CloseFile();

            cout << task << "Task Add Successfully.\n";

            mainmenu.showMainMenu();
            cin.clear();
            cin >> MainChoice;
            
            //taskList.insertAtEnd(Task(name, desc, status, prior));

            //dll connect insertatend

        } else if (MainChoice==2) {

            //Delete Task here
            //dll delete

        } else if (MainChoice==3) { 

            //Modify Task here
            //select category, modify name,desc,status,prior
            //int modifymenuchoice;
            //cin >> modifymenuchoice;
            //if(modifychoice==1){cin task}
            //else if(modifychoice==2){cin category}
            //else if(modifychoice==3){ exit }


        } else if (MainChoice==4) {

            //View All Tasks here
            //dll display

        } else if (MainChoice==5) {

            //Search Task here

        } else if (MainChoice==6) {

            //Add Category here   

        } else if (MainChoice==7) {

            //Logout here
            loginSystem.LogoutUser(userID);
            cout << "Logout Successfully.";
            break;

        } else {

            cout << "\nInvalid choice. Please try again later.\n";
            break;
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