#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <functional>
#include <iostream>
#include <vector>

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
    // TODO: student implementation
    size_type number_of_cells;

public:
    HashTable();
    HashTable(const HashTable& other);
    ~HashTable();
    HashTable& operator=(const HashTable& other);
    HashTable(size_type cells);

    bool is_empty() const;
    size_t size() const;
    size_t table_size() const;

    void make_empty();
    bool insert(const value_type& value);
    size_t remove(const key_type& key);

    bool contains(const key_type& key);
    size_t position(const key_type& key) const;

    void print_table(std::ostream& os=std::cout) const;

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};

template<class Key, class Hash>
HashTable<Key, Hash>::HashTable() {

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
HashTable<Key, Hash>::~HashTable() {

}

template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(HashTable::size_type cells) {
    this->number_of_cells = cells;
}

template<class Key, class Hash>
bool HashTable<Key, Hash>::is_empty() const {

}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::size() const {
    return 0;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::table_size() const {
    return 0;

}

template<class Key, class Hash>
void HashTable<Key, Hash>::make_empty() {

}

template<class Key, class Hash>
bool HashTable<Key, Hash>::insert(const value_type &value) {
    return true;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::remove(const key_type &key) {

}

template<class Key, class Hash>
bool HashTable<Key, Hash>::contains(const key_type &key) {
    return true;
}

template<class Key, class Hash>
size_t HashTable<Key, Hash>::position(const key_type &key) const {
    return 0;
}

template<class Key, class Hash>
void HashTable<Key, Hash>::print_table(std::ostream &os) const {

}

#endif  // HASHTABLE_OPEN_ADDRESSING_H
