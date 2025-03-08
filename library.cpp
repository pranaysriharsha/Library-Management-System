#include "library.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "account.h"
#include "book.h"
#include "faculty.h"
#include "librarian.h"
#include "student.h"
#include "user.h"

using namespace std;

std::string trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// Library Initialization which loads data from files
void Library::initialize()
{
    // Load books from file
    ifstream file("Books.txt");
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        int id, year, borrowerId;
        string title, author, publisher, isbn, status;

        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, isbn, ',');
        getline(ss, temp, ',');
        year = stoi(temp);
        getline(ss, status, ',');
        getline(ss, temp, ',');
        borrowerId = stoi(temp);

        books.emplace_back(id, title, author, publisher, isbn, year, status, borrowerId);
    }
    file.close();

    // Load users from file

    ifstream file2("Users.txt");
    if (!file2)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    while (getline(file2, line))
    {
        stringstream ss(line);
        string role, temp_id, temp_roleSpecificId, name, password, email, temp;
        int borrowedBooks;
        int historySize;
        vector<pair<string, string>> borrowedBooksList;
        vector<string> history;

        getline(ss, role, ',');
        getline(ss, temp_id, ',');
        int id = stoi(temp_id);
        getline(ss, temp_roleSpecificId, ',');
        int roleSpecificId = stoi(temp_roleSpecificId);
        getline(ss, name, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        int finePaid = 0;
        if (role == "Student" || role == "Faculty")
        {
            ss >> finePaid;
            ss.ignore(); // Ignore the comma
            ss >> borrowedBooks;
            ss.ignore(); // Ignore the comma

            for (int i = 0; i < borrowedBooks; i++)
            {
                string book, time;
                getline(ss, book, ',');
                getline(ss, time, ',');
                borrowedBooksList.push_back({book, time});
            }
            ss >> historySize;
            ss.ignore(); // Ignore the comma
            while (getline(ss, temp, ','))
            {
                temp = trim(temp);
                if (!temp.empty())
                { // Ensure it is not an empty string

                    history.push_back(temp);
                }
            }
        }

        if (role == "Student")
        {
            students.emplace_back(id, roleSpecificId, name, password, email);
        }
        else if (role == "Faculty")
        {
            faculties.emplace_back(id, roleSpecificId, name, password, email);
        }
        else if (role == "Librarian")
        {
            librarians.emplace_back(id, roleSpecificId, name, password, email);
        }
        if (role == "Student")
        {
            for (int i = 0; i < borrowedBooksList.size(); i++)
            {
                students.back().getAccount().addToBorrowedBooks(stoi(borrowedBooksList[i].first), borrowedBooksList[i].second);
            }
            for (int i = 0; i < history.size(); i++)
            {
                students.back().getAccount().addToHistory(stoi(history[i]));
            }
            students.back().getAccount().setAmountpaid(finePaid);
        }
        else if (role == "Faculty")
        {
            for (int i = 0; i < borrowedBooksList.size(); i++)
            {
                faculties.back().getAccount().addToBorrowedBooks(stoi(borrowedBooksList[i].first), borrowedBooksList[i].second);
            }
            for (int i = 0; i < history.size(); i++)
            {
                faculties.back().getAccount().addToHistory(stoi(history[i]));
            }
            faculties.back().getAccount().setAmountpaid(finePaid);
        }
    }
    file2.close();
}

// Display all books
void Library::displayBooks()
{
    for (const auto &book : books)
    {
        book.display();
    }
}

// Display all users
void Library::displayUsers()
{
    // Display all Students
    cout << "Students:" << endl;
    for (auto &student : students)
    {
        cout << "Student ID: " << student.getUserId() << ",RollNo: " << student.getRollNo() << ", Name: " << student.getName() << ", Email: " << student.getEmail() << " " << student.finePerDay << " " << student.maxBooksAllowed << " " << student.maxBorrowPeriod << endl;
        vector<Account::BorrowedBook> borrowedBooks = student.getAccount().getBorrowedBooks();
        cout << "    Borrowed Books:" << borrowedBooks.size() << endl;

        for (const auto &borrowedBook : borrowedBooks)
        {
            cout << "          Book ID: " << borrowedBook.bookId << ", Borrowed at: " << borrowedBook.borrowTimestamp << endl;
        }
    }
    // Display all Faculties
    cout << "Faculties:" << endl;
    for (auto &faculty : faculties)
    {
        cout << "Faculty ID: " << faculty.getUserId() << ",Employee ID: " << faculty.getEmployeeId() << ", Name: " << faculty.getName() << ", Email: " << faculty.getEmail() << " " << faculty.finePerDay << " " << faculty.maxBooksAllowed << " " << faculty.maxBorrowPeriod << endl;
        vector<Account::BorrowedBook> borrowedBooks = faculty.getAccount().getBorrowedBooks();
        cout << "    Borrowed Books:" << borrowedBooks.size() << endl;

        for (const auto &borrowedBook : borrowedBooks)
        {
            cout << "          Book ID: " << borrowedBook.bookId << ", Borrowed at: " << borrowedBook.borrowTimestamp << endl;
        }
    }
    // Display all Librarians
    cout << "Librarians:" << endl;
    for (auto &librarian : librarians)
    {
        cout << "Librarian ID: " << librarian.getUserId() << ",Librarian ID: " << librarian.getLibrarianId() << ", Name: " << librarian.getName() << ", Email: " << librarian.getEmail() << endl;
    }
}

// Find a book by ID
Book *Library::findBookById(int bookId)
{
    for (auto &book : books)
    {
        if (book.getId() == bookId)
        {
            return &book;
        }
    }
    // If book not found return nullptr
    return nullptr;
}

// Find a student by RollNo
Student *Library::findStudentById(int rollNo)
{
    for (auto &student : students)
    {
        if (student.getRollNo() == rollNo)
        {
            return &student;
        }
    }
    return nullptr;
}

// Find a faculty by Employee ID
Faculty *Library::findFacultyById(int employeeId)
{
    for (auto &faculty : faculties)
    {
        if (faculty.getEmployeeId() == employeeId)
        {
            return &faculty;
        }
    }
    return nullptr;
}

// Find a librarian by ID
Librarian *Library::findLibrarianById(int LibrarianId)
{
    for (auto &librarian : librarians)
    {
        if (librarian.getLibrarianId() == LibrarianId)
        {
            return &librarian;
        }
    }
    return nullptr;
}

// Add a student
void Library::addStudent(Student &student)
{
    students.push_back(student);
    cout << "Student added successfully" << endl;
}

// Add a faculty
void Library::addFaculty(Faculty &faculty)
{
    faculties.push_back(faculty);
    cout << "Faculty added successfully" << endl;
}

// Add a librarian
void Library::addLibrarian(Librarian &librarian)
{
    librarians.push_back(librarian);
    cout << "Librarian added successfully" << endl;
}

// Add a book
void Library::addBook(Book &book)
{
    books.push_back(book);
    cout << "Book added successfully" << endl;
}

// Remove a user
void Library::removeUser(int &Id, const string &role, int &roleId)
{
    if (role == "Student")
    {
        Student *student = findStudentById(roleId);
        if (student == nullptr)
        {
            cout << "Student not found" << endl;
            return;
        }
        if (student->getAccount().getBorrowedBooks().size() > 0)
        {
            for (auto &borrowedBook : student->getAccount().getBorrowedBooks())
            {
                Book *book = findBookById(borrowedBook.bookId);
                if (book)
                {
                    book->setStatus("Available");
                    book->setBorrowerId(-1);
                }
            }
        }
        for (auto it = students.begin(); it != students.end();)
        {
            if (it->getUserId() == Id && it->getRollNo() == roleId)
            {
                it = students.erase(it); // Erase returns next valid iterator
                break;                   // Stop after deletion
            }
            else
            {
                ++it; // Only increment if no deletion occurs
            }
        }
        cout << "User removed successfully" << endl;
    }
    else if (role == "Faculty")
    {
        Faculty *faculty = findFacultyById(roleId);
        if (faculty == nullptr)
        {
            cout << "Faculty not found" << endl;
            return;
        }
        if (faculty->getAccount().getBorrowedBooks().size() > 0)
        {
            for (auto &borrowedBook : faculty->getAccount().getBorrowedBooks())
            {
                Book *book = findBookById(borrowedBook.bookId);
                if (book)
                {
                    book->setStatus("Available");
                    book->setBorrowerId(-1);
                }
            }
        }
        for (auto it = faculties.begin(); it != faculties.end();)
        {
            if (it->getUserId() == Id && it->getEmployeeId() == roleId)
            {
                it = faculties.erase(it); // Erase returns next valid iterator
                break;                    // Stop after deletion
            }
            else
            {
                ++it; // Only increment if no deletion occurs
            }
        }
        cout << "User removed successfully" << endl;
    }
    else if (role == "Librarian")
    {
        Librarian *librarian = findLibrarianById(roleId);
        if (librarian == nullptr)
        {
            cout << "Librarian not found" << endl;
            return;
        }
        if (librarians.size() == 1)
        {
            cout << "Cannot remove the only librarian" << endl;
            return;
        }
        for (auto it = librarians.begin(); it != librarians.end();)
        {
            if (it->getUserId() == Id && it->getLibrarianId() == roleId)
            {
                it = librarians.erase(it); // Erase returns next valid iterator
                break;                     // Stop after deletion
            }
            else
            {
                ++it; // Only increment if no deletion occurs
            }
        }
        cout << "User removed successfully" << endl;
    }
    else
    {
        cout << "Invalid role" << endl;
    }
}

// Remove a book
void Library::removeBook(int &bookId)
{
    Book *book = findBookById(bookId);
    if (book == nullptr)
    {
        cout << "Book not found" << endl;
        return;
    }
    if (book->getStatus() == "Borrowed")
    {
        cout << "Book is borrowed, cannot be removed" << endl;
        cout << "Only available books can be removed" << endl;
        return;
    }
    for (auto it = books.begin(); it != books.end();)
    {
        if (it->getId() == bookId)
        {
            it = books.erase(it); // Erase returns next valid iterator
            break;                // Stop after deletion
        }
        else
        {
            ++it; // Only increment if no deletion occurs
        }
    }
    cout << "Book removed successfully" << endl;
}

// Save books to file
void Library::saveBooksToFile(const string &filename, const vector<Book> &books)
{
    // Open file for writing
    ofstream file(filename);
    if (!file)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (const auto &book : books)
    {
        file << book.getId() << ","
             << book.getTitle() << ","
             << book.getAuthor() << ","
             << book.getPublisher() << ","
             << book.getISBN() << ","
             << book.getYear() << ","
             << book.getStatus() << ","
             << book.getBorrowerId()
             << "\n"; // Newline for next book
    }

    file.close();
}

// Getters
vector<Book> Library::getBooks()
{
    return books;
}

vector<Student> Library::getStudents()
{
    return students;
}

vector<Faculty> Library::getFaculties()
{
    return faculties;
}

vector<Librarian> Library::getLibrarians()
{
    return librarians;
}

// Save users to file
void Library::saveUsersToFile(const string &filename,
                              const vector<Student> &students,
                              const vector<Faculty> &faculties,
                              const vector<Librarian> &librarians)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Write Students
    for (const auto &student : students)
    {
        file << "Student," << student.getUserId() << "," << student.getRollNo() << ","
             << student.getName() << "," << student.getPassword() << "," << student.getEmail() << ","
             << student.getAccount().getAmountpaid() << ","
             << student.getAccount().getBorrowedBooks().size();

        // Writing borrowed books and timestamps (if any)
        const auto &borrowedBooks = student.getAccount().getBorrowedBooks();
        for (const auto &borrowedBook : borrowedBooks)
        {
            file << "," << borrowedBook.bookId << "," << borrowedBook.borrowTimestamp;
        }

        // Writing history (if any)
        const auto &history = student.getAccount().getHistory();
        file << "," << history.size();
        for (const int id : history)
        {
            file << "," << id;
        }

        file << "\n"; // Move to the next line
    }

    // Write Faculties
    for (const auto &faculty : faculties)
    {
        file << "Faculty," << faculty.getUserId() << "," << faculty.getEmployeeId() << ","
             << faculty.getName() << "," << faculty.getPassword() << "," << faculty.getEmail() << ","
             << faculty.getAccount().getAmountpaid() << ","
             << faculty.getAccount().getBorrowedBooks().size();

        const auto &borrowedBooks = faculty.getAccount().getBorrowedBooks();
        for (const auto &borrowedBook : borrowedBooks)
        {
            file << "," << borrowedBook.bookId << "," << borrowedBook.borrowTimestamp;
        }

        const auto &history = faculty.getAccount().getHistory();
        file << "," << history.size();
        for (const int id : history)
        {
            file << "," << id;
        }

        file << "\n";
    }

    // Write Librarians
    for (const auto &librarian : librarians)
    {
        file << "Librarian," << librarian.getUserId() << "," << librarian.getLibrarianId() << ","
             << librarian.getName() << "," << librarian.getPassword() << "," << librarian.getEmail()
             << "\n";
    }

    file.close();
}

// Find a book by ISBN
Book *Library::findBookbyISBN(string isbn)
{
    for (auto &book : books)
    {
        if (book.getISBN() == isbn)
        {
            return &book;
        }
    }
    return nullptr;
}

// Find Student User ID from RollNo
int Library::getStudentIdFromRollNo(int rollNo)
{
    for (auto &student : students)
    {
        if (student.getRollNo() == rollNo)
        {
            return student.getUserId();
        }
    }
    return -1;
}

// Find Faculty User ID from Employee ID
int Library::getFacultyIdFromEmployeeId(int employeeId)
{
    for (auto &faculty : faculties)
    {
        if (faculty.getEmployeeId() == employeeId)
        {
            return faculty.getUserId();
        }
    }
    return -1;
}

// Find Librarian User ID from Librarian ID
int Library::getLibrarianIdFromLibrarianId(int LibrarianId)
{
    for (auto &librarian : librarians)
    {
        if (librarian.getLibrarianId() == LibrarianId)
        {
            return librarian.getUserId();
        }
    }
    return -1;
}

// Find Book ID from ISBN
int Library::getBookIdFromISBN(string isbn)
{
    for (auto &book : books)
    {
        if (book.getISBN() == isbn)
        {
            return book.getId();
        }
    }
    return -1;
}

// Check if a user exists
bool Library::userExists(int id)
{
    for (auto &student : students)
    {
        if (student.getUserId() == id)
        {
            return true;
        }
    }
    for (auto &faculty : faculties)
    {
        if (faculty.getUserId() == id)
        {
            return true;
        }
    }
    for (auto &librarian : librarians)
    {
        if (librarian.getUserId() == id)
        {
            return true;
        }
    }
    return false;
}