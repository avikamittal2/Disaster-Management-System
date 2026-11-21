 /* MODULE 5: AUDIT HISTORY */
   
 #include "DisasterManagementSystem.h"

void DisasterManagementSystem::viewHistory() {
    if (historyTop == NULL) {
        cout << "No audit history available.\n";
        return;
    }

    History* current = historyTop;

    cout << "\n--- Audit History (Latest First) ---\n";

    while (current != NULL) {
        cout << "- " << current->action << "\n";
        current = current->next;
    }
}

void DisasterManagementSystem::saveDataToFile() {
    ofstream file("disaster_data.txt");

    if (!file) {
        cout << "Unable to open file for saving.\n";
        return;
    }

    file << "DISASTER RECORDS\n";

    for (int i = 0; i < (int)disasters.size(); i++) {
        file << disasters[i].id << " | "
             << disasters[i].name << " | "
             << disasters[i].location << " | "
             << disasters[i].severity << "\n";
    }

    file << "\nAFFECTED PEOPLE\n";

    Person* current = peopleHead;

    while (current != NULL) {
        file << current->id << " | "
             << current->name << " | "
             << current->location << " | "
             << current->status << "\n";

        current = current->next;
    }

    file << "\nRESCUE TEAMS\n";

    for (int i = 0; i < (int)teams.size(); i++) {
        file << teams[i].id << " | "
             << teams[i].name << " | "
             << teams[i].location << " | "
             << teams[i].status << "\n";
    }

    file << "\nRESOURCES\n";

    for (int i = 0; i < (int)resources.size(); i++) {
        file << resources[i].name << " | "
             << resources[i].quantity << "\n";
    }

    file.close();

    pushHistory("Saved system data to file");

    cout << "Data saved to disaster_data.txt\n";
}

void DisasterManagementSystem::auditModule() {
    int choice;

    do {
        cout << "\n===== MODULE 5: AUDIT HISTORY =====\n";
        cout << "1. View Audit History\n";
        cout << "2. Save Data to File\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewHistory(); break;
            case 2: saveDataToFile(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}
