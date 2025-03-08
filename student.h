#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "account.h"
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

class Library;

class Student : public User
{
private:
    int rollNo;

public:
    int finePerDay;      // Which is 10 for student
    int maxBooksAllowed; // Which is 3 for student
    int maxBorrowPeriod; // Which is 15 for student

    // Constructor
    Student(int userId, int rollNo, const string &name, const string &password, const string &email);
    int getRollNo() const;                                    // Function to get Roll No
    void setRollNo(int newRollNo);                            // Function to set Roll No
    const Account &getAccount() const;                        // Account which cannot change
    Account &getAccount();                                    // Account can be modified
    void borrowBook(int bookId, Library &library) override;   // Function to Borrow a book
    void displayFine(Library &library);                       // Function to display Fine
    int calculateFine(Library &library);                      // Function to Calculate Fine
    void makePayement(Library &library, int paymentAmount);   // Function to make a payment
    void returnBook(int bookId, Library &library) override;   // Return a Book
    int fineForBook(int bookId, Library &library);            // Returns fine for  a particular book
    void displayOverDueForBook(int bookId, Library &library); // Display OverDue for a particular Book
    void displayOverDueBooks(Library &library);               // Display all Overdue Books
};

#endif // STUDENT_H
