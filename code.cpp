#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

const int MAX_LOCATIONS = 100;

struct Person {
    string id, name, location, status;
    Person* next;
};

struct History {
    string action;
    History* next;
};

struct Team {
    string id, name, location, status;
};

struct Resource {
    string name;
    int quantity;
};

struct Disaster {
    string id, name, location, severity;
};

struct Request {
    string id, description, location, priority;
    int priorityValue;
};

// ==================== DISASTER MANAGEMENT SYSTEM ====================

class DisasterManagementSystem {
private:
    Person* peopleHead;
    History* historyTop;

    vector<Disaster> disasters;
    vector<Team> teams;
    vector<Resource> resources;
    vector<Request> requests;

    vector<string> locations;
    vector<pair<int, int> > graph[MAX_LOCATIONS];

    void pushHistory(string action) {
        History* temp = new History;
        temp->action = action;
        temp->next = historyTop;
        historyTop = temp;
    }

    int findLocation(string name) {
        for (int i = 0; i < (int)locations.size(); i++) {
            if (locations[i] == name)
                return i;
        }
        return -1;
    }

    int getOrAddLocation(string name) {
        int index = findLocation(name);

        if (index != -1)
            return index;

        if ((int)locations.size() >= MAX_LOCATIONS) {
            cout << "Maximum number of locations reached.\n";
            return -1;
        }

        locations.push_back(name);
        return (int)locations.size() - 1;
    }

    int priorityNumber(string priority) {
        if (priority == "High" || priority == "high" ||
            priority == "HIGH")
            return 3;

        if (priority == "Medium" || priority == "medium" ||
            priority == "MEDIUM")
            return 2;

        return 1;
    }

public:
    DisasterManagementSystem() {
        peopleHead = NULL;
        historyTop = NULL;
    }


    ~DisasterManagementSystem() {
        while (peopleHead != NULL) {
            Person* temp = peopleHead;
            peopleHead = peopleHead->next;
            delete temp;
        }

        while (historyTop != NULL) {
            History* temp = historyTop;
            historyTop = historyTop->next;
            delete temp;
        }
    }


    // ==================================================
    // MODULE 1: DISASTER MANAGEMENT RECORD
    // ==================================================

    void addDisaster() {
        Disaster d;

        cout << "Enter Disaster ID: ";
        cin >> d.id;

        for (int i = 0; i < (int)disasters.size(); i++) {
            if (disasters[i].id == d.id) {
                cout << "A disaster with this ID already exists.\n";
                return;
            }
        }

        cout << "Enter disaster name/type: ";
        cin >> ws;
        getline(cin, d.name);

        cout << "Enter location: ";
        getline(cin, d.location);

        cout << "Enter severity (Low/Medium/High): ";
        getline(cin, d.severity);

        disasters.push_back(d);

        pushHistory("Registered disaster: " + d.id);

        cout << "Disaster record added successfully.\n";
    }

    
    void updateDisaster() {
        if (disasters.empty()) {
            cout << "No disaster records available to update.\n";
            return;
        }

        string id;

        cout << "Enter Disaster ID to update: ";
        cin >> id;

        for (int i = 0; i < (int)disasters.size(); i++) {
            if (disasters[i].id == id) {
                cout << "\nExisting Disaster Details:\n";
                cout << "Name: " << disasters[i].name << "\n";
                cout << "Location: " << disasters[i].location << "\n";
                cout << "Severity: " << disasters[i].severity << "\n";

                cout << "\nEnter new disaster name/type: ";
                cin >> ws;
                getline(cin, disasters[i].name);

                cout << "Enter new location: ";
                getline(cin, disasters[i].location);

                cout << "Enter new severity (Low/Medium/High): ";
                getline(cin, disasters[i].severity);

                pushHistory("Updated disaster: " + id);

                cout << "Disaster record updated successfully.\n";
                return;
            }
        }

        cout << "Disaster ID not found.\n";
    }

    void viewDisasters() {
        if (disasters.empty()) {
            cout << "No disaster records found.\n";
            return;
        }

        cout << "\n--- Disaster Records ---\n";

        for (int i = 0; i < (int)disasters.size(); i++) {
            cout << "\nDisaster ID: " << disasters[i].id
                 << "\nName/Type: " << disasters[i].name
                 << "\nLocation: " << disasters[i].location
                 << "\nSeverity: " << disasters[i].severity << "\n";
        }
    }

    
    void addAffectedPerson() {
        Person* temp = new Person;

        cout << "Enter Person ID: ";
        cin >> temp->id;

        cout << "Enter name: ";
        cin >> ws;
        getline(cin, temp->name);

        cout << "Enter location: ";
        getline(cin, temp->location);

        cout << "Enter status (Missing/Rescued/Injured): ";
        getline(cin, temp->status);

        temp->next = NULL;

        if (peopleHead == NULL) {
            peopleHead = temp;
        } else {
            Person* current = peopleHead;

            while (current->next != NULL)
                current = current->next;

            current->next = temp;
        }

        pushHistory("Added affected person: " + temp->id);

        cout << "Affected person record added.\n";
    }

    void viewAffectedPeople() {
        if (peopleHead == NULL) {
            cout << "No affected-person records found.\n";
            return;
        }

        Person* current = peopleHead;

        cout << "\n--- Affected People ---\n";

        while (current != NULL) {
            cout << "\nID: " << current->id
                 << "\nName: " << current->name
                 << "\nLocation: " << current->location
                 << "\nStatus: " << current->status << "\n";

            current = current->next;
        }
    }

    void updatePersonStatus() {
        if (peopleHead == NULL) {
            cout << "No affected-person records found.\n";
            return;
        }

        string id;

        cout << "Enter Person ID: ";
        cin >> id;

        Person* current = peopleHead;

        while (current != NULL) {
            if (current->id == id) {
                cout << "Enter updated status: ";
                cin >> ws;
                getline(cin, current->status);

                pushHistory("Updated status for person: " + id);

                cout << "Person status updated.\n";
                return;
            }

            current = current->next;
        }

        cout << "Person ID not found.\n";
    }

    void addTeam() {
        Team t;

        cout << "Enter Team ID: ";
        cin >> t.id;

        cout << "Enter team name: ";
        cin >> ws;
        getline(cin, t.name);

        cout << "Enter team location: ";
        getline(cin, t.location);

        cout << "Enter team status (Available/Busy): ";
        getline(cin, t.status);

        teams.push_back(t);

        pushHistory("Added rescue team: " + t.id);

        cout << "Rescue team added successfully.\n";
    }

    void viewTeams() {
        if (teams.empty()) {
            cout << "No rescue teams found.\n";
            return;
        }

        cout << "\n--- Rescue Teams ---\n";

        for (int i = 0; i < (int)teams.size(); i++) {
            cout << "\nTeam ID: " << teams[i].id
                 << "\nName: " << teams[i].name
                 << "\nLocation: " << teams[i].location
                 << "\nStatus: " << teams[i].status << "\n";
        }
    }

    void disasterModule() {
        int choice;

        do {
            cout << "\n===== MODULE 1: DISASTER MANAGEMENT RECORD =====\n";
            cout << "1. Register Disaster\n";
            cout << "2. Update Disaster\n";
            cout << "3. View Disasters\n";
            cout << "4. Add Affected Person\n";
            cout << "5. View Affected People\n";
            cout << "6. Update Person Status\n";
            cout << "7. Add Rescue Team\n";
            cout << "8. View Rescue Teams\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addDisaster(); break;
                case 2: updateDisaster(); break;
                case 3: viewDisasters(); break;
                case 4: addAffectedPerson(); break;
                case 5: viewAffectedPeople(); break;
                case 6: updatePersonStatus(); break;
                case 7: addTeam(); break;
                case 8: viewTeams(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }

        } while (choice != 0);
    }
