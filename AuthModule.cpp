#include "DisasterManagementSystem.h"

bool DisasterManagementSystem::isLoggedIn() const {
    return isAuthenticated;
}

string DisasterManagementSystem::getCurrentUser() const {
    return currentUser;
}

bool DisasterManagementSystem::login() {
    string userId, password;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    while (attempts < MAX_ATTEMPTS) {
        cout << "\n--- USER LOGIN ---\n";
        cout << "Enter User ID: ";
        cin >> userId;

        cout << "Enter Password: ";
        cin >> password;

        for (int i = 0; i < (int)users.size(); i++) {
            if (users[i].userId == userId && users[i].password == password) {
                currentUser = userId;
                isAuthenticated = true;
                pushHistory("User logged in");
                cout << "Login successful! Welcome, " << currentUser << ".\n";
                return true;
            }
        }

        attempts++;
        cout << "Invalid User ID or Password. Attempts remaining: "
             << (MAX_ATTEMPTS - attempts) << "\n";
    }

    cout << "Maximum login attempts exceeded.\n";
    return false;
}

void DisasterManagementSystem::registerUser() {
    string userId, password, confirmPassword;

    cout << "\n--- REGISTER NEW USER ---\n";
    cout << "Enter new User ID: ";
    cin >> userId;

    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].userId == userId) {
            cout << "User ID already exists. Please choose another.\n";
            return;
        }
    }

    cout << "Enter Password: ";
    cin >> password;

    cout << "Confirm Password: ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Passwords do not match. Registration cancelled.\n";
        return;
    }

    users.push_back({userId, password});
    pushHistory("Registered new user: " + userId);
    cout << "User '" << userId << "' registered successfully!\n";
}

void DisasterManagementSystem::changePassword() {
    if (!isAuthenticated) {
        cout << "You must be logged in to change your password.\n";
        return;
    }

    string oldPassword, newPassword, confirmPassword;

    cout << "\n--- CHANGE PASSWORD ---\n";
    cout << "Enter current password: ";
    cin >> oldPassword;

    int userIndex = -1;
    for (int i = 0; i < (int)users.size(); i++) {
        if (users[i].userId == currentUser) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1 || users[userIndex].password != oldPassword) {
        cout << "Incorrect current password.\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> newPassword;

    cout << "Confirm new password: ";
    cin >> confirmPassword;

    if (newPassword != confirmPassword) {
        cout << "New passwords do not match.\n";
        return;
    }

    users[userIndex].password = newPassword;
    pushHistory("Changed password");
    cout << "Password updated successfully.\n";
}

void DisasterManagementSystem::logout() {
    if (isAuthenticated) {
        pushHistory("User logged out");
        cout << "Logged out user: " << currentUser << "\n";
        currentUser = "";
        isAuthenticated = false;
    }
}

void DisasterManagementSystem::authMenu() {
    int choice;

    do {
        cout << "\n===== USER AUTHENTICATION & ACCOUNT =====\n";
        cout << "Logged in as: " << currentUser << "\n";
        cout << "1. Register New User\n";
        cout << "2. Change Password\n";
        cout << "3. Logout\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: changePassword(); break;
            case 3:
                logout();
                return; // Return immediately so main() prompts for login again
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0 && isAuthenticated);
}
