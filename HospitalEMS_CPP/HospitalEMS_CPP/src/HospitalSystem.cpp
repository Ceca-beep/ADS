#include "HospitalSystem.h"
#include <stdexcept>

HospitalSystem::HospitalSystem() : nextId(1) {}

Patient HospitalSystem::admitPatient(const std::string& name, int severity) {
    if (severity < 1 || severity > 10)
        throw std::invalid_argument("Severity must be between 1 and 10.");
    Patient p(nextId++, name, severity);
    patientRecords.insert(p);
    triageQueue.insert(p);
    wardGroups.makeSet(p.getId());
    return p;
}

Patient* HospitalSystem::searchPatient(int id) { return patientRecords.search(id); }

bool HospitalSystem::dischargePatient(int id) {
    if (!patientRecords.search(id)) return false;
    patientRecords.remove(id);
    wardGroups.remove(id);
    return true;
}

Patient HospitalSystem::treatNextPatient() {
    if (triageQueue.empty()) throw std::runtime_error("Triage queue is empty.");
    Patient p = triageQueue.extractMin();
    patientRecords.remove(p.getId());
    wardGroups.remove(p.getId());
    return p;
}

Patient* HospitalSystem::peekNextPatient() { return triageQueue.peekMin(); }

bool HospitalSystem::updateSeverity(int id, int newSeverity) {
    if (newSeverity < 1 || newSeverity > 10) return false;
    Patient* p = patientRecords.search(id);
    if (!p) return false;
    p->setSeverity(newSeverity);
    triageQueue.insert(*p);
    return true;
}

std::string HospitalSystem::assignWard(int patientId, const std::string& wardName) {
    if (!patientRecords.search(patientId)) return "";
    int root = wardGroups.find(patientId);
    wardGroups.setWardName(root, wardName);
    return wardName;
}

bool HospitalSystem::mergeWards(int a, int b) {
    if (!patientRecords.search(a) || !patientRecords.search(b)) return false;
    return wardGroups.unite(a, b);
}

bool HospitalSystem::areSameWard(int a, int b) { return wardGroups.connected(a, b); }
std::string HospitalSystem::getWardName(int id) { return wardGroups.getWardName(id); }
std::unordered_set<int> HospitalSystem::getWardMembers(int id) { return wardGroups.getWardMembers(id); }
std::unordered_map<int, std::unordered_set<int>> HospitalSystem::getAllWards() { return wardGroups.getAllWards(); }

std::vector<Patient*> HospitalSystem::getAllPatientsSortedById() {
    std::vector<Patient*> result;
    patientRecords.inorder(result);
    return result;
}

std::vector<Patient> HospitalSystem::getTriageQueue() { return triageQueue.toSortedList(); }

int HospitalSystem::getTotalPatients() const { return patientRecords.size(); }
int HospitalSystem::getTriageCount() const { return triageQueue.size(); }
int HospitalSystem::getAVLHeight() const { return patientRecords.height(); }
int HospitalSystem::getWardCount() const { return wardGroups.componentCount(); }
