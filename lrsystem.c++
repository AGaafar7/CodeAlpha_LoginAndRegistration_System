#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct User
{
    string username;
    string password;
};

class UserManager
{
private:
    vector<User> users;
    const string filename = "users.txt";

public:
    UserManager()
    {
        loadUsers();
    }

    void registerUser()
    {
        User newUser;
        cout << "Enter a username: ";
        cin >> newUser.username;
        cout << "Enter a password: ";
        cin >> newUser.password;

        if (validateUsername(newUser.username))
        {
            users.push_back(newUser);
            saveUsers();
            cout << "Registration successful!\n";
        }
        else
        {
            cout << "Username already exists. Please choose a different one.\n";
        }
    }

    bool loginUser(const string &username, const string &password)
    {
        for (const User &user : users)
        {
            if (user.username == username && user.password == password)
            {
                return true; // Credentials match
            }
        }
        return false; // Credentials not found
    }

private:
    bool validateUsername(const string &username)
    {
        for (const User &user : users)
        {
            if (user.username == username)
            {
                return false; // Username already exists
            }
        }
        return true; // Valid username
    }

    void loadUsers()
    {
        ifstream userFile(filename);
        if (userFile.is_open())
        {
            User user;
            while (userFile >> user.username >> user.password)
            {
                users.push_back(user);
            }
            userFile.close();
        }
    }

    void saveUsers()
    {
        ofstream userFile(filename);
        if (userFile.is_open())
        {
            for (const User &user : users)
            {
                userFile << user.username << " " << user.password << endl;
            }
            userFile.close();
        }
    }
};

int main()
{
    UserManager userManager;

    int choice;
    cout << "1. Register\n2. Login\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        userManager.registerUser();
    }
    else if (choice == 2)
    {
        string username, password;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (userManager.loginUser(username, password))
        {
            cout << "Login successful!\n";
        }
        else
        {
            cout << "Invalid credentials. Please try again.\n";
        }
    }
    else
    {
        cout << "Invalid choice.\n";
    }

    return 0;
}
