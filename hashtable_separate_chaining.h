#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <stdexcept>
#include <functional>
#include <iostream>

template <class Key, class Hash=std::hash<Key>>
class HashTable {
public:
    // Member Types - do not modify
    using key_type = Key;
    using value_type = Key;
    using hash = Hash;
    using size_type = size_t;
    // you can write your code below this

private:
    size_type number_of_buckets;
    size_type curr_number_of_buckets;
    float maximum_load_factor;
    float curr_load_factor;
    std::list<Key> *table;

    // Instantiation of Object
    std::hash<Key> hash_function;

public:
    HashTable();
    HashTable(const HashTable& other);
    ~HashTable();
    HashTable& operator=(const HashTable& other);
    HashTable(size_type buckets);

    bool is_empty() const;
    size_t size() const;

    void make_empty();
    bool insert(const value_type& value);
    size_t remove(const key_type& key);
    bool contains(const key_type& key);

    size_t bucket_count() const;
    size_t bucket_size(size_t n) const;
    size_t bucket(const key_type& key) const;

    float load_factor() const;
    float max_load_factor() const;
    void max_load_factor(float mlf);
    void rehash(size_type count);

    void print_table(std::ostream& os=std::cout) const;

    // Optional
//     HashTable(HashTable&& other);
//     HashTable& operator=(HashTable&& other);
//     bool insert(value_type&& value);
};

template<class Key, class Hash>
HashTable<Key, Hash>::HashTable() {
    this->number_of_buckets = 11;
    this->curr_number_of_buckets = 0;
    this->maximum_load_factor = 1.0f;
    this->curr_load_factor = 0.0f;
    table = new std::list<Key>[number_of_buckets];
}

template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(const HashTable &other) {
    std::cout << "HashTable()" << std::endl;
    this->number_of_buckets = other.bucket_count();
    this->maximum_load_factor = other.max_load_factor();
    this->curr_load_factor = other.load_factor();
    this->curr_number_of_buckets = other.bucket_size();
}

template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(HashTable::size_type buckets) {
    this->number_of_buckets = buckets;
    this->maximum_load_factor = 1.0f;
    this->curr_load_factor = 0.0f;
    table = new std::list<Key>[number_of_buckets];
}

template<class Key, class Hash>
HashTable<Key, Hash>::~HashTable() {
    delete table;
}

template<class Key, class Hash>
bool HashTable<Key, Hash>::is_empty() const {
    return true;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::size() const {
    return number_of_buckets;
}

template<class Key, class Hash>
void HashTable<Key, Hash>::make_empty() {
    this->curr_load_factor = 0.0f;
    delete this->table;
    this->table = new std::list<Key>[number_of_buckets];
}

template<class Key, class Hash>
bool HashTable<Key, Hash>::insert(const value_type &value) {
//    int index = hashFunction(value);
//    size_t hash_value = Hash{}(value);
//    table[index].push_back(value);
    return true;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::remove(const key_type &key) {
//    int index = hashFunction(key);
//
//    // find the key in (index)th list
//    std::list<int>::iterator i;
//    for (i = table[index].begin(); i != table[index].end(); i++) {
//        if (*i == key) {
//            break;
//        }
//    }
//
//    // if key is found in hash table, remove it
//    if (i != table[index].end()) {
//        table[index].erase(i);
//    }
    return 0;

}

template<class Key, class Hash>
bool HashTable<Key, Hash>::contains(const key_type &key) {
    int index = hashFunction(key);

    // find the key in (index)th list
    std::list<size_t>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key) {
            break;
        }
    }

    if (i != table[index].end()) {
        return true;
    }
    return false;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::bucket_count() const {
    return 0;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::bucket_size(size_t n) const {
    return this->number_of_buckets;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::bucket(const key_type &key) const {
    return 0;
}

template<class Key, class Hash>
float HashTable<Key, Hash>::load_factor() const {
    return curr_load_factor;
}

template<class Key, class Hash>
float HashTable<Key, Hash>::max_load_factor() const {
    return maximum_load_factor;
}

template<class Key, class Hash>
void HashTable<Key, Hash>::max_load_factor(float mlf) {
    maximum_load_factor = mlf;
}

template<class Key, class Hash>
void HashTable<Key, Hash>::rehash(HashTable::size_type count) {

}

template<class Key, class Hash>
void HashTable<Key, Hash>::print_table(std::ostream &os) const {
    for (size_type i = 0; i < number_of_buckets; i++) {
        std::cout << i;
        for (auto x : table[i])
            std::cout << " --> " << x;
        std::cout << std::endl;
    }
}


#endif  // HASHTABLE_SEPARATE_CHAINING_H
