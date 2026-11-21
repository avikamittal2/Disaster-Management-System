#include "DisasterManagementSystem.h"

void DisasterManagementSystem::addResource() {
    string name;
    int quantity;

    cout << "Enter resource name: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter quantity to add: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Quantity must be greater than zero.\n";
        return;
    }

    for (int i = 0; i < (int)resources.size(); i++) {
        if (resources[i].name == name) {
            resources[i].quantity += quantity;

            pushHistory("Added stock of resource: " + name);

            cout << "Resource stock updated.\n";
            return;
        }
    }

    Resource r;
    r.name = name;
    r.quantity = quantity;

    resources.push_back(r);

    pushHistory("Added resource: " + name);

    cout << "Resource added successfully.\n";
}

void DisasterManagementSystem::allocateResource() {
    if (resources.empty()) {
        cout << "No resources available.\n";
        return;
    }

    string name;
    int quantity;

    cout << "Enter resource name to allocate: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter quantity to allocate: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Quantity must be greater than zero.\n";
        return;
    }

    for (int i = 0; i < (int)resources.size(); i++) {
        if (resources[i].name == name) {
            if (resources[i].quantity >= quantity) {
                resources[i].quantity -= quantity;

                pushHistory("Allocated resource: " + name);

                cout << "Resource allocated successfully.\n";
            } else {
                cout << "Insufficient stock. Available quantity: "
                     << resources[i].quantity << "\n";
            }

            return;
        }
    }

    cout << "Resource not found.\n";
}

void DisasterManagementSystem::viewResources() {
    if (resources.empty()) {
        cout << "No resources found.\n";
        return;
    }

    cout << "\n--- Available Resource Stock ---\n";

    for (int i = 0; i < (int)resources.size(); i++) {
        cout << resources[i].name << " : "
             << resources[i].quantity << "\n";
    }
}

void DisasterManagementSystem::resourceModule() {
    int choice;

    do {
        cout << "\n===== MODULE 2: RESOURCE MANAGEMENT =====\n";
        cout << "1. Add Resource / Stock\n";
        cout << "2. Allocate Resource\n";
        cout << "3. View Stock\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addResource(); break;
            case 2: allocateResource(); break;
            case 3: viewResources(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}