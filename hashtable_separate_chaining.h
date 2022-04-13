#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <stdexcept>
#include <functional>
#include <iostream>

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
    size_type number_of_buckets;
    float maximum_load_factor;

    // The pointer to the hash table
    std::list<Key> *table;

    // Constants
    const size_type DEFAULT_BUCKET_SIZE = 11;
    const float DEFAULT_MAX_LOAD_FACTOR = 1.0f;

    bool is_prime(size_type num);

public:
    HashTable();

    HashTable(const HashTable &other);

    ~HashTable();

    HashTable &operator=(const HashTable &other);

    HashTable(size_type buckets);

    bool is_empty() const;

    size_t size() const;

    void make_empty();

    bool insert(const value_type &value);

    size_t remove(const key_type &key);

    bool contains(const key_type &key);

    size_t bucket_count() const;

    size_t bucket_size(size_t n) const;

    size_t bucket(const key_type &key) const;

    float load_factor() const;

    float max_load_factor() const;

    void max_load_factor(float mlf);

    void rehash(size_type count);

    void print_table(std::ostream &os = std::cout) const;

    // Optional
//     HashTable(HashTable&& other);
//     HashTable& operator=(HashTable&& other);
//     bool insert(value_type&& value);
};

//-------------------------------------------------------
// Default constructor
//
// PreCondition:
// PostCondition:
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable() {
    this->number_of_buckets = DEFAULT_BUCKET_SIZE;
    this->maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    table = new std::list<Key>[DEFAULT_BUCKET_SIZE];
}

//-------------------------------------------------------
// Copy constructor
// PreCondition:
// PostCondition:
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(const HashTable &other) {
    // Clear the content
    delete[] table;

    number_of_buckets = other.number_of_buckets;
    maximum_load_factor = other.maximum_load_factor;

    // Create a new table
    table = new std::list<Key>[number_of_buckets];

    // copy values
    for (int i = 0; i < number_of_buckets; i++) {
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
    delete[] table;

    number_of_buckets = other.number_of_buckets;
    maximum_load_factor = other.maximum_load_factor;

    // Create a new table
    table = new std::list<Key>[number_of_buckets];

    // copy values
    for (int i = 0; i < number_of_buckets; i++) {
        this->table[i] = other.table[i];
    }
    return *this;
}

//-------------------------------------------------------
// Construct a table with fix number of buckets
// Name: CircleArea
// PreCondition:
// PostCondition:
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::HashTable(size_type buckets) {
    this->number_of_buckets = buckets;
    this->maximum_load_factor = DEFAULT_MAX_LOAD_FACTOR;
    table = new std::list<Key>[number_of_buckets];
}

//-------------------------------------------------------
// Default destructor
// Name: ~HashTable()
// PreCondition:
// PostCondition: clear the hashtable
//---------------------------------------------------------
template<class Key, class Hash>
HashTable<Key, Hash>::~HashTable() {
    delete[] table;
}

//-------------------------------------------------------
// Name: is_empty()
// PreCondition:
// PostCondition: Returns true if the table is empty.
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::is_empty() const {
    for (size_type i = 0; i < number_of_buckets; ++i) {
        if (this->table[i].size() != 0) {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------
// Name: size()
// PreCondition:
// PostCondition: returns the number of values in the table.
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::size() const {
    size_type sum{};
    for (size_type i = 0; i < number_of_buckets; ++i) {
        if (this->table[i].size() != 0) {
            sum += table[i].size();
        }
    }

    return sum;
}

//-------------------------------------------------------
// Name: make_empty()
// PreCondition:
// PostCondition: remove all values from the table. Do not change the
// number of buckets. Do not change the maximum load factor.
//---------------------------------------------------------
template<class Key, class Hash>
void HashTable<Key, Hash>::make_empty() {
    for (size_type i = 0; i < number_of_buckets; i++) {
        this->table[i].clear();
    }
}

//-------------------------------------------------------
// Name: insert()
// PreCondition:  the value should be not null
// PostCondition: insert the given value reference into the table,
// rehashing only if the maximum load factor is
// exceeded, return true if insert was successful (false
// if item already exists).
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::insert(const value_type &value) {
    size_type hash_value = Hash{}(value);
    size_type index = hash_value % number_of_buckets;

    if (this->contains(value)) {
        return false;
    }

    table[index].push_back(value);

    if (this->load_factor() > maximum_load_factor) {
        // Find the next prime
        size_type bucket_number = number_of_buckets * 2;
        while (!is_prime(bucket_number)) {
            bucket_number++;
        }

        rehash(bucket_number);
    }

    return true;

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
// Name: remove()
// PreCondition: the key shouldn't be null
// PostCondition: remove the specified value from the table, return
// number of elements removed (0 or 1).
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::remove(const key_type &key) {
    size_type hash_value = Hash{}(key);
    size_type index = hash_value % number_of_buckets;

    // find the key in (index)th list
    typename std::list<Key>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key) {
            break;
        }
    }

    // if key is found in hash table, remove it
    if (i != table[index].end()) {
        table[index].erase(i);
        return 1;
    }
    return 0;

}

//-------------------------------------------------------
// Name: CircleArea
// PreCondition:  the key shouldn't be null
// PostCondition: returns Boolean true if the specified value is in the
// table.
//---------------------------------------------------------
template<class Key, class Hash>
bool HashTable<Key, Hash>::contains(const key_type &key) {
    size_type hash_value = Hash{}(key);
    size_type index = hash_value % number_of_buckets;

    // find the key in (index)th list
    typename std::list<Key>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key) {
            return true;
        }
    }

//    if (i != table[index].end()) {
//        return true;
//    }
    return false;
}

//-------------------------------------------------------
// Name: bucket_count()
// PreCondition:
// PostCondition: return the number of buckets in the table.
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::bucket_count() const {
    return number_of_buckets;
}

//-------------------------------------------------------
// Name: bucket_size()
// PreCondition:  index of the bucket should be within the range of 0 and bucket size
// PostCondition: return the number of values in the specified bucket
// (by index); throw std::out_of_range if the bucket
// index is out of bounds of the table.
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::bucket_size(size_t n) const {
    if (n < 0 || n >= number_of_buckets) throw std::out_of_range("Value is out of range");
    return table[n].size();

}

//-------------------------------------------------------
// Name: bucket()
// PreCondition:  Key should be not null value
// PostCondition: return the index of the bucket that contains the
// specified value (or would contain it, if it existed).
//---------------------------------------------------------
template<class Key, class Hash>
size_t HashTable<Key, Hash>::bucket(const key_type &key) const {
    size_type hash_value = Hash{}(key);
    size_type index = hash_value % number_of_buckets;
    return index;
}

//-------------------------------------------------------
// Name: load_factor()
// PreCondition:
// PostCondition: return the current load factor of the table.
//---------------------------------------------------------
template<class Key, class Hash>
float HashTable<Key, Hash>::load_factor() const {
    return (float) size() / (float) bucket_count();
}

//-------------------------------------------------------
// Name: max_load_factor())
// PreCondition:
// PostCondition: return the current maximum load factor of the table.
//---------------------------------------------------------
template<class Key, class Hash>
float HashTable<Key, Hash>::max_load_factor() const {
    return maximum_load_factor;
}

//-------------------------------------------------------
// Name: max_load_factor()
// PreCondition:
// PostCondition: set the maximum load factor of the table, forces a
// rehash if the new maximum is less than the current
// load factor, throws std::invalid_argument if the
// input is invalid.
//---------------------------------------------------------
template<class Key, class Hash>
void HashTable<Key, Hash>::max_load_factor(float mlf) {
    maximum_load_factor = mlf;
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
void HashTable<Key, Hash>::rehash(HashTable::size_type count) {
    std::cout << "rehashing\n";

    //If the count is same, no need to rehash
    if (count == this->number_of_buckets) {
        return;
    }

    // Check for the load factor
    if (((float) size() / count) > maximum_load_factor) {
        std::cout << "Invalid count\n";
        return;
    }

    // create a new hash table and copy values
    HashTable<Key> *newHashTable = new HashTable<Key>(count);
    newHashTable->max_load_factor(maximum_load_factor);
    // std::list<Key> *table2 = new std::list<Key>[count];

    for (size_type index = 0; index < this->number_of_buckets; ++index) {
        typename std::list<Key>::iterator i;
        for (i = table[index].begin(); i != table[index].end(); i++) {
            newHashTable->insert(*i);
        }
    }

    // Clear table;
    delete[] table;

    this->number_of_buckets = newHashTable->bucket_count();
    table = new std::list<Key>[this->number_of_buckets];

    this->table = new std::list<Key>[count];
    for (size_type index = 0; index < this->number_of_buckets; ++index) {
        typename std::list<Key>::iterator i;
        for (i = newHashTable->table[index].begin(); i != newHashTable->table[index].end(); i++) {
            this->insert(*i);
        }
    }

    delete newHashTable;

}

//-------------------------------------------------------
// Name: print_table()
// PreCondition:
// PostCondition: pretty print the table. Required to exist and
// produce reasonable output, the empty table should
// print “<empty>\n”, but the format of the output is
// not graded.
//---------------------------------------------------------
template<class Key, class Hash>
void HashTable<Key, Hash>::print_table(std::ostream &os) const {
    if (is_empty()) {
        os << "<empty>\n";
        return;
    }
    for (size_type i = 0; i < number_of_buckets; i++) {
        if (table[i].size() == 0) {
            continue;
        }
        os << i << ": [";
        bool first = true;
        for (auto x : table[i]) {
            if (first) {
                os << x;
                first = false;
            } else {
                os << ", " << x;
            }
        }
        os << "]" << std::endl;
    }
}

#endif  // HASHTABLE_SEPARATE_CHAINING_H
