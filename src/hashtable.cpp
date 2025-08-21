#include "hashtable.h"

HashTable::HashTable(size_t bucketCount) : buckets_(bucketCount ? bucketCount : 1) {}

// TODO: Implement separate chaining insert/update
bool HashTable::insert(const std::string& key, const ItemHandle& value) {
    size_t idx = indexFor(key);
    ItemHandle* second = find(key);
    if(second == nullptr)
    {
        buckets_[idx].insert(buckets_[idx].end(), Node(key, value));
        return true;
    }
    else
    {
        *second = value;
        return false;
    }
}

// TODO: Implement find (non-const)
ItemHandle* HashTable::find(const std::string& key) {
    size_t idx = indexFor(key);
    std::list<Node>::iterator it = buckets_[idx].begin();
    for (; it != buckets_[idx].end(); it++)
    {
        if (it->first == key)
        {
            return &(it->second);
        }
    }    
    return nullptr; // STUB
}

// TODO: Implement find (const)
const ItemHandle* HashTable::find(const std::string& key) const {
    return const_cast<HashTable*>(this)->find(key);
}

// TODO: Implement erase
bool HashTable::erase(const std::string& key) {
    size_t idx = indexFor(key);
    std::list<Node>::iterator it = buckets_[idx].begin();
    for (; it != buckets_[idx].end(); it++)
    {
        if (it->first == key)
        {
            buckets_[idx].erase(it);
            return true;
        }
    }    
    return false; // STUB
}
