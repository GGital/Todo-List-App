#include <iostream>
#include <string>
#include <File_Management.h>
#include <cstdlib>

using namespace std;

class User
{
public:
    int userID;
    string username;
    string password;

    User(string u, string p) : username(u), password(p)
    {
        userID = rand() % 1005;
    }
    User(int id, string u, string p) : userID(id), username(u), password(p) {}
};

class LoginSystem
{
private:
    User *users[1005];
    int userCount = 0;

public:
    FileManagement fileManager;
    void ReadUserData()
    {
        fileManager.ReadFile("./UserCollection/users.csv");
        string line;
        while (getline(cin, line))
        {
            int pos = line.find(',');
            int userID = stoi(line.substr(0, pos));
            string username = line.substr(pos + 1, line.find(',', pos + 1) - pos - 1);
            string password = line.substr(line.find(',', pos + 1) + 1);
            password = decryptPassword(password);
            users[userCount++] = new User(userID, username, password);
        }
        fileManager.CloseFile();
        // cout << "User data loaded successfully." << userCount << endl;
    }
    LoginSystem()
    {
        ReadUserData();
    }
    void RegisterUser(string username, string password);
    bool LoginUser(string username, string password);
    string hashPassword(string password);
    string decryptPassword(string hashedPassword);
    bool checkduplicate(string username);
    void LogoutUser(int userID);
};