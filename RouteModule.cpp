#include "DisasterManagementSystem.h"

void DisasterManagementSystem::addRoute() {
    string source, destination;
    int distance;

    cout << "Enter starting location: ";
    cin >> ws;
    getline(cin, source);

    cout << "Enter destination location: ";
    getline(cin, destination);

    cout << "Enter distance: ";
    cin >> distance;

    if (distance <= 0) {
        cout << "Distance must be greater than zero.\n";
        return;
    }

    int u = getOrAddLocation(source);
    int v = getOrAddLocation(destination);

    if (u == -1 || v == -1)
        return;

    if (u == v) {
        cout << "Starting location and destination must be different.\n";
        return;
    }

    // Add an undirected, weighted edge to the graph.
    graph[u].push_back(make_pair(v, distance));
    graph[v].push_back(make_pair(u, distance));

    pushHistory("Added route: " + source + " to " + destination);

    cout << "Route added successfully.\n";
}

void DisasterManagementSystem::findDirectRoute() {
    string source, destination;

    cout << "Enter starting location: ";
    cin >> ws;
    getline(cin, source);

    cout << "Enter destination location: ";
    getline(cin, destination);

    int u = findLocation(source);
    int v = findLocation(destination);

    if (u == -1 || v == -1) {
        cout << "One or both locations were not found.\n";
        return;
    }

    for (int i = 0; i < (int)graph[u].size(); i++) {
        if (graph[u][i].first == v) {
            cout << "Direct route exists from " << source
                 << " to " << destination << ".\n";

            cout << "Distance: " << graph[u][i].second << "\n";

            pushHistory("Checked direct route: " +
                        source + " to " + destination);
            return;
        }
    }

    cout << "No direct route exists between these locations.\n";
}

void DisasterManagementSystem::shortestRoute() {
    string source, destination;

    cout << "Enter starting location: ";
    cin >> ws;
    getline(cin, source);

    cout << "Enter destination location: ";
    getline(cin, destination);

    int start = findLocation(source);
    int finish = findLocation(destination);

    if (start == -1 || finish == -1) {
        cout << "One or both locations were not found.\n";
        return;
    }

    int n = (int)locations.size();

    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    // Dijkstra's algorithm finds the shortest total distance.
    for (int count = 0; count < n; count++) {
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] &&
                (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1 ||
            dist[u] == numeric_limits<int>::max())
            break;

        visited[u] = true;

        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i].first;
            int weight = graph[u][i].second;

            if (!visited[v] &&
                dist[u] <= numeric_limits<int>::max() - weight &&
                dist[u] + weight < dist[v]) {

                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    if (dist[finish] == numeric_limits<int>::max()) {
        cout << "No route is available between these locations.\n";
        return;
    }

    vector<int> path;
    int current = finish;

    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }

    cout << "Shortest route: ";

    for (int i = (int)path.size() - 1; i >= 0; i--) {
        cout << locations[path[i]];

        if (i > 0)
            cout << " -> ";
    }

    cout << "\nTotal distance: " << dist[finish] << "\n";

    pushHistory("Found shortest route: " +
                source + " to " + destination);
}

void DisasterManagementSystem::routeModule() {
    int choice;

    do {
        cout << "\n===== MODULE 4: ROUTE NAVIGATION =====\n";
        cout << "1. Add Route\n";
        cout << "2. Find Direct Route and Distance\n";
        cout << "3. Find Shortest Route and Distance\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addRoute(); break;
            case 2: findDirectRoute(); break;
            case 3: shortestRoute(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}
