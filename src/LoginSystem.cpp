#include <File_Management.h>
#include <LoginSystem.h>
using namespace std;

int User::hashUsername(string username)
{
    int hash = 0;
    for (char c : username)
    {
        hash += c;
        hash *= 31;
        hash -= 7;
        hash %= 10005;
    }
    return hash % 10005;
}

string LoginSystem::hashPassword(string password)
{
    string hashedPassword = password;
    for (char &c : hashedPassword)
    {
        c %= 26;
        c += 'a';
    }
    return hashedPassword;
}

bool LoginSystem::checkduplicate(string username)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->username == username)
        {
            return true;
        }
    }
    return false;
}

void LoginSystem::RegisterUser(string username, string password)
{
    fileManager.AppendFile("./UserCollections/users.csv");
    if (checkduplicate(username))
    {
        fileManager.CloseFile();
        return;
    }
    User *newUser = new User(username, password);
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->userID == newUser->userID)
            newUser->userID++;
    }
    cout << newUser->userID << "," << username << "," << hashPassword(password) << endl;
    fileManager.WriteFile("./UserCollections/Tasks/" + to_string(newUser->userID) + ".csv");
    fileManager.WriteFile("./UserCollections/Categories/" + to_string(newUser->userID) + ".csv");
    fileManager.CloseFile();
    users[userCount++] = newUser;
}

int LoginSystem::LoginUser(string username, string password)
{
    password = hashPassword(password);
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->username == username && users[i]->password == password)
        {
            return users[i]->userID;
        }
    }
    return -1;
}

void LoginSystem::LogoutUser(int userID)
{
    //cout << "User with ID " << userID << " logged out." << endl;
}