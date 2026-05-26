#pragma once
#include <string>
#include <chrono>

class Patient {
public:
    Patient(int id, const std::string& name, int severity);

    bool operator<(const Patient& other) const;
    bool operator>(const Patient& other) const;

    int getId() const;
    const std::string& getName() const;
    int getSeverity() const;
    int getWardId() const;
    long long getAdmissionTime() const;

    void setName(const std::string& name);
    void setSeverity(int severity);
    void setWardId(int wardId);

private:
    int id;
    std::string name;
    int severity;
    int wardId;
    long long admissionTime;
};
