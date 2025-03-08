# 📚 Library Management System

A comprehensive Library Management System built using **C++** to manage books, users, and transactions. Supports students, faculty, and librarians with essential library functionalities and file-based data persistence.

## 📖 Table of Contents

- [Features](#features)
- [Setup](#setup)
- [Run Instructions](#run-instructions)
- [Data Format](#data-format)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Important Instructions](#️-important-instructions)

**If you are testing this code, please use the data in Books.txt and Users.txt**

## Features

✅ Multi-role support (Students, Faculty, Librarians)  
✅ Book borrowing system with timestamps  
✅ Fine management with payment options  
✅ Easy tracking of overdue books and borrowing history  
✅ Librarian tools for book and user management  
✅ File-based data persistence for secure storage  
✅ Console-based interface with clear navigation

## Setup

1. **Clone the Repository**

```bash
git clone https://github.com/pranaysriharsha/Library-Management-System.git
cd Library-Management-System
```

## Run Instructions

Option 1: Compile Using find (Recommended for Linux/Unix)

```bash
g++ $(find . -name "*.cpp") -o main # Compiles all .cpp files
./main                              # Runs the compiled executable
```

Option 2: Compile by Listing Files (Recommended for Windows)

```bash
g++ main.cpp faculty.cpp user.cpp account.cpp library.cpp book.cpp student.cpp librarian.cpp -o main.exe # Compile all .cpp files
./main                                                                                                   # Runs the compiled executable

```

## Data Format

BookId,Title,Author,Publishers,ISBN,Year,Status,Borrowed ID
**Sample**
1,Introduction to Algorithms,Thomas H. Cormen,MIT Press,978-0-262-03384-8,2009,Borrowed,5

status can be anything among "Available","Borrowed" and "Reserved"

UserRole,UserId,RoleId,Name,Password,Email,AmountPaid,NoOfBorrowedBooks,Book1,Time1,...,NoOfBooksInHistory,BookIDs
**Sample**
Student,5,231052,akhil,pbat123,akhil23@iitk.ac.in,0,3,10,2025-03-07 16:51:14,16,2025-03-07 16:53:43,1,2025-03-08 10:10:11,4,1,2,15,6

UserRole can be anything among "Student","Faculty" and "Librarian"
RoleId:

- "RollNo for Student"
- "EmployeeId for Faculty"
- "Librarian Id for Librarian"

## Usage

📖 Introduction
The Library Management System is a console-based application designed to efficiently manage library operations for Students, Faculty, and Librarians. It provides a user-friendly interface for borrowing, returning, and tracking books while ensuring data is securely stored using file handling techniques.

🔹 Key Features

- Multi-role access with unique features for Students, Faculty, and Librarians.
- Book borrowing system with timestamps for accurate tracking.
- Fine management system to calculate, track, and allow users to pay fines.
- Librarians can manage book records and user details.
- Data persistence using file handling to ensure all changes are saved automatically.
- Whether you are a student looking to borrow books, a faculty member tracking borrowed resources, or a librarian managing the system, this application simplifies the entire process.

📋 Step-by-Step Instructions

- Run the Program using the commands mentioned in [Run Instructions](#run-instructions) session.
  🔐 Login Instructions
  When you run the application, you'll see the following menu:

  1.  **Enter `1`** for Student Login
  2.  **Enter `2`** for Faculty Login
  3.  **Enter `3`** for Librarian Login
  4.  **Enter `4`** to Exit the Program

💡 **Tip:** Ensure you follow the correct input format to avoid errors.

### 📋 Usage Instructions

**If you are testing, use data from Books.txt and Users.txt**

When logged in as a Student, you will see the following menu:

#### 📋 Student Menu Options

- **Enter `1`** to display all books
- **Enter `2`** to borrow a book
- **Enter `3`** to return a book
- **Enter `4`** to display borrowed books
- **Enter `5`** to display your history
- **Enter `6`** to display fine
- **Enter `7`** to pay fine
- **Enter `8`** to display overdue books
- **Enter `9`** to exit

When you logged in as Faculty you will see the following menu:

#### 📋 Faculty Menu Options

- **Enter `1`** to display all books
- **Enter `2`** to know the status of a particular book
- **Enter `3`** to borrow a book
- **Enter `4`** to return a book
- **Enter `5`** to display borrowed books
- **Enter `6`** to display your history
- **Enter `7`** to display overdue books
- **Enter `8`** to exit

When you logged in as a Librarian You will see the following menu:

#### 📋 Librarian Menu Options

- **Enter `1`** to display all books
- **Enter `2`** to add a book
- **Enter `3`** to remove a book
- **Enter `4`** to add a new user
- **Enter `5`** to remove a user
- **Enter `6`** to update a book
- **Enter `7`** to update a user
- **Enter `8`** to display all users
- **Enter `9`** to display all books
- **Enter `10`** to exit

# File Structure

LIBMS/  
├── .vscode/ # VS Code settings folder  
├── 📄 account.cpp # Account class implementation  
├── 📄 account.h # Header file for Account class  
├── 📄 book.cpp # Book class implementation  
├── 📄 book.h # Header file for Book class  
├── 📄 Books.txt # Sample book data  
├── 📄 faculty.cpp # Faculty class implementation  
├── 📄 faculty.h # Header file for Faculty class  
├── 📄 librarian.cpp # Librarian class implementation  
├── 📄 librarian.h # Header file for Librarian class  
├── 📄 library.cpp # Library core logic  
├── 📄 library.h # Header file for Library class  
├── 📄 main.cpp # Entry point of the program  
├── 📄 main.exe # Compiled executable (Windows)  
├── 📄 ReadMe.md # Project documentation  
├── 📄 student.cpp # Student class implementation  
├── 📄 student.h # Header file for Student class  
├── 📄 user.cpp # User class implementation  
├── 📄 user.h # Header file for User class  
└── 📄 Users.txt # Sample user data

# ⚠️ Important Instructions

Please follow these guidelines to ensure smooth usage and testing of the system:

- ➤ **Enter valid data** to avoid unexpected errors or system crashes.
- ➤ **If you are testing:**
  - Use the data available in **Books.txt** and **Users.txt**.
  - For **Book IDs**, refer to the **Books.txt** or use the **Display Books** command in the interface for correct numbers.
- ➤ **Do not modify the data format** in the `.txt` files directly.
- ➤ Always update or modify data using the **command line interface** to maintain data integrity.

# 📞 Contact

If you have any questions or suggestions, feel free to reach out. I'm happy to help!

📧 **Email:** [surepally23@iitk.ac.in](mailto:surepally23@iitk.ac.in)
