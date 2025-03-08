#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "faculty.h"
#include "user.h"
#include "book.h"
#include "library.h"
#include <iomanip>

using namespace std;
// Constructor
Faculty::Faculty(int userId, int employeeId, const string &name, const string &password, const string &email)
    : User(userId, name, password, "Faculty", email), employeeId(employeeId)
{
    finePerDay = 0;
    maxBooksAllowed = 5;
    maxBorrowPeriod = 30;
    maxLimitAfterBorrow = 60;
}
// Getters
int Faculty::getEmployeeId() const { return employeeId; }
void Faculty::setEmployeeId(int newEmployeeId) { employeeId = newEmployeeId; }
const Account &Faculty::getAccount() const { return account; }
Account &Faculty::getAccount() { return account; }

// Borrow a book
void Faculty::borrowBook(int bookId, Library &library)
{
    // 1. Check if the faculty has reached maxBooksAllowed
    if (account.getBorrowedBooks().size() >= maxBooksAllowed)
    {
        cout << "You have reached the maximum borrow limit of " << maxBooksAllowed << " books." << endl;
        return;
    }
    // 2. Check if the faculty has overdue books(>60 days)
    if (overDueCheck(library))
    {
        cout << "You have overdue books. Please return them before borrowing new books." << endl;
        return;
    }

    // 3. Check if the book is Exists
    Book *book = library.findBookById(bookId); // Use library object passed as parameter
    if (!book)
    {
        cout << "Book ID " << bookId << " not found." << endl;
        return;
    }
    // Check if the book is available
    if (!book->isAvailable())
    {
        if (book->getStatus() == "Borrowed")
        {
            cout << "Book ID " << bookId << " is already borrowed." << endl;
        }
        else
        {
            cout << "Book ID " << bookId << " is Reserved" << endl;
        }
        return;
    }
    // Get current time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setw(4) << 1900 + ltm->tm_year << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min << ":"
       << setfill('0') << setw(2) << ltm->tm_sec;
    string borrowTime = ss.str();

    // 4. Add the book to student's account
    account.addToBorrowedBooks(bookId, borrowTime);

    // 5. Mark the book as borrowed
    book->setBorrowerId(this->getUserId());
    book->setStatus("Borrowed");

    cout << "Book ID " << bookId << " successfully borrowed on " << borrowTime << "." << endl;
}

// Check if the faculty has overdue books (>60 days)
bool Faculty::overDueCheck(Library &library)
{
    vector<Account::BorrowedBook> borrowedBooks = getAccount().getBorrowedBooks();
    time_t now = time(0); // Get current time
    struct tm dueDate = {};
    int totalAmount = 0;
    bool hasOverDue = false;

    for (const auto &bookEntry : borrowedBooks)
    {
        int bookId = bookEntry.bookId;
        string borrowTime = bookEntry.borrowTimestamp;

        // Convert borrowTime (string) to time_t
        istringstream ss(borrowTime);
        ss >> get_time(&dueDate, "%Y-%m-%d %H:%M:%S"); // Parse date format
        time_t borrowTimestamp = mktime(&dueDate);

        // Calculate days borrowed
        int daysBorrowed = (now - borrowTimestamp) / (60 * 60 * 24);

        // Change hasOverDue to true if daysBorrowed is greater than maxLimitAfterBorrow
        if (daysBorrowed > maxLimitAfterBorrow)
        {
            hasOverDue = true;
        }
    }
    return hasOverDue;
}

void Faculty::displayOverDueBooks(Library &library)
{
    vector<Account::BorrowedBook> borrowedBooks = getAccount().getBorrowedBooks();
    time_t now = time(0); // Get current time
    struct tm dueDate = {};
    int totalAmount = 0;
    bool hasOverDue = false;

    cout << "Overdue books:" << endl;
    cout << "Book ID | Title | Due Date | Days Overdue " << endl;
    cout << "--------|-------|----------|--------------" << endl;

    for (const auto &bookEntry : borrowedBooks)
    {
        int bookId = bookEntry.bookId;
        string borrowTime = bookEntry.borrowTimestamp;

        // Convert borrowTime (string) to time_t
        istringstream ss(borrowTime);
        ss >> get_time(&dueDate, "%Y-%m-%d %H:%M:%S"); // Parse date format
        time_t borrowTimestamp = mktime(&dueDate);

        // Calculate days borrowed
        int daysBorrowed = (now - borrowTimestamp) / (60 * 60 * 24);

        // Change hasOverDue to true if daysBorrowed is greater than maxLimitAfterBorrow
        if (daysBorrowed > maxBorrowPeriod)
        {
            Book *book = library.findBookById(bookId);
            cout << bookId << " | " << book->getTitle() << " | " << put_time(&dueDate, "%Y-%m-%d") << " | " << daysBorrowed - maxBorrowPeriod << endl;
            hasOverDue = true;
        }
    }

    if (!hasOverDue)
    {
        cout << "No overdue books." << endl;
    }
}

void Faculty::displayOverDueForBook(int bookID, Library &library)
{
    Book *book = library.findBookById(bookID);
    // Check if the book is borrowed by the faculty
    if (!book)
    {
        cout << "Book ID " << bookID << " not found." << endl;
        return;
    }
    if (book->getBorrowerId() != this->getUserId())
    {
        cout << "You have not borrowed Book ID " << bookID << "." << endl;
        return;
    }

    time_t now = time(0); // Get current time
    struct tm dueDate = {};
    Account::BorrowedBook borrowedBook;
    for (const auto &bookEntry : account.getBorrowedBooks())
    {
        if (bookEntry.bookId == bookID)
        {
            borrowedBook = bookEntry;
            break;
        }
    }
    string borrowTime = borrowedBook.borrowTimestamp;

    // Convert borrowTime (string) to time_t
    istringstream ss(borrowTime);
    ss >> get_time(&dueDate, "%Y-%m-%d %H:%M:%S"); // Parse date format
    time_t borrowTimestamp = mktime(&dueDate);

    // Calculate days borrowed
    int daysBorrowed = (now - borrowTimestamp) / (60 * 60 * 24);

    // Get user-specific fine settings
    if (daysBorrowed > maxBorrowPeriod)
    { // `maxBorrowPeriod` is inherited from `User`
        int overdueDays = daysBorrowed - maxBorrowPeriod;
        string bookTitle = book ? book->getTitle() : "Unknown";

        cout << "Book ID: " << bookID << " | Title: " << bookTitle
             << " | Overdue by: " << overdueDays << " days"
             << " |Borrowed on: " << borrowTime << endl;
    }
    else
    {
        int overdueDays = 0;
        string bookTitle = book ? book->getTitle() : "Unknown"; // If book is not found, display "Unknown"

        cout << "Book ID: " << bookID << " | Title: " << bookTitle
             << " | Overdue by: " << overdueDays << " days"
             << " |Borrowed on: " << borrowTime << endl;
    }
}

void Faculty::returnBook(int bookId, Library &library)
{
    // 1. Check if the book is borrowed by the faculty
    Book *book = library.findBookById(bookId);
    if (!book)
    {
        cout << "Book ID " << bookId << " not found." << endl;
        return;
    }
    if (book->getBorrowerId() != this->getUserId())
    {
        cout << "You have not borrowed Book ID " << bookId << "." << endl;
        return;
    }
    // 2. Get current time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setw(4) << 1900 + ltm->tm_year << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min << ":"
       << setfill('0') << setw(2) << ltm->tm_sec;
    string returnTime = ss.str();

    this->displayOverDueForBook(bookId, library);
    account.addToHistory(bookId);

    vector<Account::BorrowedBook> temp;
    vector<Account::BorrowedBook> borrowedBooks = getAccount().getBorrowedBooks();
    // Remove the book from the faculty's account
    for (auto &borrowedBook : borrowedBooks)
    {
        if (borrowedBook.bookId != bookId)
        {
            temp.push_back(borrowedBook);
        }
    }
    account.deleteBorrowedBooks();
    for (auto &borrowedBook : temp)
    {
        account.addToBorrowedBooks(borrowedBook.bookId, borrowedBook.borrowTimestamp);
    }

    // 3. Mark the book as available
    book->setBorrowerId(-1);
    book->setStatus("Available");

    cout << "Book ID " << bookId << " successfully returned on " << returnTime << "." << endl;
}
