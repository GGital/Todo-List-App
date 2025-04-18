#include <File_Management.h>
#include <LoginSystem.h>
using namespace std;

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
        cout << "Username already exists." << endl;
        return;
    }
    User *newUser = new User(username, password);
    cout << newUser->userID << "," << username << "," << password << endl;
    fileManager.CloseFile();
    users[userCount++] = newUser;
}

bool LoginSystem::LoginUser(string username, string password)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->username == username && users[i]->password == password)
        {
            return true;
        }
    }
    return false;
}

void LoginSystem::LogoutUser(int userID)
{
    cout << "User with ID " << userID << " logged out." << endl;
}