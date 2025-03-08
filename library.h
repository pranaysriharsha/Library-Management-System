#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include "book.h"
#include "student.h"
#include "faculty.h"
#include "librarian.h"
#include "user.h"

using namespace std;

class Library
{

private:
    vector<Book> books; // Vector to store books
    vector<Student> students;
    vector<Faculty> faculties;
    vector<Librarian> librarians;

public:
    // Function to initialize the library by reading from Books.txt
    void initialize();

    // Function to display all books
    void displayBooks();

    void displayUsers();                                                     // Function to display all users
    Book *findBookById(int bookId);                                          // Function to find a book by ID
    Student *findStudentById(int rollNo);                                    // Function to find a student by RollNo
    Faculty *findFacultyById(int employeeId);                                // Function to find a faculty by Employee ID
    Librarian *findLibrarianById(int LibrarianId);                           // Function to find a librarian by ID
    void addStudent(Student &student);                                       // Function to add a student to vector<Student> in Library
    void addFaculty(Faculty &faculty);                                       // Function to add a faculty to vector<Faculty> in Library
    void addLibrarian(Librarian &librarian);                                 // Function to add a librarian to vector<Librarian> in Library
    void addBook(Book &book);                                                // Function to add a book to vector<Book> in Library
    void removeUser(int &Id, const string &role, int &roleId);               // Function to remove a user
    void removeBook(int &bookId);                                            // Function to remove a book
    void saveBooksToFile(const string &filename, const vector<Book> &books); // Function to save books changes to file
    // Function to save users changes to file
    void saveUsersToFile(const string &filename, const vector<Student> &students, const vector<Faculty> &faculties, const vector<Librarian> &librarians);
    // Getters
    vector<Book> getBooks();
    vector<Student> getStudents();
    vector<Faculty> getFaculties();
    vector<Librarian> getLibrarians();
    // Function to find a book by ISBN
    Book *findBookbyISBN(string isbn);
    int getStudentIdFromRollNo(int rollNo);
    int getFacultyIdFromEmployeeId(int employeeId);
    int getLibrarianIdFromLibrarianId(int LibrarianId);
    int getBookIdFromISBN(string isbn);
    bool userExists(int id); // Function to check if a user exists
};

#endif // LIBRARY_H
