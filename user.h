#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "account.h"

using namespace std;
class Library;

class User
{
protected:
    int userId;      // Unique User ID
    string name;     // User's name
    string password; // User's password
    string role;     // "Student", "Faculty", or "Librarian"
    string email;    // User's email address
    Account account; // User's account

public:
    //  Constructor
    User(int userId, const string &name, const string &password, const string &role, const string &email);

    // Getters
    int getUserId() const;
    string getName() const;
    string getPassword() const;
    string getRole() const;
    string getEmail() const;

    // Setters
    void setName(const string &newName);
    void setPassword(const string &newPassword);
    void setEmail(const string &newEmail);

    // Virtual function for borrowing a book (overridden in Student & Faculty)
    virtual void borrowBook(int bookId, Library &library) = 0;
    // Virtual function for returning a book (overridden in Student & Faculty)
    virtual void returnBook(int bookId, Library &library) = 0;
};

#endif // USER_H
