#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "librarian.h"
#include "user.h"
#include "library.h"
#include "student.h"
#include "faculty.h"

using namespace std;

Librarian::Librarian(int userId, int LibrarianId, const string &name, const string &password, const string &email)
    : User(userId, name, password, "Librarian", email), LibrarianId(LibrarianId) {}

int Librarian::getLibrarianId() const { return LibrarianId; }
void Librarian::setLibrarianId(int newLibrarianId) { LibrarianId = newLibrarianId; }
void Librarian::borrowBook(int bookId, Library &library)
{
    cout << "Librarian cannot borrow books" << endl;
}
void Librarian::returnBook(int bookId, Library &library)
{
    cout << "Librarian cannot return books" << endl;
}

void Librarian::addUser(Library &library, int &Id, const string &role, int &roleId, const string &name, const string &password, const string &email)
{
    if (role == "Student")
    {
        Student newStudent(Id, roleId, name, password, email);
        library.addStudent(newStudent);
    }
    else if (role == "Faculty")
    {
        Faculty newFaculty(Id, roleId, name, password, email);
        library.addFaculty(newFaculty);
    }
    else if (role == "Librarian")
    {
        Librarian newLibrarian(Id, roleId, name, password, email);
        library.addLibrarian(newLibrarian);
    }
    else
    {
        cout << "Invalid role" << endl;
    }
}

void Librarian::addBook(Library &library, int &bookId, const string &title, const string &author, const string &publisher, const string &isbn, int year)
{
    Book newBook(bookId, title, author, publisher, isbn, year, "Available", -1);
    library.addBook(newBook);
}

void Librarian::removeUser(Library &library, int &Id, const string &role, int &roleId)
{
    library.removeUser(Id, role, roleId);
}

void Librarian::removeBook(Library &library, int &bookId)
{
    library.removeBook(bookId);
}