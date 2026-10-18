#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


void clearBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

string readString(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int readInt(const string& prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val)) {
        cout << "Invalid number. Try again: ";
        clearBuffer();
    }
    clearBuffer();
    return val;
}

// 1. DATA MODELS / CLASSES

class AffectedPerson {
private:
    string id, name, location, status;

public:
    AffectedPerson(string i, string n, string l, string s) 
        : id(i), name(n), location(l), status(s) {}

    string getId() const { return id; }
    string getName() const { return name; }
    string getLocation() const { return location; }
    string getStatus() const { return status; }
    void setStatus(const string& newStatus) { status = newStatus; }

    void display() const {
        cout << "[ID: " << id << "] Name: " << name 
             << " | Location: " << location 
             << " | Status: " << status << "\n";
    }
};

class RescueTeam {
private:
    string id, name, specialization;

public:
    RescueTeam(string i, string n, string spec) 
        : id(i), name(n), specialization(spec) {}

    void display() const {
        cout << "[Team ID: " << id << "] Name: " << name 
             << " | Specialization: " << specialization << "\n";
    }
};

struct Disaster {
    string id;
    string details;
};

struct Resource {
    string name;
    int quantity;
};

struct EmergencyRequest {
    string requestId;
    string complainantName;
    string urgency; 
    int priority;   
};

struct Route {
    string source;
    string destination;
    int distance;
}};

// 2. CORE MODULES

// Module 1: Disaster Management
class DisasterModule {
private:
    vector<Disaster> disasters;

public:
    void registerDisaster(const string& id, const string& details) {
        disasters.push_back({id, details});
        cout << "--> Disaster registered: " << id << "\n";
    }

    void updateDisaster(const string& id, const string& newDetails) {
        for (auto& d : disasters) {
            if (d.id == id) {
                d.details = newDetails;
                cout << "--> Disaster updated successfully.\n";
                return;
            }
        }
        cout << "--> Disaster ID not found.\n";
    }

    void viewDisasters() const {
        if (disasters.empty()) {
            cout << "No active disasters.\n";
            return;
        }
        cout << "\n--- ACTIVE DISASTERS ---\n";
        for (const auto& d : disasters) {
            cout << "ID: " << d.id << " | Details: " << d.details << "\n";
        }
    }
};

// Module 2: Resource Management
class ResourceModule {
private:
    vector<Resource> inventory;

public:
    void addResource(const string& name, int qty) {
        for (auto& r : inventory) {
            if (r.name == name) {
                r.quantity += qty;
                cout << "--> Updated stock. Total units of " << name << ": " << r.quantity << "\n";
                return;
            }
        }
        inventory.push_back({name, qty});
        cout << "--> Added " << qty << " units of " << name << ".\n";
    }

    void allocateResource(const string& name, int qty) {
        for (auto& r : inventory) {
            if (r.name == name) {
                if (r.quantity >= qty) {
                    r.quantity -= qty;
                    cout << "--> Allocated " << qty << " units of " << name << ".\n";
                } else {
                    cout << "--> Error: Insufficient inventory.\n";
                }
                return;
            }
        }
        cout << "--> Resource not found.\n";
    }

    void displayResources() const {
        if (inventory.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }
        cout << "\n--- RESOURCE INVENTORY ---\n";
        for (const auto& r : inventory) {
            cout << "Resource: " << r.name << " | Available: " << r.quantity << "\n";
        }
    }
};

// Module 3: Emergency Requests (Priority handling using simple vector sorting)
class EmergencyRequestModule {
private:
    vector<EmergencyRequest> requests;

public:
    void pushRequest(const string& id, const string& name, const string& urgency) {
        int weight = 1;
        if (urgency == "High" || urgency == "high") weight = 3;
        else if (urgency == "Medium" || urgency == "medium") weight = 2;

        requests.push_back({id, name, urgency, weight});
        
        // Sort vector so highest priority stays at the front
        sort(requests.begin(), requests.end(), [](const EmergencyRequest& a, const EmergencyRequest& b) {
            return a.priority > b.priority;
        });

        cout << "--> Request logged for " << name << ".\n";
    }

    void processNextRequest() {
        if (requests.empty()) {
            cout << "No pending emergency requests.\n";
            return;
        }
        EmergencyRequest req = requests.front();
        requests.erase(requests.begin()); 

        cout << "--> Processing Request ID: " << req.requestId 
             << " | From: " << req.complainantName 
             << " | Urgency: " << req.urgency << "\n";
    }

    void viewPendingRequests() const {
        if (requests.empty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "\n--- PENDING EMERGENCY REQUESTS ---\n";
        for (const auto& r : requests) {
            cout << "ID: " << r.requestId << " | Name: " << r.complainantName 
                 << " | Urgency: " << r.urgency << "\n";
        }
    }
};

// Module 4: Route Navigation
class RouteModule {
private:
    vector<Route> routes;

public:
    void addRoute(const string& u, const string& v, int distance) {
        routes.push_back({u, v, distance});
        cout << "--> Route added between " << u << " and " << v << " (" << distance << " km)\n";
    }

    void findShortestPath(const string& start, const string& target) const {
        for (const auto& r : routes) {
            if ((r.source == start && r.destination == target) || 
                (r.source == target && r.destination == start)) {
                cout << "\n--- ROUTE FOUND ---\n";
                cout << "Direct Distance: " << r.distance << " km\n";
                cout << "Path: " << start << " -> " << target << "\n";
                return;
            }
        }
        cout << "No direct route found between " << start << " and " << target << ".\n";
    }
};

// Module 5: Audit History Logging
class HistoryModule {
private:
    vector<string> historyLogs;

public:
    void logAction(const string& action) {
        historyLogs.push_back(action);
    }

    void viewHistory() const {
        if (historyLogs.empty()) {
            cout << "No actions recorded yet.\n";
            return;
        }
        cout << "\n--- ACTION HISTORY LOGS ---\n";
        for (int i = historyLogs.size() - 1; i >= 0; --i) {
            cout << "- " << historyLogs[i] << "\n";
        }
    }
};

/*3.Main System Controller*/
class DisasterManagementSystem {
private:
    DisasterModule disasterMod;
    ResourceModule resourceMod;
    EmergencyRequestModule requestMod;
    RouteModule routeMod;
    HistoryModule historyMod;
    
    vector<AffectedPerson> affectedPeople;
    vector<RescueTeam> rescueTeams;

public:
    void addAffectedPerson(string id, string name, string loc, string status) {
        affectedPeople.push_back(AffectedPerson(id, name, loc, status));
        historyMod.logAction("Added affected person: " + name);
        cout << "--> Affected person registered successfully.\n";
    }

    void searchAffectedPerson(const string& nameQuery) const {
        cout << "\n--- SEARCH RESULTS FOR: " << nameQuery << " ---\n";
        bool found = false;
        for (const auto& person : affectedPeople) {
            if (person.getName().find(nameQuery) != string::npos) {
                person.display();
                found = true;
            }
        }
        if (!found) cout << "No matching records found.\n";
    }

    void updatePersonStatus(const string& idOrName, const string& newStatus) {
        bool found = false;
        for (auto& person : affectedPeople) {
            if (person.getId() == idOrName || person.getName() == idOrName) {
                person.setStatus(newStatus);
                cout << "--> Updated status for " << person.getName() << " to: " << newStatus << "\n";
                historyMod.logAction("Updated status of " + person.getName() + " to " + newStatus);
                found = true;
                break;
            }
        }
        if (!found) cout << "--> Person not found.\n";
    }

    void addRescueTeam(string id, string name, string spec) {
        rescueTeams.push_back(RescueTeam(id, name, spec));
        historyMod.logAction("Registered rescue team: " + name);
        cout << "--> Rescue team registered.\n";
    }

    void displayAllTeams() const {
        if (rescueTeams.empty()) {
            cout << "\nNo rescue teams registered.\n";
            return;
        }
        cout << "\n--- RESCUE TEAMS LIST ---\n";
        for (const auto& team : rescueTeams) {
            team.display();
        }
    }

    void saveDataToFile() {
        ofstream outFile("disaster_system_data.txt");
        if (!outFile) {
            cout << "Error opening file for writing!\n";
            return;
        }
        outFile << "--- AFFECTED PEOPLE ---\n";
        for (const auto& p : affectedPeople) {
            outFile << p.getId() << "," << p.getName() << "," << p.getLocation() << "," << p.getStatus() << "\n";
        }
        outFile.close();
        cout << "--> Data saved to 'disaster_system_data.txt'.\n";
        historyMod.logAction("Data saved to file.");
    }

    DisasterModule& getDisasterMod() { return disasterMod; }
    ResourceModule& getResourceMod() { return resourceMod; }
    EmergencyRequestModule& getRequestMod() { return requestMod; }
    RouteModule& getRouteMod() { return routeMod; }
    HistoryModule& getHistoryMod() { return historyMod; }
};
