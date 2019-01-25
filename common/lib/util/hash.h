// Safe hash function, resistant to hash attacks.
//
// Since it uses std::hash internally, users are advised to continue defining
// custom hashes as std::hash overloads, as usual.
//
// Also provides convenience aliases:
//
// * hash_set       for  std::unordered_set
// * hash_multiset  for  std::unordered_multiset
// * hash_map       for  std::unordered_map
// * hash_multimap  for  std::unordered_multimap


#pragma once

#include <random>
#include <unordered_map>
#include <unordered_set>


template <typename T>
struct SafeHash {
    std::size_t operator()(const T& value) const {
        static std::size_t salt = []() {
            std::random_device rd;
            std::uniform_int_distribution<int> dist;
            return dist(rd);
        }();
        return std::hash<T>()(value) ^ salt;
    }
};


template <typename T>
using hash_set = std::unordered_set<T, SafeHash<T>>;

template <typename T>
using hash_multiset = std::unordered_multiset<T, SafeHash<T>>;

template <typename Key, typename T>
using hash_map = std::unordered_map<Key, T, SafeHash<Key>>;

template <typename Key, typename T>
using hash_multimap = std::unordered_multimap<Key, T, SafeHash<Key>>;
