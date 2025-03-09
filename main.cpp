#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "user.h"
#include "library.h"
#include "book.h"
#include "account.h"
#include "student.h"
#include "faculty.h"
#include "librarian.h"

using namespace std;

// Save Data to file
void SaveData(Library &library)
{

    library.saveBooksToFile("Books.txt", library.getBooks());                                                     // Save books to file
    library.saveUsersToFile("Users.txt", library.getStudents(), library.getFaculties(), library.getLibrarians()); // Save users to file
}

int main()
{
    Library library;      // Create Library object
    library.initialize(); // Load data from file using initialize function

    cout << "Welcome to Library Management System" << endl;
    cout << "------------------------------------" << endl;
    while (1)
    {
        if (cin.fail())
        {
            cout << "Error in input type" << endl;
            cout << "Please Give a valid input next time" << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "------------------------------------" << endl;
        cout << "Enter 1 to login as Student" << endl;
        cout << "Enter 2 to login as Faculty" << endl;
        cout << "Enter 3 to login as Librarian" << endl;
        cout << "Enter 4 to Terminate the Program" << endl;
        cout << "------------------------------------" << endl;

        int choice;
        cout << "Enter your choice here: ";
        cin >> choice;
        if (choice == 1)
        {
            // Student Login
            cout << "Enter Roll Number:\n";
            int rollNo;
            cin >> rollNo;
            Student *student = library.findStudentById(rollNo);
            if (student)
            {
                cout << "Enter Password:\n";
                string password;
                cin >> password;
                if (student->getPassword() == password)
                {
                    // If password is correct then login
                    cout << "Login Successful" << endl;
                    cout << "Welcome " << student->getName() << endl;
                    cout << "------------------------------------" << endl;
                    while (1)
                    {
                        if (cin.fail())
                        {
                            cout << "Error in input type" << endl;
                            cin.clear(); // Clear error state
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout << "------------------------------------" << endl;
                        cout << "Enter 1 to display all books" << endl;
                        cout << "Enter 2 to borrow a book" << endl;
                        cout << "Enter 3 to return a book" << endl;
                        cout << "Enter 4 to display borrowed books" << endl;
                        cout << "Enter 5 to display your history" << endl;
                        cout << "Enter 6 to display fine" << endl;
                        cout << "Enter 7 to payfine" << endl;
                        cout << "Enter 8 to display overdue books" << endl;
                        cout << "Enter 9 to exit" << endl;
                        cout << "------------------------------------" << endl;
                        int studentChoice;
                        cout << "Enter your choice here: ";

                        cin >> studentChoice;
                        if (studentChoice == 1)
                        {
                            // Display all books
                            cout << "------------------------------------" << endl;
                            library.displayBooks();
                            cout << "------------------------------------" << endl;
                        }
                        else if (studentChoice == 2)
                        {
                            // Borrow a book
                            cout << "\n Enter Book ID you want to borrow: \n"
                                 << endl;
                            int bookid;
                            cin >> bookid;
                            student->borrowBook(bookid, library);
                            SaveData(library);
                        }
                        else if (studentChoice == 3)
                        {
                            // Return a book
                            cout << "\n Enter Book ID you want to return: \n"
                                 << endl;
                            int bookid;
                            cin >> bookid;
                            student->returnBook(bookid, library);
                            SaveData(library);
                        }
                        else if (studentChoice == 4)
                        {
                            // Display borrowed books
                            student->getAccount().displayBorrowedBooks(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (studentChoice == 5)
                        {
                            // Display history
                            student->getAccount().viewHistory(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (studentChoice == 6)
                        {
                            // Display fine
                            student->displayFine(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (studentChoice == 7)
                        {
                            // Pay fine
                            int amount;
                            cout << "Enter amount you want to pay: " << endl;
                            cin >> amount;
                            // Check if amount is valid
                            if (amount < 0)
                            {
                                cout << "Invalid Amount" << endl;
                                cout << "------------------------------------" << endl;
                                continue;
                            }
                            student->makePayement(library, amount);
                            SaveData(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (studentChoice == 8)
                        {
                            // Display overdue books
                            student->displayOverDueBooks(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (studentChoice == 9)
                        {
                            break;
                        }
                        else
                        {
                            // If invalid choice
                            cout << "Invalid Choice" << endl;
                            cout << "------------------------------------" << endl;
                        }

                        // Save data to file at the end of each iteration
                        SaveData(library);
                    }
                }
                else
                {
                    // If password is incorrect
                    cout << "Invalid Password" << endl;
                    cout << "------------------------------------" << endl;
                }
            }
            else
            {
                // If student not found
                cout << "Student not found" << endl;
                cout << "------------------------------------" << endl;
                continue;
            }
            SaveData(library);
        }
        // Faculty Login
        else if (choice == 2)
        {
            cout << "Enter Employee ID: " << endl;
            int facultyid;
            cin >> facultyid;
            Faculty *faculty = library.findFacultyById(facultyid);
            if (faculty)
            {
                // If faculty found then ask for password
                cout << "Enter Password: " << endl;
                string password;
                cin >> password;
                // If password is correct then login
                if (faculty->getPassword() == password)
                {
                    cout << "Login Successful" << endl;
                    cout << "Welcome " << faculty->getName() << endl;
                    cout << "------------------------------------" << endl;
                    while (1)
                    {
                        if (cin.fail())
                        {
                            cout << "Error in input type" << endl;
                            cin.clear(); // Clear error state
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout << "------------------------------------" << endl;
                        cout << "Enter 1 to display all books" << endl;
                        cout << "Enter 2 to know status of a particular book" << endl;
                        cout << "Enter 3 to borrow a book" << endl;
                        cout << "Enter 4 to return a book" << endl;
                        cout << "Enter 5 to display borrowed books" << endl;
                        cout << "Enter 6 to display your history" << endl;
                        cout << "Enter 7 to display Overdue books" << endl;
                        cout << "Enter 8 to exit" << endl;
                        cout << "-------------------------------------" << endl;
                        int facultyChoice;
                        cout << "Enter your choice here: ";
                        cin >> facultyChoice;
                        if (facultyChoice == 1)
                        {
                            // Display all books
                            cout << "------------------------------------" << endl;
                            library.displayBooks();
                            cout << "------------------------------------" << endl;
                        }
                        else if (facultyChoice == 2)
                        {
                            // Display status of a particular book
                            cout << "Enter Book ID: " << endl;
                            int bookid;
                            cin >> bookid;
                            library.findBookById(bookid)->display();
                        }
                        else if (facultyChoice == 3)
                        {
                            // Borrow a book
                            cout << "\nEnter Book ID you want to borrow: " << endl;
                            int bookid;
                            cin >> bookid;
                            faculty->borrowBook(bookid, library);
                            SaveData(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (facultyChoice == 4)
                        {
                            // Return a book
                            cout << "\nEnter Book ID you want to return: " << endl;
                            int bookid;
                            cin >> bookid;
                            faculty->returnBook(bookid, library);
                            SaveData(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (facultyChoice == 5)
                        {
                            // Display borrowed books
                            faculty->getAccount().displayBorrowedBooks(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (facultyChoice == 6)
                        {
                            // Display history
                            faculty->getAccount().viewHistory(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (facultyChoice == 7)
                        {
                            // Display overdue books
                            faculty->displayOverDueBooks(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (facultyChoice == 8)
                        {
                            // Exit
                            cout << "------------------------------------" << endl;
                            break;
                        }
                        else
                        {
                            // If invalid choice
                            cout << "Invalid Choice" << endl;
                            cout << "Please enter a valid choice" << endl;
                            continue;
                        }
                        cout << "------------------------------------" << endl;
                    }
                }
                else
                {
                    // If password is incorrect
                    cout << "Invalid password" << endl;
                    cout << "-------------------------------------" << endl;
                }
            }
            else
            {
                // If faculty not found
                cout << "Faculty not found" << endl;
                cout << "-------------------------------------" << endl;
                continue;
            }
        }
        // Librarian Login
        else if (choice == 3)
        {
            // Ask for librarian ID
            cout << "Enter Librarian ID: " << endl;
            int librarianid;
            cin >> librarianid;
            Librarian *librarian = library.findLibrarianById(librarianid);
            if (librarian)
            {
                cout << "Enter Password: " << endl;
                string password;
                cin >> password;
                if (librarian->getPassword() == password)
                {
                    cout << "Login Successful" << endl;
                    cout << "Welcome " << librarian->getName() << endl;
                    cout << "------------------------------------" << endl;
                    while (1)
                    {
                        if (cin.fail())
                        {
                            cout << "Error in input type" << endl;
                            cin.clear(); // Clear error state
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout << "------------------------------------" << endl;
                        cout << "Enter 1 to display all books" << endl;
                        cout << "Enter 2 to add a book" << endl;
                        cout << "Enter 3 to remove a book" << endl;
                        cout << "Enter 4 to add a new user" << endl;
                        cout << "Enter 5 to remove a user" << endl;
                        cout << "Enter 6 to update a book" << endl;
                        cout << "Enter 7 to update a user" << endl;
                        cout << "Enter 8 to display all users" << endl;
                        cout << "Enter 9 to display all books" << endl;
                        cout << "Enter 10 to exit" << endl;
                        cout << "------------------------------------" << endl;
                        int librarianChoice;
                        cout << "Enter your choice here: ";
                        cin >> librarianChoice;
                        if (librarianChoice == 1)
                        {
                            library.displayBooks();
                            cout << "------------------------------------" << endl;
                        }
                        else if (librarianChoice == 2)
                        {
                            int newBookId;
                            string title, author, publisher, isbn;
                            int year;
                            cout << "Enter Book ID you want to add: \n";
                            cin >> newBookId;
                            if (cin.fail())
                            {
                                cout << "Invalid Book ID! Please enter a valid integer.\n";
                                cin.clear();                                         // Clear the fail state
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                continue;
                            }
                            if (library.findBookById(newBookId) != nullptr)
                            {
                                cout << "Book with Book ID already exist" << endl;
                                cout << "------------------------------------" << endl;
                                continue;
                            }
                            cout << "Enter Title: \n";
                            cin.ignore();
                            getline(cin >> ws, title);
                            cout << "Enter Author: \n";
                            getline(cin >> ws, author);
                            cout << "Enter Publisher: \n";
                            getline(cin >> ws, publisher);
                            cout << "Enter ISBN: \n";
                            getline(cin >> ws, isbn);
                            cout << "Enter Year: \n";
                            cin >> year;
                            librarian->addBook(library, newBookId, title, author, publisher, isbn, year);
                            SaveData(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (librarianChoice == 3)
                        {
                            cout << "Enter Book ID you want to remove: ";
                            int bookId;
                            cin >> bookId;
                            librarian->removeBook(library, bookId);
                            SaveData(library);
                            cout << "------------------------------------" << endl;
                        }
                        else if (librarianChoice == 4)
                        {
                            cout << "Enter 1 if you want to add a student" << endl;
                            cout << "Enter 2 if you want to add a faculty" << endl;
                            cout << "Enter 3 if you want to add a librarian" << endl;
                            cout << "Enter 4 to exit" << endl;
                            cout << "------------------------------------" << endl;
                            int input;
                            cin >> input;
                            if (input == 1)
                            {
                                int newStudentId;

                                int rollNo;
                                string name, password, email;
                                cout << " Enter User ID: \n";
                                cin >> newStudentId;
                                if (cin.fail())
                                {
                                    cout << "Invalid User ID! Please enter a valid integer.\n";
                                    cin.clear();                                         // Clear the fail state
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    continue;
                                }
                                if (library.userExists(newStudentId))
                                {
                                    cout << "User with User ID already exist" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }

                                cout << "Enter Roll Number: \n";
                                cin >> rollNo;
                                if (cin.fail())
                                {
                                    cout << "Invalid Roll Number! Please enter a valid integer.\n";
                                    cin.clear();                                         // Clear the fail state
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    continue;
                                }
                                if (library.findStudentById(rollNo))
                                {
                                    cout << "Student with Roll No already exist" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                cin.ignore();
                                cout << "Enter Name: \n";
                                getline(cin >> ws, name);
                                cout << "Enter Password: \n";
                                cin >> password;
                                cout << "Enter Email: \n";
                                cin >> email;
                                librarian->addUser(library, newStudentId, "Student", rollNo, name, password, email);
                                SaveData(library);
                                cout << "------------------------------------" << endl;
                            }
                            else if (input == 2)
                            {
                                int newFacultyId;
                                int employeeId;
                                string name, password, email;
                                cout << "Enter User ID: \n";
                                cin >> newFacultyId;
                                if (cin.fail())
                                {
                                    cout << "Invalid User ID! Please enter a valid integer.\n";
                                    cin.clear();                                         // Clear the fail state
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    continue;
                                }
                                if (library.userExists(newFacultyId))
                                {
                                    cout << "User with User ID already exist" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                cout << "Enter Employee ID: \n";
                                cin >> employeeId;
                                if (cin.fail())
                                {
                                    cout << "Invalid Employee ID! Please enter a valid integer.\n";
                                    cin.clear();                                         // Clear the fail state
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    continue;
                                }
                                if (library.findFacultyById(employeeId))
                                {
                                    cout << "Faculty with Employee ID already exist" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                cin.ignore();
                                cout << "Enter Name: \n";
                                getline(cin >> ws, name);
                                cout << "Enter Password: \n";
                                cin >> password;
                                cout << "Enter Email: \n";
                                cin >> email;
                                librarian->addUser(library, newFacultyId, "Faculty", employeeId, name, password, email);
                                SaveData(library);
                                cout << "------------------------------------" << endl;
                            }
                            else if (input == 3)
                            {
                                int newLibrarianId;
                                int librarianId;
                                string name, password, email;
                                cout << "Enter User ID: ";
                                cin >> newLibrarianId;
                                if (cin.fail())
                                {
                                    cout << "Invalid User ID! Please enter a valid integer.\n";
                                    cin.clear();                                         // Clear the fail state
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    continue;
                                }
                                if (library.userExists(newLibrarianId))
                                {
                                    cout << "User with User ID already exist" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                cout << "Enter Librarian ID: ";
                                cin >> librarianId;
                                if (cin.fail())
                                {
                                    cout << "Invalid Librarian ID! Please enter a valid integer.\n";
                                    cin.clear();                                         // Clear the fail state
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    continue;
                                }
                                if (library.findLibrarianById(librarianId))
                                {
                                    cout << "Librarian with Librarian ID already exist" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                cin.ignore();
                                cout << "Enter Name: ";
                                getline(cin >> ws, name);
                                cout << "Enter Password: ";
                                cin >> password;
                                cout << "Enter Email: ";
                                cin >> email;
                                librarian->addUser(library, newLibrarianId, "Librarian", librarianId, name, password, email);
                                SaveData(library);
                                cout << "------------------------------------" << endl;
                            }
                            else if (input == 4)
                            {
                                continue;
                            }
                            else
                            {
                                cout << "Invalid Choice" << endl;
                                cout << "------------------------------------" << endl;
                                continue;
                            }
                        }
                        else if (librarianChoice == 5)
                        {
                            cout << "Enter 1 if you want to remove a student" << endl;
                            cout << "Enter 2 if you want to remove a faculty" << endl;
                            cout << "Enter 3 if you want to remove a librarian" << endl;
                            cout << "Enter 4 to exit" << endl;
                            cout << "------------------------------------" << endl;
                            int input;
                            cin >> input;
                            if (input == 1)
                            {
                                int rollNo;
                                cout << "Enter Roll Number of student you want to remove: ";
                                cin >> rollNo;
                                int studentIdNo = library.getStudentIdFromRollNo(rollNo);
                                if (studentIdNo == -1)
                                {
                                    cout << "Student not found" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                librarian->removeUser(library, studentIdNo, "Student", rollNo);
                                SaveData(library);
                                cout << "------------------------------------" << endl;
                            }
                            else if (input == 2)
                            {
                                int employeeId;
                                cout << "Enter Employee ID of faculty you want to remove: ";
                                cin >> employeeId;
                                int facultyIdNo = library.getFacultyIdFromEmployeeId(employeeId);
                                if (facultyIdNo == -1)
                                {
                                    cout << "Faculty not found" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                librarian->removeUser(library, facultyIdNo, "Faculty", employeeId);
                                SaveData(library);
                                cout << "------------------------------------" << endl;
                            }
                            else if (input == 3)
                            {
                                int librarianId;
                                cout << "Enter Librarian ID of librarian you want to remove: " << endl;
                                cout << "------------------------------------" << endl;
                                cin >> librarianId;
                                int librarianIdNo = library.getLibrarianIdFromLibrarianId(librarianId);
                                if (librarianIdNo == -1)
                                {
                                    cout << "Librarian not found" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                librarian->removeUser(library, librarianIdNo, "Librarian", librarianId);
                                SaveData(library);
                                cout << "------------------------------------" << endl;
                            }
                            else if (input == 4)
                            {
                                continue;
                            }
                            else
                            {
                                cout << "Invalid Choice" << endl;
                                cout << "------------------------------------" << endl;
                            }
                        }
                        else if (librarianChoice == 6)
                        {
                            cout << "Enter Book ID you want to update:";
                            int bookId;
                            cin >> bookId;
                            Book *book = library.findBookById(bookId);
                            if (book)
                            {
                                cout << "Enter 1 to update title" << endl;
                                cout << "Enter 2 to update author" << endl;
                                cout << "Enter 3 to update publisher" << endl;
                                cout << "Enter 4 to update ISBN" << endl;
                                cout << "Enter 5 to update year" << endl;
                                cout << "Enter 6 to update status" << endl;

                                cout << "Enter 7 to exit" << endl;
                                cout << "------------------------------------" << endl;
                                int updateChoice;
                                cout << "Enter your choice here:";

                                cin >> updateChoice;
                                if (updateChoice == 1)
                                {
                                    string title;
                                    cin.ignore();
                                    cout << "Enter new title:\n";
                                    getline(cin >> ws, title);
                                    book->setTitle(title);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateChoice == 2)
                                {
                                    string author;
                                    cin.ignore();
                                    cout << "Enter new author:\n";
                                    getline(cin >> ws, author);
                                    book->setAuthor(author);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateChoice == 3)
                                {
                                    string publisher;
                                    cin.ignore();
                                    cout << "Enter new publisher:\n";
                                    getline(cin >> ws, publisher);
                                    book->setPublisher(publisher);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateChoice == 4)
                                {
                                    string isbn;
                                    cin.ignore();
                                    cout << "Enter new ISBN:\n";
                                    getline(cin >> ws, isbn);
                                    book->setISBN(isbn);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateChoice == 5)
                                {
                                    int year;
                                    cout << "Enter new year:\n";
                                    cin >> year;
                                    book->setYear(year);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateChoice == 6)
                                {
                                    string status;
                                    cout << "Enter 1 to update status to Reserved" << endl;
                                    cout << "Enter 2 to update status from Reserved to Available" << endl;
                                    cout << "Enter 3 to exit" << endl;
                                    cout << "Enter new status:";

                                    int statusChoice;
                                    cin >> statusChoice;
                                    if (statusChoice == 1)
                                    {
                                        status = "Reserved";
                                        if (book->getStatus() == "Borrowed")
                                        {
                                            cout << "Book is already borrowed" << endl;
                                            continue;
                                        }
                                        book->setStatus(status);
                                        SaveData(library);
                                        cout << "------------------------------------" << endl;
                                    }
                                    else if (statusChoice == 2)
                                    {
                                        status = "Available";
                                        if (book->getStatus() == "Borrowed")
                                        {
                                            cout << "Book is already borrowed" << endl;
                                            continue;
                                        }
                                        book->setStatus(status);
                                        SaveData(library);
                                        cout << "------------------------------------" << endl;
                                    }
                                    else if (statusChoice == 3)
                                    {
                                        cout << "------------------------------------" << endl;
                                        continue;
                                    }
                                    else
                                    {
                                        cout << "Invalid Choice" << endl;
                                    }
                                }

                                else if (updateChoice == 7)
                                {
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                else
                                {
                                    cout << "Invalid Choice" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                            }
                            else
                            {
                                cout << "Book not found" << endl;
                                cout << "------------------------------------" << endl;
                                continue;
                            }
                        }
                        else if (librarianChoice == 7)
                        {
                            cout << "Enter 1 to update student" << endl;
                            cout << "Enter 2 to update faculty" << endl;
                            cout << "Enter 3 to update librarian" << endl;
                            cout << "Enter 4 to exit" << endl;
                            cout << "------------------------------------" << endl;
                            int updateChoice;
                            cout << "Enter your choice here:";
                            cin >> updateChoice;
                            if (updateChoice == 1)
                            {
                                cout << "Enter Roll Number of student you want to update: ";
                                int rollNo;
                                cin >> rollNo;
                                int studentIdNo = library.getStudentIdFromRollNo(rollNo);
                                // cout << "studentIdNo" << studentIdNo << endl;
                                if (studentIdNo == -1)
                                {
                                    cout << "Student not found" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                Student *student = library.findStudentById(rollNo);
                                cout << "Enter 1 to update name" << endl;
                                cout << "Enter 2 to update password" << endl;
                                cout << "Enter 3 to update email" << endl;
                                cout << "Enter 4 to exit" << endl;
                                cout << "------------------------------------" << endl;
                                int updateStudentChoice;
                                cout << "Enter your choice here:";
                                cin >> updateStudentChoice;
                                if (updateStudentChoice == 1)
                                {
                                    string name;
                                    cin.ignore();
                                    cout << "Enter new name:\n";
                                    getline(cin >> ws, name);
                                    cout << "name" << endl;
                                    if (student == nullptr)
                                    {
                                        cout << "Error: student is uninitialized (nullptr)!" << endl;

                                        continue;
                                    }
                                    student->setName(name);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateStudentChoice == 2)
                                {
                                    string password;
                                    cout << "Enter new password:\n";
                                    cin >> password;
                                    student->setPassword(password);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateStudentChoice == 3)
                                {
                                    string email;
                                    cout << "Enter new email:";
                                    cin >> email;
                                    student->setEmail(email);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateStudentChoice == 4)
                                {
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                else
                                {
                                    cout << "Invalid Choice" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                            }
                            else if (updateChoice == 2)
                            {
                                cout << "Enter Employee ID of faculty you want to update: ";
                                int employeeId;
                                cin >> employeeId;
                                int facultyIdNo = library.getFacultyIdFromEmployeeId(employeeId);
                                if (facultyIdNo == -1)
                                {
                                    cout << "Faculty not found" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                Faculty *faculty = library.findFacultyById(employeeId);
                                cout << "Enter 1 to update name" << endl;
                                cout << "Enter 2 to update password" << endl;
                                cout << "Enter 3 to update email" << endl;
                                cout << "Enter 4 to exit" << endl;
                                cout << "------------------------------------" << endl;
                                int updateFacultyChoice;
                                cout << "Enter your choice here:";

                                cin >> updateFacultyChoice;
                                if (updateFacultyChoice == 1)
                                {
                                    string name;
                                    cin.ignore();
                                    cout << "Enter new name:\n";
                                    getline(cin >> ws, name);
                                    faculty->setName(name);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateFacultyChoice == 2)
                                {
                                    string password;
                                    cout << "Enter new password:";
                                    cin >> password;
                                    faculty->setPassword(password);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateFacultyChoice == 3)
                                {
                                    string email;
                                    cout << "Enter new email:\n";
                                    cin >> email;
                                    cout << email << endl;
                                    faculty->setEmail(email);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateFacultyChoice == 4)
                                {
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                else
                                {
                                    cout << "Invalid Choice" << endl;
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                            }
                            else if (updateChoice == 3)
                            {
                                cout << "Enter Librarian ID of librarian you want to update: ";
                                int librarianId;
                                cin >> librarianId;
                                int librarianIdNo = library.getLibrarianIdFromLibrarianId(librarianId);
                                if (librarianIdNo == -1)
                                {
                                    cout << "Librarian not found" << endl;
                                    continue;
                                }
                                Librarian *librarian = library.findLibrarianById(librarianId);
                                cout << "Enter 1 to update name" << endl;
                                cout << "Enter 2 to update password" << endl;
                                cout << "Enter 3 to update email" << endl;
                                cout << "Enter 4 to exit" << endl;
                                cout << "------------------------------------" << endl;
                                int updateLibrarianChoice;
                                cout << "Enter your choice here:";
                                cin >> updateLibrarianChoice;
                                if (updateLibrarianChoice == 1)
                                {
                                    string name;
                                    cin.ignore();
                                    cout << "Enter new name:";
                                    getline(cin >> ws, name);
                                    librarian->setName(name);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateLibrarianChoice == 2)
                                {
                                    string password;
                                    cout << "Enter new password:";
                                    cin >> password;
                                    librarian->setPassword(password);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateLibrarianChoice == 3)
                                {
                                    string email;
                                    cout << "Enter new email:";
                                    cin >> email;
                                    librarian->setEmail(email);
                                    SaveData(library);
                                    cout << "------------------------------------" << endl;
                                }
                                else if (updateLibrarianChoice == 4)
                                {
                                    cout << "------------------------------------" << endl;
                                    continue;
                                }
                                else
                                {

                                    cout << "Invalid Choice" << endl;
                                    cout << "------------------------------------" << endl;
                                }
                            }
                        }
                        else if (librarianChoice == 8)
                        {
                            library.displayUsers();
                            cout << "------------------------------------" << endl;
                        }
                        else if (librarianChoice == 9)
                        {
                            library.displayBooks();
                            cout << "------------------------------------" << endl;
                        }
                        else if (librarianChoice == 10)
                        {
                            cout << "------------------------------------" << endl;
                            break;
                        }
                        else
                        {
                            cout << "Invalid Choice" << endl;
                            cout << "Please enter a valid choice" << endl;
                            cout << "------------------------------------" << endl;
                            continue;
                        }
                        cout << "------------------------------------" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Password" << endl;
                }
            }
            else
            {
                cout << "Librarian not found" << endl;
                continue;
            }
        }
        else if (choice == 4)
        {
            cout << "Program Terminated" << endl;
            break;
        }
        else
        {
            cout << "Invalid Choice" << endl;
            continue;
        }
    }

    library.saveBooksToFile("Books.txt", library.getBooks());                                                     // Save books to file
    library.saveUsersToFile("Users.txt", library.getStudents(), library.getFaculties(), library.getLibrarians()); // Save users to file
    return 0;
}
