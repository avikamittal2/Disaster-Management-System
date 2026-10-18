#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// --- UTILITY INPUT HELPERS ---
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

// ==========================================
// 1. DATA MODELS / CLASSES
// ==========================================

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
