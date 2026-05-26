# Hospital Emergency Management System

A console-based C++ application simulating a hospital emergency department, built as a project for the **Advanced Data Structures** course at West University of Timișoara.

Three data structures are implemented from scratch with no external dependencies.

---

## Data Structures

| Structure | Role | Complexity |
|-----------|------|------------|
| **AVL Tree** | Patient record storage, indexed by ID | O(log n) insert / search / delete |
| **Binomial Heap** | Triage priority queue, ordered by severity | O(log n) insert / extract-min |
| **DSU (Union-Find)** | Ward grouping and merging | O(α(n)) ≈ O(1) |

---

## Features

```
[1]  Admit patient               [2]  Search patient by ID
[3]  Treat next (highest sev.)   [4]  View triage queue
[5]  All patients (AVL inorder)  [6]  Discharge patient
[7]  Update severity             [8]  Assign ward name
[9]  Merge two wards             [10] Check same ward
[11] View all wards              [12] System statistics
```

---

## Project Structure

```
HospitalEMS/
├── include/
│   ├── AVLTree.h
│   ├── BinomialHeap.h
│   ├── DSU.h
│   ├── Patient.h
│   ├── HospitalSystem.h
│   └── ConsoleUI.h
├── src/
│   ├── AVLTree.cpp
│   ├── BinomialHeap.cpp
│   ├── DSU.cpp
│   ├── Patient.cpp
│   ├── HospitalSystem.cpp
│   ├── ConsoleUI.cpp
│   └── main.cpp
└── CMakeLists.txt
```

---

## How to Run

### CLion
1. Open the `HospitalEMS` folder in CLion (File → Open)
2. CLion detects `CMakeLists.txt` automatically
3. Press **Shift+F10** to build and run

### Command line (g++)
```bash
g++ -std=c++17 -I include src/*.cpp -o hospital
./hospital
```

**Requirements:** C++17 or later — no external libraries needed.

---

## Demo

Six patients are loaded automatically on startup with pre-configured ward assignments, so all features can be demonstrated immediately.