#pragma once
#include "HospitalSystem.h"

class ConsoleUI {
public:
    ConsoleUI();
    void run();

private:
    HospitalSystem system;

    void printBanner() const;
    void printMenu() const;
    void seedDemoData();

    void admitPatient();
    void searchPatient();
    void treatNext();
    void viewTriageQueue();
    void viewAllPatients();
    void dischargePatient();
    void updateSeverity();
    void assignWard();
    void mergeWards();
    void checkSameWard();
    void viewWards();
    void viewStats();

    std::string severityBar(int severity) const;
    std::string formatPatient(const Patient& p);
    int readInt(const std::string& prompt, int min, int max);
    void printLine(const std::string& color, const std::string& msg) const;
};
