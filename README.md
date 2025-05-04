# Todo-List-App

## **Project Overview**

Managing tasks efficiently is a growing challenge in today’s fast-paced world. Traditional methods like sticky notes and basic planners often lack flexibility, prioritization, and reminder features, leading to missed deadlines and reduced productivity.

This ToDo Application offers a simple yet powerful solution to create, organize, and track tasks effectively.

<p align="center"><img src="https://github.com/user-attachments/assets/125a83dc-8691-42a9-8627-c1b7a153bb8c"> <img height=300px src="https://github.com/user-attachments/assets/0a22b7f5-ad0c-4027-9749-a5a4042d2417"></p>

## **Key Features**

- Managing Task (Add, Remove, Checking status, Modify)
- Categorizing Tasks
- Filter & Searching
- Task Ordering (Topological sorting)
- Reminding Upcoming Tasks

## Topological Sorting Example
<p align="center"><img src="https://github.com/user-attachments/assets/027d5078-232b-457a-83de-464eb0caf9b5"></p>


## **Project Structure**

- `UserCollections` - Directory storing user-specific data
- `include` - Directory storing all header files for data structure or class implementation
- `src` - Directory storing function implementation
- `app.exe` Executable program made by `MAKEFILE`

## **Data Structure Used**

- Priority Queue – To handle priority-based tasks efficiently
- Doubly Linked list - To traverse through tasks forward and backward. Also allowing inserting and deletion
- Hash Table – for searching and categorization
- Graph – for managing sequential tasks

## **Usage**

- To compile the project:
  ```
  make
  ```
- To run the executable:
  ```
  make run
  ```
- To clean the build files:
  ```
  make clean
  ```

## Requirements

**MinGW has to be version of 13.1.0 only**

### **This project is a part of CPE112 (Data Structure and Algorithms) at KMUTT**

---
