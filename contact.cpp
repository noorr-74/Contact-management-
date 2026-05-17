#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;

// Global variables
User users[100];
Contact contacts[100];
int userCount = 0;
int contactCount = 0;

void loadUsers() {
    ifstream file("users.txt");
    userCount = 0;
    while (file >> users[userCount].username >> users[userCount].password) {
        userCount++;
    }
    file.close();
}

void saveUsers() {
    ofstream file("users.txt");
    for (int i = 0; i < userCount; i++) {
        file << users[i].username << " " << users[i].password << endl;
    }
    file.close();
}

void loadContacts() {
    ifstream file("contacts.txt");
    contactCount = 0;
    string line;

    while (getline(file, contacts[contactCount].name) &&
        getline(file, contacts[contactCount].phone) &&
        getline(file, contacts[contactCount].email)) {

        // Read the category (if it exists in the file)
        if (!getline(file, contacts[contactCount].category)) {
            contacts[contactCount].category = ""; // Set empty category if not found
        }

        contactCount++;
    }
    file.close();
}

void saveContacts() {
    ofstream file("contacts.txt");
    for (int i = 0; i < contactCount; i++) {
        file << contacts[i].name << endl;
        file << contacts[i].phone << endl;
        file << contacts[i].email << endl;
        file << contacts[i].category << endl; // Save the category
    }
    file.close();
}

void signUp() {
    cin.ignore();
    cout << "Enter a username: ";
    getline(cin, users[userCount].username);

    cout << "Enter a password: ";
    getline(cin, users[userCount].password);

    userCount++;
    saveUsers();
    cout << "Sign up successful!\n";
}

bool logIn() {
    string username, password;
    cin.ignore();

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login successful!\n";
            return true;
        }
    }

    cout << "Invalid username or password.\n";
    return false;
}

void addContact() {
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, contacts[contactCount].name);

    cout << "Enter phone: ";
    getline(cin, contacts[contactCount].phone);

    // Validate phone number
    bool validPhone = true;
    for (char c : contacts[contactCount].phone) {
        if (c < '0' || c > '9') {
            validPhone = false;
            break;
        }
    }

    if (!validPhone) {
        cout << "Invalid phone number! Only digits are allowed.\n";
        return;
    }

    cout << "Enter email: ";
    getline(cin, contacts[contactCount].email);

    cout << "Enter category (family, friends, work, etc.): ";
    getline(cin, contacts[contactCount].category);

    contactCount++;
    saveContacts();
    cout << "Contact added!\n";
}

void searchContact() {
    string searchName;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].name == searchName) {
            cout << "Found: " << contacts[i].name << ", "
                << contacts[i].phone << ", "
                << contacts[i].email;

            if (!contacts[i].category.empty()) {
                cout << ", Category: " << contacts[i].category;
            }

            cout << endl;
            found = true;
        }
    }

    if (!found) cout << "Contact not found.\n";
}

void editContact() {
    string search;
    cout << "Enter name, phone, or email to edit: ";
    cin.ignore();
    getline(cin, search);

    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].name == search || contacts[i].phone == search || contacts[i].email == search) {
            cout << "Editing contact: " << contacts[i].name << endl;

            cout << "Enter new name: ";
            getline(cin, contacts[i].name);

            cout << "Enter new phone: ";
            getline(cin, contacts[i].phone);

            cout << "Enter new email: ";
            getline(cin, contacts[i].email);

            cout << "Enter new category: ";
            getline(cin, contacts[i].category);

            saveContacts();
            cout << "Contact updated!\n";
            return;
        }
    }

    cout << "Contact not found.\n";
}

void deleteContact() {
    cin.ignore();
    string search;

    cout << "Enter name, phone, or email to delete: ";
    getline(cin, search);

    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].name == search || contacts[i].phone == search || contacts[i].email == search) {
            contacts[i] = contacts[contactCount - 1];
            contactCount--;

            saveContacts();

            cout << "Contact deleted!\n";
            return;
        }
    }

    cout << "Contact not found.\n";
}

void displayContacts() {
    if (contactCount == 0) {
        cout << "No contacts to display.\n";
        return;
    }

    cout << "--- Contact List ---\n";
    for (int i = 0; i < contactCount; i++) {
        cout << i + 1 << ". " << contacts[i].name << ", "
            << contacts[i].phone << ", "
            << contacts[i].email;

        if (!contacts[i].category.empty()) {
            cout << ", Category: " << contacts[i].category;
        }

        cout << endl;
    }
}

string toLowerCase(const string& str) {
    string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a'; // Convert uppercase to lowercase
        }
    }
    return result;
}

bool containsSubstring(const string& str, const string& substr) {
    if (substr.empty()) return true; // Empty substring always matches
    size_t strLen = str.length();
    size_t substrLen = substr.length();

    for (size_t i = 0; i <= strLen - substrLen; ++i) {
        bool match = true;
        for (size_t j = 0; j < substrLen; ++j) {
            if (str[i + j] != substr[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

void filterContacts() {
    char filterChoice;
    cout << "\n----- Filter Contacts by Category -----\n";
    cout << "1. By exact category (family, friends, work)\n";
    cout << "2. By partial category name\n";
    cout << "Enter your choice (1-2): ";
    cin >> filterChoice;

    // Validate filter choice
    while (filterChoice != '1' && filterChoice != '2') {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin >> filterChoice;
    }

    cin.ignore();
    string searchTerm;
    cout << "Enter category to search for: ";
    getline(cin, searchTerm);

    // Convert search term to lowercase
    searchTerm = toLowerCase(searchTerm);

    bool found = false;
    cout << "\n===== Filtered Results =====\n";

    for (int i = 0; i < contactCount; ++i) {
        string category = toLowerCase(contacts[i].category); // Convert category to lowercase

        bool matches = false;
        if (filterChoice == '1') {
            matches = (category == searchTerm); // Exact match
        }
        else {
            matches = containsSubstring(category, searchTerm); // Partial match
        }

        if (matches) {
            cout << "\nContact #" << (i + 1) << ":\n";
            cout << "Name: " << contacts[i].name << endl;
            cout << "Phone: " << contacts[i].phone << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Category: " << contacts[i].category << endl;
            cout << "------------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No matching contacts found.\n";
    }
}
