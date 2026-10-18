# Disaster Management System
### Emergency Response Management System

A C++-based Disaster Management System developed as a Project-Based Learning (PBL) project. It helps manage disaster records, affected people, rescue teams, emergency resources, requests, routes, and action history using Object-Oriented Programming and Data Structures.

## 📌 Project Details

- **Project Title:** Disaster Management System
- **Team Name:** ShieldNova
- **Team ID:** DSCPP-III-2026-T058
- **Domain:** Data Structures and C++
- **Semester:** 3rd Semester
- **Mentor:** Mr. Navneet Rajpoot

## 👥 Team Members

| Name | Role |
|---|---|
| Avika Mittal | Data Structures and Classes |
| Avni Khandelwal | Core Modules |
| Aryan Gautam | Main System Controller |
| Gaurav Singh Negi | Program Entry Point |

## 🎯 Objectives

- Maintain disaster and affected-person records.
- Register and manage rescue teams.
- Track available resources and their allocation.
- Prioritize emergency requests based on urgency.
- Find direct routes between locations.
- Maintain an action history.
- Save affected-person records to a text file.

## ⚙️ Features

### 1. Disaster Management
Register, update, and view disaster records.

### 2. Affected People Management
Add affected-person details, search records by name, and update status.

### 3. Rescue Team Management
Register and display rescue teams.

### 4. Resource Management
Add resources, view inventory, and allocate available quantities.

### 5. Emergency Request Management
Sort emergency requests according to urgency:
- **High:** Priority 3
- **Medium:** Priority 2
- **Low:** Priority 1

Requests with higher priority are processed first using vector sorting.

### 6. Route Navigation
Add routes between locations and check whether a direct route exists. The system displays the distance when a matching route is found.

### 7. Audit History
Record actions and display the latest logged actions first.

### 8. File Handling
Save affected-person records in a text file named `disaster_system_data.txt`.

## 🧠 Concepts Used

- Object-Oriented Programming (OOP)
- Classes and Objects
- Encapsulation
- Structures
- Vectors
- Searching
- Sorting
- Input Validation
- File Handling

## 🛠️ Technology Stack

- **Language:** C++
- **Libraries:** iostream, vector, string, fstream, algorithm
- **Tools:** VS Code / Code::Blocks
- **Version Control:** Git and GitHub

## ▶️ How to Run

1. Clone or download this repository.
2. Open the project folder in your C++ IDE.
3. Compile the C++ source file using a C++ compiler.
4. Run the generated executable.
5. Follow the menu displayed in the console.

### Compile using g++

```bash
g++ main.cpp -o disaster_management
```

### Run

```bash
./disaster_management
```

On Windows, run:

```bash
disaster_management.exe
```

*Replace `main.cpp` with the actual source filename if it is different.*

## 💾 Data Storage

The current implementation saves affected-person records to a text file. Loading previously saved data and persistent storage for all modules are not yet implemented.

## 🚧 Future Enhancements

- Implement Dijkstra's algorithm for shortest-path routing.
- Improve emergency request management.
- Add file loading and complete data persistence.
- Enhance testing and error handling.
- Expand route navigation and resource management.

## 📚 References

- [C++ Reference](https://en.cppreference.com/)
- [cplusplus.com](https://cplusplus.com/)

---

**Project:** Disaster Management System  
**Team:** ShieldNova  
**Team ID:** DSCPP-III-2026-T058
