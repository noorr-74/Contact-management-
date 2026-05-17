#ifndef CONTACT_H
#define CONTACT_H


#include <string>
using namespace std;

// User structure
struct User {
    string username;
    string password;
};

// Contact structure
struct Contact {
    string name;
    string phone;
    string email;
    string category;
};

// Function declarations

// User functions
void loadUsers();
void saveUsers();
void signUp();
bool logIn();

// Contact functions
void loadContacts();
void saveContacts();
void addContact();
void searchContact();
void editContact();
void deleteContact();
void displayContacts();
void filterContacts();

// Helper functions
string toLowerCase(const string& str);
bool containsSubstring(const string& str, const string& substr);

#endif