#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "user.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Library;

class Librarian : public User
{
private:
    int LibrarianId;

public:
    // Constructor
    Librarian(int userId, int LibrarianId, const string &name, const string &password, const string &email);
    int getLibrarianId() const;
    void setLibrarianId(int newLibrarianId);
    void borrowBook(int bookId, Library &library) override;
    void returnBook(int bookId, Library &library) override;
    // Add a user
    void addUser(Library &library, int &Id, const string &role, int &roleId, const string &name, const string &password, const string &email);
    // Add a book
    void addBook(Library &library, int &bookId, const string &title, const string &author, const string &publisher, const string &isbn, int year);
    // Remove a user
    void removeUser(Library &library, int &Id, const string &role, int &roleId);
    // Remove a book
    void removeBook(Library &library, int &bookId);
};

#endif // LIBRARIAN_H
