/* Disaster Management Header File */
#ifndef DISASTER_MANAGEMENT_SYSTEM_H
#define DISASTER_MANAGEMENT_SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>
using namespace std;

const int MAX_LOCATIONS = 100;

// ==================== DATA STRUCTURES ====================

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
    int sequence;
};

struct CompareRequest {
    bool operator()(const Request& a, const Request& b) {
        if (a.priorityValue == b.priorityValue) {
            return a.sequence > b.sequence;
        }
        return a.priorityValue < b.priorityValue;
    }
};

// ==================== DISASTER MANAGEMENT SYSTEM ====================

class DisasterManagementSystem {
private:
    Person* peopleHead;
    History* historyTop;

    vector<Disaster> disasters;
    vector<Team> teams;
    vector<Resource> resources;
    priority_queue<Request, vector<Request>, CompareRequest> requests;
    int requestCounter = 0;

    vector<string> locations;
    vector<pair<int, int> > graph[MAX_LOCATIONS];

    // Core Helpers (CoreHelpers.cpp)
    void pushHistory(string action);
    int findLocation(string name);
    int getOrAddLocation(string name);
    int priorityNumber(string priority);

public:
    DisasterManagementSystem();
    ~DisasterManagementSystem();

    // Module 1: Disaster Management Record (DisasterModule.cpp)
    void addDisaster();
    void updateDisaster();
    void viewDisasters();
    void addAffectedPerson();
    void viewAffectedPeople();
    void updatePersonStatus();
    void addTeam();
    void viewTeams();
    void disasterModule();

    // Module 2: Resource Management (ResourceModule.cpp)
    void addResource();
    void allocateResource();
    void viewResources();
    void resourceModule();

    // Module 3: Emergency Request (EmergencyModule.cpp)
    void addRequest();
    void viewRequests();
    void processRequest();
    void emergencyModule();

    // Module 4: Route Navigation (RouteModule.cpp)
    void addRoute();
    void findDirectRoute();
    void shortestRoute();
    void routeModule();

    // Module 5: Audit History (AuditModule.cpp)
    void viewHistory();
    void saveDataToFile();
    void auditModule();
};

#endif
