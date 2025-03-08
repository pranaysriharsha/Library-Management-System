#include "user.h"
#include <iostream>
#include <string>
using namespace std;

class Library;

// int User::counter = 0;

// Constructor
User::User(int userId, const string &name, const string &password, const string &role, const string &email)
    : userId(userId), name(name), password(password), role(role), email(email) {}

// Getters
int User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getPassword() const { return password; }
string User::getRole() const { return role; }
string User::getEmail() const { return email; }

// Setters
void User::setName(const string &newName) { name = newName; }
void User::setPassword(const string &newPassword) { password = newPassword; }
void User::setEmail(const string &newEmail) { email = newEmail; }
