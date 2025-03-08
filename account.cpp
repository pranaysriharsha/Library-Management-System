#include "account.h"
#include <iostream>
#include <string>
#include <vector>
#include "book.h"
#include "library.h"

using namespace std;

// Constructor
Account::Account()
{
    Amountpaid = 0;
}

// Add a book to the borrowed list with timestamp
void Account::addToBorrowedBooks(int bookId, const string &timestamp)
{
    BorrowedBook book = {bookId, timestamp};
    borrowedBooks.push_back(book);
}

// Add a book to the history list
void Account::addToHistory(int bookId)
{
    history.push_back(bookId);
}

// Get borrowed books
vector<Account::BorrowedBook> Account::getBorrowedBooks() const
{
    return borrowedBooks;
}

// Get history of borrowed books
vector<int> Account::getHistory() const
{
    return history;
}

// Get amount paid
int Account::getAmountpaid() const
{
    return Amountpaid;
}

// Set amount paid
void Account::setAmountpaid(int amount)
{
    Amountpaid = amount;
}

// View history of borrowed books
void Account::viewHistory(Library &library) const
{
    cout << "History of borrowed books:" << endl;
    for (const auto &bookId : history)
    {
        Book *book = library.findBookById(bookId);
        if (book)
        {
            cout << "Book ID: " << bookId << " | Title: " << book->getTitle() << endl;
        }
    }
}

// Delete borrowed books
void Account::deleteBorrowedBooks()
{
    while (this->borrowedBooks.size() > 0)
    {
        this->borrowedBooks.pop_back();
    }
}

// Display borrowed books
void Account::displayBorrowedBooks(Library &library) const
{
    cout << "Borrowed books:" << endl;
    for (const auto &book : borrowedBooks)
    {
        Book *bookEntry = library.findBookById(book.bookId);
        if (bookEntry)
        {
            cout << "Book ID: " << book.bookId << " | Book Tile: " << bookEntry->getTitle() << " | Borrowed at: " << book.borrowTimestamp << endl;
        }
    }
}