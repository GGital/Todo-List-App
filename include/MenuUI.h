#pragma once
#include <iostream>
#include <LoginSystem.h>
#include <Task.h>
#include <UI.h>
#include <string.h>
using namespace std;
UI ui;
class LoginSystemUI
{
public:
    void showAuthMenu()
    {
        ui.ClearScreen();
        // LoginSystem authSystem;

        cout << ANSI_COLOR_BABY_BLUE << " (***********************************************************)\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE2 << "(                  " << ANSI_COLOR_RESET ANSI_UNDERLINE << ANSI_BOLD << ANSI_COLOR_BABY_BLUE2 << "  Authentication Menu.   " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE2 << "                  )\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE2 << " (                       " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE << "                      \\)\\)      " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE2 << "    )\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE3 << "( " << ANSI_COLOR_RESET ANSI_COLOR_PASTEL_ORANGE << "    1.Register.    " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE2 << "                        \\(" << ANSI_COLOR_RESET ANSI_COLOR_RED << "๐" << ANSI_COLOR_RESET ANSI_COLOR_RED << " ๐" << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE2 << ")       " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE3 << "    )\n";
        cout << ANSI_COLOR_BABY_BLUE3 << " ( " << ANSI_COLOR_RESET ANSI_COLOR_ORANGE << "   2.Login.        " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE3 << "                          ))Z   " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE3 << "       )\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE4 << "(   " << ANSI_COLOR_RESET ANSI_COLOR_ORANGE2 << "  3.Exit.         " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE4 << "                          /\\       " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE4 << "     )\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE4 << " (               " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE5 << "                                            )\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE5 << "  **********************************************************\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_GREEN2 << "  Enter your choice: " << ANSI_COLOR_RESET;

        cin.clear();
    }
    void showRegisterMenu()
    {
        cout << "\n";
        cout << ANSI_COLOR_BABY_BLUE << "                ╭───────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE3 << "                │ " << ANSI_COLOR_RESET ANSI_COLOR_PASTEL_ORANGE << "  Register Menu. " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE3 << " │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE5 << "                ╰───────────────────╯\n\n"
             << ANSI_COLOR_RESET;
    }
    void showLoginMenu()
    {
        cout << "\n";
        cout << ANSI_COLOR_BABY_BLUE << "                ╭─────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE3 << "                │ " << ANSI_COLOR_RESET ANSI_COLOR_ORANGE << "  Login Menu.  " << ANSI_COLOR_RESET ANSI_COLOR_BABY_BLUE3 << " │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_BABY_BLUE << "                ╰─────────────────╯\n\n"
             << ANSI_COLOR_RESET;
    }
};

class MainMenuUI
{
public:
    void showMainMenu()
    {
        cout << ANSI_COLOR_RW2 << "╭────────────────────────────────────────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW3 << "│         " << ANSI_COLOR_RESET ANSI_COLOR_RW2 << "              Main Menu.             " << ANSI_COLOR_RESET ANSI_COLOR_RW2 << "              │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW3 << "│         " << ANSI_COLOR_RESET ANSI_COLOR_RW3 << "                                     " << ANSI_COLOR_RESET ANSI_COLOR_RW3 << "              │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW4 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW4 << "   1.Add Task.      " << ANSI_COLOR_RESET ANSI_COLOR_RW4 << "                                       │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW5 << "   2.Delete Task.   " << ANSI_COLOR_RESET ANSI_COLOR_RW5 << "                                       │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW7 << "   3.Modify Task.   " << ANSI_COLOR_RESET ANSI_COLOR_RW7 << "                                       │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW8 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW8 << "   4.View All Tasks." << ANSI_COLOR_RESET ANSI_COLOR_RW8 << "                                       │\n";
        cout << ANSI_COLOR_RW9 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW9 << "   5.Search Task.   " << ANSI_COLOR_RESET ANSI_COLOR_RW9 << "                                       │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW11 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW11 << "   6.Topological Task.  " << ANSI_COLOR_RESET ANSI_COLOR_RW11 << "                                   │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW14 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW14 << "   7.Add Category.      " << ANSI_COLOR_RESET ANSI_COLOR_RW14 << "                                   │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW15 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_RW15 << "   8.Delete Category.   " << ANSI_COLOR_RESET ANSI_COLOR_RW15 << "                                   │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RED << "╰────────────────────────────────────────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_GREEN2 << "Enter your choice: " << ANSI_COLOR_RESET;
        cin.clear();
    }
};

class RemoveMenuUI
{
public:
    void showRemoveMenu()
    {

        cout << ANSI_COLOR_RW5 << "╭────────────────────────────────────────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "│                      Remove Menu.                          │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "│                                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "│   1.Remove By Name.                                        │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "│   2.Remove By Task ID.                                     │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_ORANGE2 << "  3.Exit.   " << ANSI_COLOR_RESET ANSI_COLOR_RW5 << "                                              │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "│                                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW5 << "╰────────────────────────────────────────────────────────────╯\n"
             << ANSI_COLOR_RESET;

        cout << ANSI_COLOR_GREEN2 << "Enter your choice: " << ANSI_COLOR_RESET;
        cin.clear();
    }
};

class ModifyMenuUI
{
public:
    void showModifyMenu()
    {

        cout << ANSI_COLOR_RW7 << "╭────────────────────────────────────────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│                       Modify Menu.                         │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│                                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│     1.Modify By Name.                                      │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│     2.Modify By Task ID.                                   │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│ " << ANSI_COLOR_RESET ANSI_COLOR_ORANGE2 << "    3.Exit.    " << ANSI_COLOR_RESET ANSI_COLOR_RW7 << "                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│                                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "╰────────────────────────────────────────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_GREEN2 << "Enter your choice: " << ANSI_COLOR_RESET;
        cin.clear();
    }
    void ModifyTaskORCategoryMenu()
    {

        cout << ANSI_COLOR_RW7 << "╭────────────────────────────────────────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│                      Modify Menu.                          │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│                                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│     1.Modify tasks.                                        │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│     2.Assign Task's Category.                              │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│  " << ANSI_COLOR_RESET ANSI_COLOR_ORANGE2 << "   3.Exit.                  " << ANSI_COLOR_RESET ANSI_COLOR_RW7 << "                              │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "│                                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW7 << "╰────────────────────────────────────────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_GREEN2 << "Enter your choice: " << ANSI_COLOR_RESET;
        cin.clear();
    }
};

class SearchUI
{
public:
    void SearchMainUI()
    {

        cout << ANSI_COLOR_RW9 << "╭────────────────────────────────────────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│                        Search Menu.                        │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│     1.Search By Name.                                      │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│     2.Search By Task ID.\n                                 │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│     3.Search By Priority Level.                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│  " << ANSI_COLOR_RESET ANSI_COLOR_ORANGE2 << "   4.Exit.         " << ANSI_COLOR_RESET ANSI_COLOR_RW9 << "                                       │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│                                                            │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "╰────────────────────────────────────────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_GREEN2 << "Enter your choice: " << ANSI_COLOR_RESET;
        cin.clear();
    }
    void SearchNameUI()
    {

        cout << ANSI_COLOR_RW9 << "╭──────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│    Search By Name Menu.  │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "╰──────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "  Enter Task's Name: " << ANSI_COLOR_RESET;
        cin.clear();
    }
    void SearchIDUI()
    {

        cout << ANSI_COLOR_RW9 << "╭──────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│     Search By ID Menu.   │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "╰──────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "  Enter Task's ID: " << ANSI_COLOR_RESET;
        cin.clear();
    }
    void SearchPriorUI()
    {

        cout << ANSI_COLOR_RW9 << "╭──────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "│ Search By Priority Menu. │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "╰──────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW9 << "  Enter Task's Priority: " << ANSI_COLOR_RESET;
        cin.clear();
    }
    void SearchCategoryUI()
    {

        cout << "***************\n";
        cout << "Search By Category Menu.\n\n";
        cout << "Enter Task's Category: ";
    }
};

class CategoryUI
{
public:
    void AddCategoryMenu()
    {

        cout << ANSI_COLOR_RW14 << "╭──────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW14 << "│  Add the Category Menu.  │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW14 << "╰──────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW14 << "  Enter your category name: " << ANSI_COLOR_RESET;
        cin.clear();
    }
    void DeleteCategoryMenu()
    {

        cout << ANSI_COLOR_RW15 << "╭───────────────────────────╮\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW15 << "│ Delete the Category Menu. │\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW15 << "╰───────────────────────────╯\n\n"
             << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_RW15 << "  Enter your category name: " << ANSI_COLOR_RESET;
        cin.clear();
    }
};
