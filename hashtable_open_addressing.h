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

    bool rehash(size_type count);

    float load_factor() const;

    bool is_prime(size_type num);

    std::vector<std::pair<bool, Key>> get_table();

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
    number_of_cells = DEFAULT_CELL_SIZE;
    maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    count = 0;
    table.reserve(DEFAULT_CELL_SIZE);
    for (size_type i = 0; i < number_of_cells; i++) {
        table.emplace_back();
    }
    for (size_type i = 0; i < number_of_cells; i++) {
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
            table[i] = other.table[i];
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
            table[i] = other.table[i];
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
    number_of_cells = cells;
    maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    count = 0;
    table.reserve(number_of_cells);
    for (size_type i = 0; i < number_of_cells; i++) {
        table.emplace_back();
    }
    for (size_type i = 0; i < number_of_cells; i++) {
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
    for (size_type i = 0; i < number_of_cells; i++) {
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
    if (contains(value)) {
        return false;
    }

    bool ret = true;
    for (size_type i = 0; i < number_of_cells; i++) {

        auto &slot = table[index];

        // If the slot has no value we can insert  the value
        if (!slot.first) {
            slot.first = true;
            slot.second = value;
            count++;

            std::cout << "Load factor " << load_factor() << std::endl;

            if (load_factor() > maximum_load_factor) {
                size_type cell_number = number_of_cells * 4;
                while (!is_prime(cell_number)) {
                    cell_number++;
                }

                ret = rehash(cell_number);
            }
            return ret;

        } else {
            hash_value++;
            index = (hash_value) % number_of_cells;
        }

    }

    return false;
}

//-------------------------------------------------------
// Name: is_prime()
// PreCondition: num should be positive
// PostCondition: returns the number is prime or not.
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::is_prime(size_type num) {
    for (size_type i = 2; i * i <= num; i++)
        if (num % i == 0) // Factor found
            return false;
    return true;
}

//-------------------------------------------------------
// Name: load_factor()
// PreCondition:
// PostCondition: return the current load factor of the table.
//---------------------------------------------------------
template<class Key, class Hash>
float HashTable<Key, Hash>::load_factor() const {
    return (float) size() / (float) table_size();
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
    if (contains(key)) {
        size_type index = position(key);
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
// Name: rehash()
// PreCondition:
// PostCondition: set the number of buckets to the specified value and
// rehash the table if the total number of buckets has
// changed. If the new number of buckets would cause the
// load factor to exceed the maximum load factor, then
// the new number of buckets is at least size() /
// max_load_factor().
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::rehash(size_type count) {

    std::cout << "Size " << size() << " count " << count << std::endl;
    //If the count is same, no need to rehash
    if (count == number_of_cells) {
        return false;
    }

    // Check for the load factor
    if (((float) size() / (float) count) > maximum_load_factor) {
        std::cout << "Invalid count\n";
        return false;
    }

    HashTable<Key> *newHashTable = new HashTable<Key>(count);

    for (size_type index = 0; index < number_of_cells; index++) {
        auto &slot = table[index];
        if (slot.first) {
            newHashTable->insert(slot.second);
        }
    }

    table.reserve(count);
    number_of_cells = count;

    for (size_type i = 0; i < count; i++) {
        auto &slot = table[i];
        slot.first = false;
    }

    for (size_type index = 0; index < count; index++) {
        auto &slot = (newHashTable->get_table())[index];
        if (slot.first) {
            insert(slot.second);
        }
    }

    delete newHashTable;
    return true;

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

template<class Key, class Hash>
std::vector<std::pair<bool, Key>> HashTable<Key, Hash>::get_table() {
    return table;
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
        if (slot.first) {
            os << i << ": ";
            os << slot.second;
            os << std::endl;
        }

    }
}

#endif  // HASHTABLE_OPEN_ADDRESSING_H
