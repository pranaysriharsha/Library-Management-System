#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class Book
{
private:
    int id;
    string title;
    string author;
    string publisher;
    string isbn;
    int year;
    string status;
    int borrowerId;

public:
    //  Constructor
    Book(int id, string title, string author, string publisher, string isbn, int year, string status, int borrowerId);

    // Getter functions
    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    string getISBN() const;
    int getYear() const;
    string getStatus() const;
    int getBorrowerId() const;

    // Setter functions
    void setStatus(const string &newStatus);
    void setBorrowerId(int newBorrowerId);
    bool isAvailable() const;
    void setTitle(const string &newTitle);
    void setAuthor(const string &newAuthor);
    void setPublisher(const string &newPublisher);
    void setISBN(const string &newISBN);
    void setYear(const int &newYear);

    // Display function
    void display() const;
};

#endif
