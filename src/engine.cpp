#include "engine.h"
#include "provided.h"
#include <iostream>

Engine::Engine(size_t hashBuckets) : byName_(hashBuckets) {}

void Engine::loadCSV(const std::string& path) {
    using provided::now; using provided::ms_between;
    auto t0 = now();
    std::vector<ItemHandle> items;
    size_t skipped = 0;
    if (!provided::readCSV(path, items, skipped)) {
        std::cout << "ERROR: cannot open " << path << "\n";
        return;
    }
    size_t loaded = 0;
    for (const auto& h : items) {
        if (add(h)) ++loaded; // With stubs, this will likely be 0
    }
    auto t1 = now();
    std::cout << "LOADED " << loaded << " (skipped " << skipped << ") in "
              << ms_between(t0, t1) << " ms\n";
}

bool Engine::add(const ItemHandle& item) {
    // TODO: Implement: check BST duplicate, insert into hash and BST atomically
    if (ordered_.contains(item)) {return false; }

    ordered_.insert(item);
    byName_.insert(item.name(), item);

    return false; // STUB forces tests to fail until implemented
}

bool Engine::eraseByName(const std::string& name) {
    // TODO: Implement: find by name in hash, remove from both structures
    ItemHandle value = *findByName(name);
    return byName_.erase(name) && ordered_.erase(value); // STUB
}

const ItemHandle* Engine::findByName(const std::string& name) const {
    return byName_.find(name);
}

void Engine::listInOrder(std::vector<ItemHandle>& out) const {
    ordered_.inorder(out);
}

void Engine::sortSnapshot(std::vector<ItemHandle>& out, SortAlgo algo, bool ascending) const {
    ordered_.inorder(out);
    sortItems(out, algo, ascending);
}
