#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

class Library;

class Faculty : public User
{
private:
    int employeeId; // Unique Employee ID

public:
    int finePerDay;          // Fine per day for overdue books
    int maxBooksAllowed;     // Maximum number of books allowed to borrow
    int maxBorrowPeriod;     // Maximum number of days a book can be borrowed
    int maxLimitAfterBorrow; // Maximum Days after which new books cannot be borrowed
    // Constructor
    Faculty(int userId, int employeeId, const string &name, const string &password, const string &email);
    int getEmployeeId() const;
    void setEmployeeId(int newEmployeeId);
    const Account &getAccount() const;                        // Get account this cannot change the account
    Account &getAccount();                                    // Get account
    void borrowBook(int bookId, Library &library) override;   // Borrow a book
    bool overDueCheck(Library &library);                      // Check if the faculty has overdue books
    void displayOverDueBooks(Library &library);               // Display overdue books
    void returnBook(int bookId, Library &library) override;   // Return a book
    void displayOverDueForBook(int bookId, Library &library); // Display overdue books for a specific book
};

#endif // FACULTY_H
