#include <iostream>
#include "Doubly-Linked-List.h"
#include "File_Management.h"
#include "Task.h"
using namespace std;

int main()
{
    DoublyLinkedList<int> dll;
    dll.insertAtEnd(10);
    dll.insertAtEnd(30);
    dll.display();

    DoublyLinkedList<double> dll2;
    dll2.insertAtEnd(10.5);
    dll2.insertAtEnd(30.5);
    dll2.display();

    WriteFile("./output/output.txt");
    dll.display();
    dll2.display();
    CloseFile();

    return 0;
}