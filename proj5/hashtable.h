#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 101;
 
namespace cop4530 {
    template <typename K, typename V>
        class HashTable {
            public:
                HashTable(size_t size = 101); // Constructor
                ~HashTable(); // Destructor
                bool contains(const K & k) const; // Checks if key contained hash table
                bool match(const std::pair<K, V> &kv) const; // Check if key-value pair contained in hash table
                bool insert(const std::pair<K, V> & kv); // Add key-value pair to hash table
                bool insert(std::pair<K, V> && kv); // Move version of insert(..)
                bool remove(const K & k); // Deletes key k from hash table
                void clear(); // Deletes all elements in hash table
                bool load(const char *filename); // Load content of file into hash table
                void dump() const; // Display all entries in hash table
                size_t size() const; // Return number of elements in hash table
                bool write_to_file(const char *filename) const; // Write elements in hash table to file

            private:
                std::vector<std::list<std::pair<K, V> > > theLists;
                int curr_size;

                void makeEmpty(); // Delete all elements in hash table
                void rehash(); // Rehash function
                size_t myhash(const K &k) const; // Return index of vector entry
                unsigned long prime_below(unsigned long); 
                void setPrimes(std::vector<unsigned long> &);
        };

    #include "hashtable.hpp"

} // end of namespace cop4530

#endif
