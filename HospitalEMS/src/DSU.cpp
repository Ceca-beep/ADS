#include "DSU.h"

DSU::DSU() : components(0) {}

void DSU::makeSet(int id) {
    if (parent.find(id) == parent.end()) {
        parent[id] = id;
        rank[id] = 0;
        components++;
    }
}

int DSU::find(int id) {
    if (parent.find(id) == parent.end()) return -1;
    if (parent[id] != id) parent[id] = find(parent[id]);
    return parent[id];
}

bool DSU::unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA == -1 || rootB == -1 || rootA == rootB) return false;

    if (rank[rootA] < rank[rootB]) {
        parent[rootA] = rootB;
        if (wardNames.count(rootA)) wardNames[rootB] = wardNames[rootA];
    } else if (rank[rootA] > rank[rootB]) {
        parent[rootB] = rootA;
    } else {
        parent[rootB] = rootA;
        rank[rootA]++;
    }
    components--;
    return true;
}

bool DSU::connected(int a, int b) {
    int rA = find(a), rB = find(b);
    return rA != -1 && rA == rB;
}

void DSU::remove(int id) {
    if (parent.find(id) == parent.end()) return;
    int root = find(id);
    parent.erase(id);
    rank.erase(id);
    if (root == id) {
        wardNames.erase(id);
        components--;
    }
}

void DSU::setWardName(int representativeId, const std::string& name) {
    wardNames[representativeId] = name;
}

std::string DSU::getWardName(int id) {
    int root = find(id);
    if (root < 0) return "Unassigned";
    auto it = wardNames.find(root);
    if (it != wardNames.end()) return it->second;
    return "Ward-" + std::to_string(root);
}

std::unordered_set<int> DSU::getWardMembers(int id) {
    int root = find(id);
    std::unordered_set<int> members;
    for (auto& [key, _] : parent)
        if (find(key) == root) members.insert(key);
    return members;
}

std::unordered_map<int, std::unordered_set<int>> DSU::getAllWards() {
    std::unordered_map<int, std::unordered_set<int>> wards;
    for (auto& [id, _] : parent)
        wards[find(id)].insert(id);
    return wards;
}

bool DSU::contains(int id) const { return parent.count(id) > 0; }
int DSU::componentCount() const { return components; }
