#include <iostream>
#include "hashtable.h"

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
using namespace cop4530;

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) {
  curr_size = 0;
  theLists.resize(prime_below(size));
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
  makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const {
  auto & whichList = theLists[myhash(k)];
  // return find(begin(whichList), end(whichList), k != end(whichList));

  for (auto itr = whichList.begin(); itr != whichList.end(); ++itr) { 
    if(itr->first == k) {
      return true;
    }
  }

  return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
  auto & whichList = theLists[myhash(kv.first)];
  return find(begin(whichList), end(whichList), kv) != end(whichList);
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {
  auto & whichList = theLists[myhash(kv)];

  if (find(begin(whichList), end(whichList), kv) != end(whichList)) {
    return false;
  }

  whichList.push_back(kv);

  if (++curr_size > theLists.size()) {
    rehash();
  }

  return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv) {
  auto & whichList = theLists[myhash(kv.first)];

  if (find(begin(whichList), end(whichList), kv) != end(whichList)) {
    return false;
  }

  whichList.push_back(std::move(kv));

  if (++curr_size > theLists.size()) {
    rehash();
  }

  return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {
  auto & whichList = theLists[myhash(k)];

  for (auto itr = whichList.begin(); itr != whichList.end(); ++itr) {
    if (itr->first == k) {
      whichList.erase(itr);
      --curr_size;
      return true;
    }
  }

  return false;
}

template <typename K, typename V>
void HashTable<K, V>::clear() {
  makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
  std::ifstream instream;

  K key;
  V value;

  instream.clear();
  instream.open(filename);

  if (!instream) {
    return false;
  }

  while (!instream.eof()) {
    instream >> key >> value;
    insert(std::make_pair(key, value));
  }

  instream.close();
  return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const {
  if (curr_size != 0) {
    for (auto & whichList : theLists) {
      for (auto itr = whichList.begin(); itr != whichList.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
      }
    }
  }
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {
  return curr_size;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const {
  std::ofstream outstream;

  outstream.open(filename);

  if (!outstream) {
    return false;
  }

  for (int i = 0; i < theLists.size(); i++) {
    auto & whichList = theLists[i];
    
    for (auto itr = whichList.begin(); itr != whichList.end(); ++itr) {
      outstream << itr->first << " " << itr->second << std::endl;
    }
  }

  outstream.close();
  return true;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
  for (auto & thisList : theLists) {
    thisList.clear();
  } 
}

template <typename K, typename V>
void HashTable<K, V>::rehash() {
  auto oldLists = theLists;

  theLists.resize(prime_below(2 * theLists.size()));

  makeEmpty();

  for (auto & thisList : oldLists) {
    for (auto & kv : thisList) {
      insert(std::move(kv));
    }
  }
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const {
  static std::hash<K> _hashTable;
  return _hashTable(k) % theLists.size();
}

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

