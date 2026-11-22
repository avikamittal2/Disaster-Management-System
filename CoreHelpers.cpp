#include "DisasterManagementSystem.h"

DisasterManagementSystem::DisasterManagementSystem() {
    peopleHead = NULL;
    historyTop = NULL;
    isAuthenticated = false;
    currentUser = "";

    // Default administrator account
    users["admin"] = "admin123";
}

DisasterManagementSystem::~DisasterManagementSystem() {
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

void DisasterManagementSystem::pushHistory(string action) {
    History* temp = new History;
    string actor = isAuthenticated ? "[" + currentUser + "] " : "[System] ";
    temp->action = actor + action;
    temp->next = historyTop;
    historyTop = temp;
}

int DisasterManagementSystem::findLocation(string name) {
    for (int i = 0; i < (int)locations.size(); i++) {
        if (locations[i] == name)
            return i;
    }
    return -1;
}

int DisasterManagementSystem::getOrAddLocation(string name) {
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

int DisasterManagementSystem::priorityNumber(string priority) {
    if (priority == "High" || priority == "high" ||
        priority == "HIGH")
        return 3;

    if (priority == "Medium" || priority == "medium" ||
        priority == "MEDIUM")
        return 2;

    return 1;
}
