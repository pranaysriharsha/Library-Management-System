#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "student.h"
#include "book.h"
#include "account.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include "library.h"

using namespace std;

// Constructor
Student::Student(int userId, int rollNo, const string &name, const string &password, const string &email)
    : User(userId, name, password, "Student", email), rollNo(rollNo)
{
    finePerDay = 10;
    maxBooksAllowed = 3;
    maxBorrowPeriod = 15;
}

// Getters and Setters
int Student::getRollNo() const { return rollNo; }
void Student::setRollNo(int newRollNo) { rollNo = newRollNo; }
const Account &Student::getAccount() const { return account; }
Account &Student::getAccount() { return account; }

// Function to borrow a book
void Student::borrowBook(int bookId, Library &library)
{
    // 1. Check if the student has reached maxBooksAllowed
    if (account.getBorrowedBooks().size() >= maxBooksAllowed)
    {
        cout << "You have reached the maximum borrow limit of " << maxBooksAllowed << " books." << endl;
        return;
    }

    // 2. Check if the book is available
    Book *book = library.findBookById(bookId); // Use library object passed as parameter
    if (!book)
    {
        cout << "Book ID " << bookId << " not found." << endl;
        return;
    }
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
    if (this->calculateFine(library) > 0)
    {
        cout << "You have outstanding fines. Please pay them before borrowing a new book." << endl;
        return;
    }

    // 3. Get the current timestamp
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
    cout << "--------------------------------------------------" << endl;
}

// Function to Display Overall payment amount for a student
void Student::displayFine(Library &library)
{
    vector<Account::BorrowedBook> borrowedBooks = getAccount().getBorrowedBooks(); // Get borrowed books

    cout << "Outstanding Fines for " << getName() << " (User ID: " << getUserId() << ")\n";
    cout << "--------------------------------------------------\n";

    time_t now = time(0); // Get current time
    struct tm dueDate = {};
    bool hasFines = false;
    int totalAmount = 0;

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
        cout << "maxtime:" << maxBorrowPeriod << endl;
        cout << "daysBorrowed:" << daysBorrowed << endl;

        // Get user-specific fine settings
        if (daysBorrowed > maxBorrowPeriod)
        { // `maxBorrowPeriod` is inherited from `User`
            hasFines = true;
            int overdueDays = daysBorrowed - maxBorrowPeriod;
            int fineAmount = overdueDays * finePerDay; // `finePerDay` is inherited from `User`
            totalAmount += fineAmount;

            // Get book details
            Book *book = library.findBookById(bookId);
            string bookTitle = book ? book->getTitle() : "Unknown";

            cout << "Book ID: " << bookId << " | Title: " << bookTitle
                 << " | Overdue by: " << overdueDays << " days"
                 << " |Borrowed on: " << borrowTime
                 << " | Fine: " << fineAmount << endl;
        }
    }
    cout << "--------------------------------------------------\n";

    if (!hasFines)
    {
        // If no fines
        cout << "No outstanding fines.\n";
    }

    else
    {
        cout << "Total Fine: " << totalAmount << endl;
        if (account.getAmountpaid() < 0)
        {
            // If the Student has not paid fines while returning the book then the amount will be negative
            cout << "Previous Dues: " << -1 * account.getAmountpaid() << endl;
        }
        else
        {

            cout << "Amount Paid: " << account.getAmountpaid() << endl;
        }
        cout << "Amount Due: " << totalAmount - account.getAmountpaid() << endl;
    }

    cout << "--------------------------------------------------\n";
}

// Function to calculate fine for a student
int Student::calculateFine(Library &library)
{
    vector<Account::BorrowedBook> borrowedBooks = getAccount().getBorrowedBooks(); // Get borrowed books
    time_t now = time(0);                                                          // Get current time
    struct tm dueDate = {};
    bool hasFines = false;
    int totalAmount = 0;

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

        // Get user-specific fine settings
        if (daysBorrowed > maxBorrowPeriod)
        { // `maxBorrowPeriod` is inherited from `User`
            hasFines = true;
            int overdueDays = daysBorrowed - maxBorrowPeriod;
            int fineAmount = overdueDays * finePerDay; // `finePerDay` is inherited from `User`
            totalAmount += fineAmount;

            // Get book details
            Book *book = library.findBookById(bookId);
            string bookTitle = book ? book->getTitle() : "Unknown";
        }
    }

    if (!hasFines)
    {
        return 0;
    }

    else
    {
        return totalAmount - account.getAmountpaid();
    }
}

// Function to make payment for a student
void Student::makePayement(Library &library, int paymentAmount)
{
    int fine = this->calculateFine(library);
    if (fine <= 0)
    {
        cout << "You have no payments to pay" << endl;
        cout << "Amount returned: " << paymentAmount << endl;
        return;
    }
    else
    {
        if (paymentAmount >= fine)
        {
            // If the payment amount is greater than the fine amount then the remaining amount will be returned
            cout << "Amount returned: " << paymentAmount - fine << endl;
            account.setAmountpaid(fine + account.getAmountpaid());
        }
        else
        {
            // If the payment amount is less than the fine amount then the remaining amount which is to be paid will be displayed
            cout << "You have still " << fine - paymentAmount << " to pay" << endl;
            account.setAmountpaid(paymentAmount + account.getAmountpaid());
        }
    }
}

// Function to calculate fine for a particular book
int Student::fineForBook(int bookId, Library &library)
{
    bool isBookBorrowed = false;
    Account::BorrowedBook borrowedBook;
    time_t now = time(0); // Get current time
    struct tm dueDate = {};
    int FineAmount = 0;
    for (auto &Book : account.getBorrowedBooks())
    {
        if (Book.bookId == bookId)
        {
            isBookBorrowed = true;
            borrowedBook = Book;
            break;
        }
    }
    if (!isBookBorrowed)
    {
        return 0;
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
        int fineAmount = overdueDays * finePerDay; // `finePerDay` is inherited from `User`
        FineAmount = fineAmount;
    }
    return FineAmount;
}

// Function to return a book
void Student::returnBook(int bookId, Library &library)
{
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
    if (fineForBook(bookId, library) > 0)
    {
        // The fine for the book which is being returned is calculated and subtracted from the total amount paid by the student
        // If total amount can go less than 0
        account.setAmountpaid(account.getAmountpaid() - fineForBook(bookId, library));
    }
    // Calculate the return time
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
    // Display overdue books for the book being returned
    this->displayOverDueForBook(bookId, library);
    account.addToHistory(bookId);
    vector<Account::BorrowedBook> temp;
    vector<Account::BorrowedBook> borrowedBooks = getAccount().getBorrowedBooks();
    for (auto &borrowedBook : borrowedBooks)
    {
        if (borrowedBook.bookId != bookId)
        {
            temp.push_back(borrowedBook);
        }
    }
    // Remove the book from the student's account
    account.deleteBorrowedBooks();
    for (auto &borrowedBook : temp)
    {
        account.addToBorrowedBooks(borrowedBook.bookId, borrowedBook.borrowTimestamp);
    }
    // Mark the book as available
    book->setBorrowerId(-1);
    book->setStatus("Available");
    cout << "Book ID " << bookId << " successfully returned on " << returnTime << "." << endl;
    cout << "--------------------------------------------------" << endl;
}

// Function to display overdue books for a particular book
void Student::displayOverDueForBook(int bookID, Library &library)
{
    Book *book = library.findBookById(bookID);
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
        string bookTitle = book ? book->getTitle() : "Unknown";

        cout << "Book ID: " << bookID << " | Title: " << bookTitle
             << " | Overdue by: " << overdueDays << " days"
             << " |Borrowed on: " << borrowTime << endl;
    }
}

// Function to display overdue books for a student
void Student::displayOverDueBooks(Library &library)
{
    vector<Account::BorrowedBook> borrowedBooks = account.getBorrowedBooks();
    time_t now = time(0); // Get current time
    struct tm dueDate = {};
    bool hasOverDues = false;

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

        // Get user-specific fine settings
        if (daysBorrowed > maxBorrowPeriod)
        { // `maxBorrowPeriod` is inherited from `User`
            cout << "maxtime:" << maxBorrowPeriod << endl;
            cout << "daysBorrowed:" << daysBorrowed << endl;
            hasOverDues = true;
            int overdueDays = daysBorrowed - maxBorrowPeriod;

            // Get book details
            Book *book = library.findBookById(bookId);
            string bookTitle = book ? book->getTitle() : "Unknown";

            cout << "Book ID: " << bookId << " | Title: " << bookTitle
                 << " | Overdue by: " << overdueDays << " days"
                 << " |Borrowed on: " << borrowTime << endl;
        }
    }
    cout << "--------------------------------------------------\n";

    if (!hasOverDues)
    {
        cout << "No Overdues\n";
    }
}
