#include "ConsoleUI.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <climits>

static const std::string RESET  = "\033[0m";
static const std::string RED    = "\033[31m";
static const std::string GREEN  = "\033[32m";
static const std::string YELLOW = "\033[33m";
static const std::string CYAN   = "\033[36m";
static const std::string BOLD   = "\033[1m";
static const std::string DIM    = "\033[2m";

ConsoleUI::ConsoleUI() {}

void ConsoleUI::run() {
    printBanner();
    seedDemoData();
    bool running = true;
    while (running) {
        printMenu();
        std::string choice;
        std::getline(std::cin, choice);
        for (auto& c : choice) if (c == '[' || c == ']') c = ' ';
        choice.erase(0, choice.find_first_not_of(" \t"));
        choice.erase(choice.find_last_not_of(" \t") + 1);
        std::cout << "\n";

        if      (choice == "1")  admitPatient();
        else if (choice == "2")  searchPatient();
        else if (choice == "3")  treatNext();
        else if (choice == "4")  viewTriageQueue();
        else if (choice == "5")  viewAllPatients();
        else if (choice == "6")  dischargePatient();
        else if (choice == "7")  updateSeverity();
        else if (choice == "8")  assignWard();
        else if (choice == "9")  mergeWards();
        else if (choice == "10") checkSameWard();
        else if (choice == "11") viewWards();
        else if (choice == "12") viewStats();
        else if (choice == "0")  { running = false; printLine(GREEN, "System shutdown. Goodbye."); }
        else                      printLine(RED, "Invalid option. Try again.");
    }
}

void ConsoleUI::printBanner() const {
    std::cout << BOLD << CYAN;
    std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
    std::cout <<   "║        HOSPITAL EMERGENCY MANAGEMENT SYSTEM          ║\n";
    std::cout <<   "║   AVL Tree  •  Binomial Heap  •  Union-Find (DSU)    ║\n";
    std::cout <<   "╚══════════════════════════════════════════════════════╝\n";
    std::cout << RESET << "\n";
}

void ConsoleUI::printMenu() const {
    std::cout << BOLD + "─── MAIN MENU ───────────────────────────────────────\n" + RESET;
    std::cout << CYAN + "  PATIENT MANAGEMENT\n" + RESET;
    std::cout << "   [1] Admit patient          [2] Search patient by ID\n";
    std::cout << "   [6] Discharge patient      [7] Update severity\n\n";
    std::cout << CYAN + "  TRIAGE QUEUE  (Binomial Heap)\n" + RESET;
    std::cout << "   [3] Treat next patient     [4] View triage queue\n\n";
    std::cout << CYAN + "  WARD MANAGEMENT  (DSU)\n" + RESET;
    std::cout << "   [8] Assign patient to ward [9] Merge two wards\n";
    std::cout << "   [10] Check same ward        [11] View all wards\n\n";
    std::cout << CYAN + "  SYSTEM\n" + RESET;
    std::cout << "   [5] All patients (AVL)     [12] System statistics\n";
    std::cout << "   [0] Exit\n";
    std::cout << DIM + "─────────────────────────────────────────────────────\n" + RESET;
    std::cout << BOLD + "Choose > " + RESET;
}

void ConsoleUI::admitPatient() {
    std::cout << "Patient name: ";
    std::string name;
    std::getline(std::cin, name);
    if (name.empty()) { printLine(RED, "Name cannot be empty."); return; }
    int severity = readInt("Severity (1=low, 10=critical): ", 1, 10);
    Patient p = system.admitPatient(name, severity);
    printLine(GREEN, "Admitted: " + formatPatient(p));
}

void ConsoleUI::searchPatient() {
    int id = readInt("Patient ID: ", 1, INT_MAX);
    Patient* p = system.searchPatient(id);
    if (!p) printLine(RED, "Patient ID " + std::to_string(id) + " not found.");
    else    printLine(GREEN, "Found: " + formatPatient(*p));
}

void ConsoleUI::treatNext() {
    Patient* next = system.peekNextPatient();
    if (!next) { printLine(YELLOW, "Triage queue is empty."); return; }
    std::cout << YELLOW << "Next up: " << formatPatient(*next) << RESET << "\n";
    std::cout << "Confirm treatment? (y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);
    if (confirm == "y" || confirm == "Y") {
        system.treatNextPatient();
        printLine(GREEN, "Patient treated and discharged.");
    } else {
        printLine(DIM, "Cancelled.");
    }
}

void ConsoleUI::viewTriageQueue() {
    auto queue = system.getTriageQueue();
    if (queue.empty()) { printLine(YELLOW, "Triage queue is empty."); return; }
    std::cout << BOLD << CYAN << "\n  TRIAGE QUEUE (highest severity first)\n" << RESET;
    std::cout << DIM << "  #   ID    Name                  Severity  Ward\n";
    std::cout <<        "  ──  ────  ────────────────────  ────────  ────────────\n" << RESET;
    int rank = 1;
    for (const auto& p : queue) {
        std::string ward = system.getWardName(p.getId());
        std::cout << "  " << std::left;
        printf("  %-3d %-5d %-22s %s  %s\n",
            rank++, p.getId(), p.getName().c_str(),
            severityBar(p.getSeverity()).c_str(), ward.c_str());
    }
    std::cout << "\n";
}

void ConsoleUI::viewAllPatients() {
    auto patients = system.getAllPatientsSortedById();
    if (patients.empty()) { printLine(YELLOW, "No patients in the system."); return; }
    std::cout << BOLD << CYAN << "\n  ALL PATIENTS (sorted by ID — AVL inorder)\n" << RESET;
    std::cout << DIM << "  ID    Name                  Severity  Ward\n";
    std::cout <<        "  ────  ────────────────────  ────────  ────────────\n" << RESET;
    for (const auto* p : patients) {
        printf("  %-5d %-22s %s  %s\n",
            p->getId(), p->getName().c_str(),
            severityBar(p->getSeverity()).c_str(),
            system.getWardName(p->getId()).c_str());
    }
    printf("%s", DIM.c_str());
    printf("  %d patient(s) | AVL height: %d\n\n", system.getTotalPatients(), system.getAVLHeight());
    std::cout << RESET;
}

void ConsoleUI::dischargePatient() {
    int id = readInt("Patient ID to discharge: ", 1, INT_MAX);
    if (system.dischargePatient(id)) printLine(GREEN, "Patient " + std::to_string(id) + " discharged.");
    else                              printLine(RED, "Patient ID " + std::to_string(id) + " not found.");
}

void ConsoleUI::updateSeverity() {
    int id = readInt("Patient ID: ", 1, INT_MAX);
    Patient* p = system.searchPatient(id);
    if (!p) { printLine(RED, "Patient not found."); return; }
    std::cout << "Current severity: " << p->getSeverity() << "\n";
    int newSev = readInt("New severity (1-10): ", 1, 10);
    if (system.updateSeverity(id, newSev)) printLine(GREEN, "Severity updated.");
    else                                    printLine(RED, "Update failed.");
}

void ConsoleUI::assignWard() {
    int id = readInt("Patient ID: ", 1, INT_MAX);
    if (!system.searchPatient(id)) { printLine(RED, "Patient not found."); return; }
    std::cout << "Ward name: ";
    std::string wardName;
    std::getline(std::cin, wardName);
    std::string result = system.assignWard(id, wardName);
    if (!result.empty()) printLine(GREEN, "Patient " + std::to_string(id) + " assigned to ward '" + wardName + "'.");
    else                  printLine(RED, "Assignment failed.");
}

void ConsoleUI::mergeWards() {
    std::cout << "Merge the wards of two patients (DSU union).\n";
    int idA = readInt("First patient ID: ", 1, INT_MAX);
    int idB = readInt("Second patient ID: ", 1, INT_MAX);
    if (system.mergeWards(idA, idB))
        printLine(GREEN, "Wards of patients " + std::to_string(idA) + " and " + std::to_string(idB) + " merged.");
    else
        printLine(YELLOW, "Could not merge — patients not found or already in the same ward.");
}

void ConsoleUI::checkSameWard() {
    int idA = readInt("First patient ID: ", 1, INT_MAX);
    int idB = readInt("Second patient ID: ", 1, INT_MAX);
    if (system.areSameWard(idA, idB))
        printLine(GREEN, "Patients " + std::to_string(idA) + " and " + std::to_string(idB) +
                  " are in the same ward: " + system.getWardName(idA));
    else
        printLine(YELLOW, "Patients " + std::to_string(idA) + " and " + std::to_string(idB) + " are in different wards.");
}

void ConsoleUI::viewWards() {
    auto wards = system.getAllWards();
    if (wards.empty()) { printLine(YELLOW, "No patients in the system."); return; }
    std::cout << BOLD << CYAN << "\n  WARD ASSIGNMENTS (DSU components)\n" << RESET;
    for (auto& [rep, members] : wards) {
        std::string wardName = system.getWardName(rep);
        std::vector<int> sorted(members.begin(), members.end());
        std::sort(sorted.begin(), sorted.end());
        std::string ids = "[";
        for (int i = 0; i < (int)sorted.size(); i++) {
            ids += std::to_string(sorted[i]);
            if (i + 1 < (int)sorted.size()) ids += ", ";
        }
        ids += "]";
        printf("  %-20s → patients: %s\n", wardName.c_str(), ids.c_str());
    }
    std::cout << "\n";
}

void ConsoleUI::viewStats() {
    std::cout << BOLD << CYAN << "\n  SYSTEM STATISTICS\n" << RESET;
    std::cout << "  Total patients    : " << system.getTotalPatients() << "\n";
    std::cout << "  In triage queue   : " << system.getTriageCount() << "\n";
    std::cout << "  AVL tree height   : " << system.getAVLHeight() << "\n";
    std::cout << "  Active wards      : " << system.getWardCount() << "\n\n";
}

void ConsoleUI::seedDemoData() {
    system.admitPatient("Alice Martin",  8);
    system.admitPatient("Bob Chen",      3);
    system.admitPatient("Clara Ionescu", 10);
    system.admitPatient("David Popescu", 6);
    system.admitPatient("Elena Rusu",    2);
    system.admitPatient("Florin Dima",   9);
    system.assignWard(1, "ICU");
    system.assignWard(2, "General");
    system.mergeWards(3, 6);
    system.assignWard(3, "ICU");
    system.mergeWards(1, 3);
    printLine(DIM, "Demo data loaded: 6 patients, wards pre-configured.\n");
}

std::string ConsoleUI::severityBar(int severity) const {
    std::string color = severity >= 8 ? RED : severity >= 5 ? YELLOW : GREEN;
    char buf[32];
    snprintf(buf, sizeof(buf), "[%2d/10]", severity);
    return color + std::string(buf) + RESET;
}

std::string ConsoleUI::formatPatient(const Patient& p) {
    char buf[256];
    snprintf(buf, sizeof(buf), "ID=%-3d  %-22s  sev=%s  ward=%s",
        p.getId(), p.getName().c_str(),
        severityBar(p.getSeverity()).c_str(),
        system.getWardName(p.getId()).c_str());
    return std::string(buf);
}

void ConsoleUI::printLine(const std::string& color, const std::string& msg) const {
    std::cout << color << msg << RESET << "\n\n";
}

int ConsoleUI::readInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        try {
            int val = std::stoi(line);
            if (val >= min && val <= max) return val;
            std::cout << RED << "Enter a number between " << min << " and " << max << ".\n" << RESET;
        } catch (...) {
            std::cout << RED << "Invalid number.\n" << RESET;
        }
    }
}
