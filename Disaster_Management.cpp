#include "DisasterManagementSystem.h"

void DisasterManagementSystem::addRequest() {
    Request r;

    cout << "Enter Request ID: ";
    cin >> r.id;

    cout << "Enter request description: ";
    cin >> ws;
    getline(cin, r.description);

    cout << "Enter request location: ";
    getline(cin, r.location);

    cout << "Enter priority (High/Medium/Low): ";
    getline(cin, r.priority);

    r.priorityValue = priorityNumber(r.priority);
    r.sequence = requestCounter++;

    requests.push(r);

    pushHistory("Added emergency request: " + r.id);

    cout << "Emergency request added and prioritized.\n";
}

void DisasterManagementSystem::viewRequests() {
    if (requests.empty()) {
        cout << "No emergency requests found.\n";
        return;
    }

    cout << "\n--- Emergency Requests (Highest Priority First) ---\n";

    priority_queue<Request, vector<Request>, CompareRequest> tempQueue = requests;

    while (!tempQueue.empty()) {
        Request current = tempQueue.top();
        tempQueue.pop();

        cout << "\nRequest ID: " << current.id
             << "\nDescription: " << current.description
             << "\nLocation: " << current.location
             << "\nPriority: " << current.priority << "\n";
    }
}

void DisasterManagementSystem::processRequest() {
    if (requests.empty()) {
        cout << "No pending emergency requests.\n";
        return;
    }

    Request topRequest = requests.top();

    cout << "\nProcessing highest-priority request:\n";
    cout << "Request ID: " << topRequest.id << "\n";
    cout << "Description: " << topRequest.description << "\n";
    cout << "Location: " << topRequest.location << "\n";
    cout << "Priority: " << topRequest.priority << "\n";

    requests.pop();

    pushHistory("Processed emergency request: " + topRequest.id);

    cout << "Request processed successfully.\n";
}

void DisasterManagementSystem::emergencyModule() {
    int choice;

    do {
        cout << "\n===== MODULE 3: EMERGENCY REQUEST =====\n";
        cout << "1. Add Emergency Request\n";
        cout << "2. View Pending Requests\n";
        cout << "3. Process Highest-Priority Request\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addRequest(); break;
            case 2: viewRequests(); break;
            case 3: processRequest(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}
