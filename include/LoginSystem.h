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
        userID = hashUsername(u);
    }
    User(int id, string u, string p) : userID(id), username(u), password(p) {}
    int hashUsername(string username);
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

    /* RegisterUser
    Parameter : (string username, string password)
    Description : This function registers a new user by appending the username and password to the users.csv file.
    */
    void RegisterUser(string username, string password);

    /* LoginUser
    Parameter : (string username, string password)
    Description : This function checks if the username and password match any existing user in the users.csv file.
    Returns true if the user is found, false otherwise.
    */
    bool LoginUser(string username, string password);

    /* hashPassword
    Parameter : (string password)
    Description : This function hashes the password using a simple algorithm.
    Returns the hashed password as a string.
    */
    string hashPassword(string password);

    /* decryptPassword
    Parameter : (string hashedPassword)
    Description : This function decrypts the hashed password using a simple algorithm.
    Returns the original password as a string.
    */
    string decryptPassword(string hashedPassword);

    /* checkduplicate
    Parameter : (string username)
    Description : This function checks if the username already exists in the users.csv file.
    Returns true if the username is found, false otherwise.
    If the username is found, it will not register the user again.
    */
    bool checkduplicate(string username);

    /* LogoutUser
    Parameter : (int userID)
    Description : This function logs out the user by removing their session data.
    Returns nothing.
    */
    void LogoutUser(int userID);
};