#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <functional>
#include <iostream>
#include <vector>

template<class Key, class Hash=std::hash<Key>>
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
    size_type count;

    // The pointer to the hash table
    std::vector<std::pair<bool, Key>> table;

    // Constants
    const size_type DEFAULT_CELL_SIZE = 11;
    const float DEFAULT_MAX_LOAD_FACTOR = 0.5f;

public:
    HashTable();

    HashTable(const HashTable &other);

    ~HashTable();

    HashTable &operator=(const HashTable &other);

    HashTable(size_type cells);

    bool is_empty() const;

    size_t size() const;

    size_t table_size() const;

    void make_empty();

    bool insert(const value_type &value);

    size_t remove(const key_type &key);

    bool contains(const key_type &key);

    size_t position(const key_type &key) const;

    void print_table(std::ostream &os = std::cout) const;

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};

//-------------------------------------------------------
// Name: HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: makes an empty table with 11 cells.
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable() {
    this->number_of_cells = DEFAULT_CELL_SIZE;
    this->maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    this->count = 0;
    table.reserve(DEFAULT_CELL_SIZE);
    for (size_type i = 0; i < number_of_cells; i++) {
        table.emplace_back();
    }
    for (size_type i = 0; i < number_of_cells; ++i) {
        auto &slot = table[i];
        slot.first = false;
    }
}

//-------------------------------------------------------
// Name: HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: constructs a copy of the given table.
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(const HashTable &other) {
    // Clear the content

    number_of_cells = other.number_of_cells;

    // No need to import as the maximum load factor is fixed to 0.5f
    maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;

    // Create a new table
    table.reserve(number_of_cells);

    // copy values
    for (size_type i = 0; i < number_of_cells; i++) {
        auto &slot = table[i];
        if (slot.first) {
            this->table[i] = other.table[i];
        }
    }
}

//-------------------------------------------------------
// Equal operator
// PreCondition:
// PostCondition: assigns a copy of the given table.
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash> &HashTable<Key, Hash>::operator=(const HashTable &other) { // clear , new, copy
    // Clear the content

    number_of_cells = other.number_of_cells;

    // No need to import as the maximum load factor is fixed to 0.5f
    maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;

    // Create a new table
    table.reserve(number_of_cells);

    // copy values
    for (size_type i = 0; i < number_of_cells; i++) {
        auto &slot = table[i];
        if (slot.first) {
            this->table[i] = other.table[i];
        }
    }

    return *this;
}

//-------------------------------------------------------
// Name: ~HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: destructs this table.
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::~HashTable() {
    // Nothing to do here
}

//-------------------------------------------------------
// Name: HashTable
// PreCondition:  the radius is greater than zero
// PostCondition: makes an empty table with the specified number of
// cells
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(size_type cells) {
    this->number_of_cells = cells;
    this->maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    this->count = 0;
    table.reserve(number_of_cells);
    for (size_type i = 0; i < number_of_cells; i++) {
        table.emplace_back();
    }
    for (size_type i = 0; i < number_of_cells; ++i) {
        auto &slot = table[i];
        slot.first = false;
    }
}

//-------------------------------------------------------
// Name: is_empty
// PreCondition:  the radius is greater than zero
// PostCondition: returns true if the table is empty.
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::is_empty() const {
    for (size_type i = 0; i < number_of_cells; i++) {
        auto &slot = table[i];
        if (slot.first) {
            return false;
        }
    }

    return true;

}

//-------------------------------------------------------
// Name: size
// PreCondition:  the radius is greater than zero
// PostCondition: returns the number of active values in the table.
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::size() const {
    return count;
}

//-------------------------------------------------------
// Name: table_size
// PreCondition:  the radius is greater than zero
// PostCondition: return the number of cells in the table.
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::table_size() const {
    return number_of_cells;
}

//-------------------------------------------------------
// Name: make_empty
// PreCondition:  the radius is greater than zero
// PostCondition: remove all values from the table. Do not change the
// number of cells.
//---------------------------------------------------------
template<class Key, class Hash>
void HashTable<Key, Hash>::make_empty() {
    for (size_type i = 0; i < number_of_cells; ++i) {
        auto &slot = table[i];
        slot.first = false;
//        slot.second = Key();
    }
}

//-------------------------------------------------------
// Name: insert
// PreCondition:  the radius is greater than zero
// PostCondition: insert the given value reference into the table,
// rehashing if the maximum load factor is exceeded,
// return true if insert was successful (false if item
// already exists).
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::insert(const value_type &value) {
    // get the hash value
    size_type hash_value = Hash{}(value);
    size_type index = hash_value % number_of_cells;

    // Check whether the values is available
    if (this->contains(value)) {
        return false;
    }

    // if not exceeding the load factor, insert the values
    if (((float) (count + 1) / number_of_cells) >= maximum_load_factor) {
        return false;
    }

    for (size_type i = 0; i < number_of_cells; i++) {
        auto &slot = table[index];

        // If the slot has no value we can insert  the value
        if (!slot.first) {
            slot.first = true;
            slot.second = value;
            count++;
            return true;
        } else {
            hash_value++;
            index = (hash_value) % number_of_cells;
        }

    }

    return false;
}

//-------------------------------------------------------
// Name: remove
// PreCondition:  the radius is greater than zero
// PostCondition: remove the specified value from the table, return
// number of elements removed (0 or 1). Use lazy
// deletion.
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::remove(const key_type &key) {
    if (this->contains(key)) {
        size_type index = this->position(key);
        auto &slot = table[index];
        slot.first = false;
        count--;
        return 1;
    } else {
        return 0;
    }

}

//-------------------------------------------------------
// Name: contains
// PreCondition:  the radius is greater than zero
// PostCondition: returns Boolean true if the specified value is in the
// table
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::contains(const key_type &key) {
    size_type hash_value = Hash{}(key);
    size_type index = hash_value % number_of_cells;

    for (size_type i = 0; i < number_of_cells; i++) {
        auto &slot = table[index];

        // If the slot has no value
        if (!slot.first) {
            return false;
        }


        if (slot.second == key) {
            return true;
        } else {
            hash_value++;
            index = (hash_value) % number_of_cells;
        }
    }

    return false;
}

//-------------------------------------------------------
// Name: position
// PreCondition:  the radius is greater than zero
// PostCondition: return the index of the cell that would contain the
// specified value. This method handles collision
// resolution.
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::position(const key_type &key) const {
    size_type hash_value = Hash{}(key);
    size_type index = hash_value % number_of_cells;

    for (size_type i = 0; i < number_of_cells; i++) {
        auto &slot = table[index];

        if (!slot.first) {
            return number_of_cells + 1;
        }

        if (slot.second == key) {
            return index;
        } else {
            hash_value++;
            index = (hash_value) % number_of_cells;
        }
    }

    // returning an invalid position
    return number_of_cells + 1;
}

//-------------------------------------------------------
// Name: print_table
// PreCondition:  the radius is greater than zero
// PostCondition: pretty print the table. Required to exist and
//produce reasonable output, the empty table should
//print “<empty>\n”.
//---------------------------------------------------------
template<class Key, class Hash>
void HashTable<Key, Hash>::print_table(std::ostream &os) const {
    if (is_empty()) {
        std::cout << "<empty>\n";
        return;
    }
    for (size_type i = 0; i < number_of_cells; i++) {
        auto &slot = table[i];
        os << i << ": ";
        if (slot.first) {
            os << slot.second;
        }
        os << std::endl;
    }
}

#endif  // HASHTABLE_OPEN_ADDRESSING_H
