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
    size_type number_of_cells;
    float maximum_load_factor;

    // The pointer to the hash table
    std::vector<Key> *table;

    // Constants
    const size_type DEFAULT_CELL_SIZE = 11;
    const float DEFAULT_MAX_LOAD_FACTOR = 0.5f;

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

//-------------------------------------------------------
// Name: HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable() {
    this->number_of_cells = DEFAULT_CELL_SIZE;
    this->maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    table = new std::vector<Key>[DEFAULT_CELL_SIZE];

}

//-------------------------------------------------------
// Name: HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(const HashTable &other) {
    // Clear the content
    make_empty();
    delete[] table;

    number_of_cells = other.number_of_cells;
    maximum_load_factor = other.maximum_load_factor;

    // Create a new table
    table = new std::vector<Key>[number_of_cells];

    // copy values
    for (int i = 0; i < number_of_cells; i++) {
        this->table[i] = other.table[i];
    }
}

//-------------------------------------------------------
// Equal operator
// PreCondition:
// PostCondition:
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash> &HashTable<Key, Hash>::operator=(const HashTable &other) { // clear , new, copy
    // Clear the content
    make_empty();
    delete[] table;

    number_of_cells = other.number_of_cells;
    maximum_load_factor = other.maximum_load_factor;

    // Create a new table
    table = new std::vector<Key>[number_of_cells];

    // copy values
    for (int i = 0; i < number_of_cells; i++) {
        this->table[i] = other.table[i];
    }
    return *this;
}

//-------------------------------------------------------
// Name: ~HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::~HashTable() {
    make_empty();
    delete[] table;
}

//-------------------------------------------------------
// Name: HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(size_type cells) {
    this->number_of_cells = cells;
    this->maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    table = new std::vector<Key>[number_of_cells];
}

//-------------------------------------------------------
// Name: is_empty
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::is_empty() const {
    for (size_type i = 0; i < number_of_cells; ++i) {
        if (this->table[i].size() != 0) {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------
// Name: size
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::size() const {
    size_type sum{};
    for (size_type i = 0; i < number_of_cells; ++i) {
        if (this->table[i].size() != 0) {
            sum += table[i].size();
        }
    }

    return sum;
}

//-------------------------------------------------------
// Name: table_size
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::table_size() const {
    return number_of_cells;

}

//-------------------------------------------------------
// Name: make_empty
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
void HashTable<Key, Hash>::make_empty() {
    for (size_type i = 0; i < number_of_cells; i++) {
        this->table[i].clear();
    }
}

//-------------------------------------------------------
// Name: insert
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::insert(const value_type &value) {
    size_type hash_value = Hash{}(value);
    size_type index = hash_value % number_of_cells;
    size_type temp_index = index;

    while (table[index].size() != 0) {
        index = (hash_value + 1) % number_of_cells;
        if (index == temp_index) {
            return false;
        }
    }
    table[index].push_back(value);
    return true;
}

//-------------------------------------------------------
// Name: remove
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::remove(const key_type &key) {

}

//-------------------------------------------------------
// Name: contains
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::contains(const key_type &key) {
    return true;
}

//-------------------------------------------------------
// Name: position
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::position(const key_type &key) const {
    return 0;
}

//-------------------------------------------------------
// Name: print_table
// PreCondition:  the radius is greater than zero
// PostCondition: Returns the calculated area of the circle
//---------------------------------------------------------
template<class Key, class Hash>
void HashTable<Key, Hash>::print_table(std::ostream &os) const {
    if (is_empty()) {
        std::cout << "<empty>\n";
        return;
    }
    for (size_type i = 0; i < number_of_cells; i++) {
        if (table[i].size() != 0) {
            std::cout << i << ":";
            auto content = table[i].begin();
            std::cout << *content;
            std::cout << std::endl;
        }

    }
}

#endif  // HASHTABLE_OPEN_ADDRESSING_H
