#include "Patient.h"

Patient::Patient(int id, const std::string& name, int severity)
    : id(id), name(name), severity(severity), wardId(-1) {
    admissionTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

bool Patient::operator<(const Patient& other) const {
    if (severity != other.severity) return severity > other.severity;
    return admissionTime < other.admissionTime;
}

bool Patient::operator>(const Patient& other) const { return other < *this; }

int Patient::getId() const { return id; }
const std::string& Patient::getName() const { return name; }
int Patient::getSeverity() const { return severity; }
int Patient::getWardId() const { return wardId; }
long long Patient::getAdmissionTime() const { return admissionTime; }

void Patient::setName(const std::string& name) { this->name = name; }
void Patient::setSeverity(int severity) { this->severity = severity; }
void Patient::setWardId(int wardId) { this->wardId = wardId; }
