#include <iostream>
#include <sstream>
#include "hashtable_open_addressing.h"

using std::cout, std::endl;

void test_strings();

void test_integer_1();

int main() {
    test_strings();
    test_integer_1();

    return 0;
}

void test_integer_1() {
    const int INITIAL_SIZE = 0;
    const int INITIAL_TABLE_SIZE = 11;
    const int NUMBER_OF_INPUTS = 3;
    const int NUMBER_OF_INPUTS_AFTER_REMOVE = 2;
    const int POSITION_OF_THREE = 3;
    const int INVALID_REHASH_VALUE = 1;
    const int VALID_REHASH_VALUE = 50;


    std::cout << "make an empty hash table with 11 buckets for ints" << std::endl;
    HashTable<int> table(INITIAL_TABLE_SIZE);

    if (table.size() == INITIAL_SIZE) {
        std::cout << "[PASSED] initial size test " << std::endl;
    } else {
        std::cout << "initial size test failed" << std::endl;
    }

    if (table.table_size() == INITIAL_TABLE_SIZE) {
        std::cout << "[PASSED] initial table size test" << std::endl;
    } else {
        std::cout << "initial table size test failed" << std::endl;
    }

    table.insert(5);
    table.insert(3);
    table.insert(6);

    if (table.size() == NUMBER_OF_INPUTS) {
        std::cout << "[PASSED] insert test " << std::endl;
    } else {
        std::cout << "insert test failed" << std::endl;
    }

    if (table.contains(6)) {
        std::cout << "[PASSED] contains test " << std::endl;
    } else {
        std::cout << "contains test failed" << std::endl;
    }

    if (table.load_factor() == (float) POSITION_OF_THREE / (float) INITIAL_TABLE_SIZE) {
        std::cout << "[PASSED] load factor test " << std::endl;
    } else {
        std::cout << "load factor test failed" << std::endl;
    }

    if (!table.contains(8)) {
        std::cout << "[PASSED] contains non exist test " << std::endl;
    } else {
        std::cout << "contains non exist test failed" << std::endl;
    }

    if (table.position(3) == POSITION_OF_THREE) {
        std::cout << "[PASSED] position test " << std::endl;
    } else {
        std::cout << "position test failed" << std::endl;
    }

    table.remove(8);
    if (table.size() == NUMBER_OF_INPUTS) {
        std::cout << "[PASSED] remove non exist test " << std::endl;
    } else {
        std::cout << "remove non exist test failed" << std::endl;
    }

    if (!table.rehash(INITIAL_TABLE_SIZE)) {
        std::cout << "[PASSED] rehash the same value test " << std::endl;
    } else {
        std::cout << "rehash the same value test failed" << std::endl;
    }

    if (!table.rehash(INVALID_REHASH_VALUE)) {
        std::cout << "[PASSED] rehash the invalid value test " << std::endl;
    } else {
        std::cout << "rehash the invalid value test failed" << std::endl;
    }

    if (table.rehash(VALID_REHASH_VALUE)) {
        std::cout << "[PASSED] rehash test " << std::endl;
    } else {
        std::cout << "rehash test failed" << std::endl;
    }


    table.remove(6);
    if (table.size() == NUMBER_OF_INPUTS_AFTER_REMOVE) {
        std::cout << "[PASSED] remove test" << std::endl;
    } else {
        std::cout << "remove test failed " << table.size() << std::endl;
    }

    table.make_empty();
    if (table.size() == INITIAL_SIZE) {
        std::cout << "[PASSED] make empty test " << std::endl;
    } else {
        std::cout << "make empty test failed" << std::endl;
    }


}

void test_strings() {
    // Example test case in lab document
    std::cout << "make an empty hash table with 11 buckets for strings" << std::endl;
    HashTable<std::string> table(11);

    std::cout << "initial size is " << table.size() << std::endl;
    std::cout << "initial table size is " << table.table_size() << std::endl;

    std::cout << "insert several strings" << std::endl;
    table.insert("And them who hold High Places");
    table.insert("Must be the ones to start");
    table.insert("To mold a new Reality");
    table.insert("Closer to the Heart");
    table.insert("The Blacksmith and the Artist");
    table.insert("Reflect it in their Art");
    table.insert("Forge their Creativity");
    table.insert("Closer to the Heart");
    table.insert("Philosophers and Plowmen");
    table.insert("Each must know their Part");
    table.insert("To sow a new Mentality");
    table.insert("Closer to the Heart");
    table.insert("You can be the Captain");
    table.insert("I will draw the Chart");
    table.insert("Sailing into Destiny");
    table.insert("Closer to the Heart");

    std::cout << "size is " << table.size() << std::endl;
    std::cout << "table size is " << table.table_size() << std::endl;

    {
        std::cout << "print the table" << std::endl;
        std::stringstream ss;
        table.print_table(ss);
        std::cout << ss.str() << std::endl;
    }

    std::cout << "remove \"Philosophers and Plowmen\"" << std::endl;
    table.remove("Philosophers and Plowmen");
    std::cout << "remove \"Each must know their Part\"" << std::endl;
    table.remove("Each must know their Part");

    std::cout << "size is " << table.size() << std::endl;
    std::cout << "table size is " << table.table_size() << std::endl;

    {
        std::cout << "print the table" << std::endl;
        std::stringstream ss;
        table.print_table(ss);
        std::cout << ss.str() << std::endl;
    }

    std::cout << "find \"The Blacksmith and the Artist\"" << std::endl;
    size_t index = table.position("The Blacksmith and the Artist");
    std::cout << " ==> cell " << index << std::endl;

    std::cout << "make the table empty" << std::endl;
    table.make_empty();

    std::cout << "size is " << table.size() << std::endl;
    std::cout << "table size is " << table.table_size() << std::endl;

    {
        std::cout << "print the table" << std::endl;
        std::stringstream ss;
        table.print_table(ss);
        std::cout << ss.str() << std::endl;
    }

}