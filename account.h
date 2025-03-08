#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;
class Library;

class Account
{
public:
    struct BorrowedBook
    {
        int bookId;
        string borrowTimestamp;
    };

private:
    // Structure to store book ID and timestamp
    vector<BorrowedBook> borrowedBooks; // Stores borrowed books with timestamps
    vector<int> history;                // Stores history of borrowed books
    int Amountpaid;                     // Stores Amount Paid to calculate Overall Fine
public:
    // Constructor
    Account();

    // Add a book to borrowedBooks list
    void addToBorrowedBooks(int bookId, const string &timestamp);
    void addToHistory(int bookId);                     // Add a book to history list
    vector<BorrowedBook> getBorrowedBooks() const;     // Get borrowed books
    vector<int> getHistory() const;                    // Get history of borrowed books
    int getAmountpaid() const;                         // Get amount paid
    void setAmountpaid(int amount);                    // Set amount paid
    void viewHistory(Library &library) const;          // View history of borrowed books
    void deleteBorrowedBooks();                        // Delete borrowed books
    void displayBorrowedBooks(Library &library) const; // Display borrowed books
};

#endif // ACCOUNT_H
