#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>

class DSU {
public:
    DSU();

    void makeSet(int id);
    int find(int id);
    bool unite(int a, int b);
    bool connected(int a, int b);
    void remove(int id);
    void setWardName(int representativeId, const std::string& name);
    std::string getWardName(int id);
    std::unordered_set<int> getWardMembers(int id);
    std::unordered_map<int, std::unordered_set<int>> getAllWards();
    bool contains(int id) const;
    int componentCount() const;

private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;
    std::unordered_map<int, std::string> wardNames;
    int components;
};
