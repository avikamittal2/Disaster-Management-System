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
