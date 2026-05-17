#include <iostream>
#include "header.h"

int main() {
    loadUsers();
    loadContacts();

    int choice;
    bool loggedIn = false;

    while (true) {
        if (!loggedIn) {
            std::cout << "\n=== CONTACT MANAGEMENT SYSTEM ===\n";
            std::cout << "1. Sign Up\n";
            std::cout << "2. Log In\n";
            std::cout << "3. Exit\n";
            std::cout << "Enter choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                loggedIn = logIn();
                break;
            case 3:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
            }
        }
        else {
            std::cout << "\n=== CONTACT MANAGEMENT ===\n";
            std::cout << "1. Add Contact\n";
            std::cout << "2. Search Contact\n";
            std::cout << "3. Edit Contact\n";
            std::cout << "4. Delete Contact\n";
            std::cout << "5. Display All Contacts\n";
            std::cout << "6. Filter Contacts\n"; // Added filter option
            std::cout << "7. Log Out\n";
            std::cout << "8. Exit\n";
            std::cout << "Enter choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                displayContacts();
                break;
            case 6:
                filterContacts(); // Added filter function call
                break;
            case 7:
                loggedIn = false;
                std::cout << "Logged out successfully.\n";
                break;
            case 8:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    }

    return 0;
}