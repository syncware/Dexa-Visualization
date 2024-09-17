#pragma once

#ifndef HASHTABLE_H
#define HASHTABLE_H
#endif

#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int capacity;
    int size;

    int hash(int key) {
        return key % capacity;
    }

public:
    HashTable(int cap) : capacity(cap), size(0) {
        table.resize(capacity, -1);  // -1 indicates empty
    }

    bool insert(int key) {
        if (size == capacity) return false;  // Hash table full

        int idx = hash(key);
        while (table[idx] != -1) {
            idx = (idx + 1) % capacity;  // Linear probing
        }
        table[idx] = key;
        size++;
        return true;
    }

    bool search(int key) {
        int idx = hash(key);
        int originalIdx = idx;

        while (table[idx] != -1) {
            if (table[idx] == key) return true;
            idx = (idx + 1) % capacity;

            if (idx == originalIdx) break;  // Full circle
        }
        return false;
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1)
                std::cout << "Empty ";
            else
                std::cout << table[i] << " ";
        }
        std::cout << std::endl;
    }
};