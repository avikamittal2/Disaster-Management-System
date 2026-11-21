#include "DisasterManagementSystem.h"

int main() {
    DisasterManagementSystem system;
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "       DISASTER MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Disaster Management Record\n";
        cout << "2. Resource Management\n";
        cout << "3. Emergency Request\n";
        cout << "4. Route Navigation\n";
        cout << "5. Audit History\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.disasterModule(); break;
            case 2: system.resourceModule(); break;
            case 3: system.emergencyModule(); break;
            case 4: system.routeModule(); break;
            case 5: system.auditModule(); break;
            case 0: cout << "Exiting system. Stay safe!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
