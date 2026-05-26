#pragma once
#include "AVLTree.h"
#include "BinomialHeap.h"
#include "DSU.h"
#include <vector>
#include <string>

class HospitalSystem {
public:
    HospitalSystem();

    Patient admitPatient(const std::string& name, int severity);
    Patient* searchPatient(int id);
    bool dischargePatient(int id);
    Patient treatNextPatient();
    Patient* peekNextPatient();
    bool updateSeverity(int id, int newSeverity);

    std::string assignWard(int patientId, const std::string& wardName);
    bool mergeWards(int patientIdA, int patientIdB);
    bool areSameWard(int idA, int idB);
    std::string getWardName(int patientId);
    std::unordered_set<int> getWardMembers(int patientId);
    std::unordered_map<int, std::unordered_set<int>> getAllWards();

    std::vector<Patient*> getAllPatientsSortedById();
    std::vector<Patient> getTriageQueue();

    int getTotalPatients() const;
    int getTriageCount() const;
    int getAVLHeight() const;
    int getWardCount() const;

private:
    AVLTree patientRecords;
    BinomialHeap triageQueue;
    DSU wardGroups;
    int nextId;
};
