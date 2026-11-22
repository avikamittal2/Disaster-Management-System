/* Main File */
#include "DisasterManagementSystem.h"

int main() {
    DisasterManagementSystem system;
    int choice;

    while (true) {
        // Authentication 
        while (!system.isLoggedIn()) {
            cout << "\n========================================\n";
            cout << "   DISASTER MANAGEMENT SYSTEM - LOGIN\n";
            cout << "========================================\n";
            cout << "Default Admin -> ID: admin | Pass: admin123\n";
            cout << "----------------------------------------\n";
            cout << "1. Login\n";
            cout << "2. Register New User\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                system.login();
            } else if (choice == 2) {
                system.registerUser();
            } else if (choice == 0) {
                cout << "Exiting system. Stay safe!\n";
                return 0;
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        }

        // Main System Menu (Accessible only when authenticated)
        do {
            cout << "\n========================================\n";
            cout << "       DISASTER MANAGEMENT SYSTEM\n";
            cout << "       Active User: " << system.getCurrentUser() << "\n";
            cout << "========================================\n";
            cout << "1. Disaster Management Record\n";
            cout << "2. Resource Management\n";
            cout << "3. Emergency Request\n";
            cout << "4. Route Navigation\n";
            cout << "5. Audit History\n";
            cout << "6. User Authentication & Account\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: system.disasterModule(); break;
                case 2: system.resourceModule(); break;
                case 3: system.emergencyModule(); break;
                case 4: system.routeModule(); break;
                case 5: system.auditModule(); break;
                case 6: system.authMenu(); break;
                case 0:
                    system.logout();
                    cout << "Exiting system. Stay safe!\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (system.isLoggedIn());
    }

    return 0;
}
