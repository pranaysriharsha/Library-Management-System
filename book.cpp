#include "book.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor correctly initializes private members
Book::Book(int id, string title, string author, string publisher, string isbn, int year, string status, int borrowerId)
    : id(id), title(title), author(author), publisher(publisher), isbn(isbn), year(year), status(status), borrowerId(borrowerId) {}

// Getters for accessing private members
int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
string Book::getISBN() const { return isbn; }
int Book::getYear() const { return year; }
string Book::getStatus() const { return status; }
int Book::getBorrowerId() const { return borrowerId; }

// Setters for controlled modifications
void Book::setStatus(const string &newStatus) { status = newStatus; }
void Book::setBorrowerId(int newBorrowerId) { borrowerId = newBorrowerId; }
void Book ::setTitle(const string &newTitle) { title = newTitle; }
void Book ::setAuthor(const string &newAuthor) { author = newAuthor; }
void Book ::setPublisher(const string &newPublisher) { publisher = newPublisher; }
void Book ::setISBN(const string &newISBN) { isbn = newISBN; }
void Book ::setYear(const int &newYear) { year = newYear; }

// ✅ Display function
void Book::display() const
{
    cout << "ID: " << id << ", Title: " << title << ", Author: " << author
         << ", Publisher: " << publisher << ", ISBN: " << isbn
         << ", Year: " << year << ", Status: " << status
         << ", Borrower ID: " << borrowerId << endl;
}

// ✅ isAvailable function
bool Book::isAvailable() const
{
    return status == "Available";
}