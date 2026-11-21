 // MODULE 3: EMERGENCY REQUEST

    void addRequest() {
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

        requests.push_back(r);

        for (int i = 0; i < (int)requests.size() - 1; i++) {
            for (int j = 0; j < (int)requests.size() - i - 1; j++) {
                if (requests[j].priorityValue <
                    requests[j + 1].priorityValue) {

                    Request temp = requests[j];
                    requests[j] = requests[j + 1];
                    requests[j + 1] = temp;
                }
            }
        }

        pushHistory("Added emergency request: " + r.id);

        cout << "Emergency request added and prioritized.\n";
    }

    void viewRequests() {
        if (requests.empty()) {
            cout << "No emergency requests found.\n";
            return;
        }

        cout << "\n--- Emergency Requests (Highest Priority First) ---\n";

        for (int i = 0; i < (int)requests.size(); i++) {
            cout << "\nRequest ID: " << requests[i].id
                 << "\nDescription: " << requests[i].description
                 << "\nLocation: " << requests[i].location
                 << "\nPriority: " << requests[i].priority << "\n";
        }
    }

    void processRequest() {
        if (requests.empty()) {
            cout << "No pending emergency requests.\n";
            return;
        }

        cout << "\nProcessing highest-priority request:\n";
        cout << "Request ID: " << requests[0].id << "\n";
        cout << "Description: " << requests[0].description << "\n";
        cout << "Location: " << requests[0].location << "\n";
        cout << "Priority: " << requests[0].priority << "\n";

        string id = requests[0].id;

        requests.erase(requests.begin());

        pushHistory("Processed emergency request: " + id);

        cout << "Request processed successfully.\n";
    }

    void emergencyModule() {
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
