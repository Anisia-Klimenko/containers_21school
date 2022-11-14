//
// Created by Attack Cristina on 22.09.2022.
//

#ifdef STL
#include <vector>
namespace ft = std;
#else
#include "vector.h"
#endif

#include <iostream>
#include <sstream>
#include "main.h"

#if defined(TERM) && defined(STL)
void printTitle(std::string TITLE, std::string key, T value) { std::cout << YELLOW << "[ " << TITLE << " ] " << END << std::endl; }
void printValue(std::string key, std::string value) { std::cout << GRN << key << " : " << END << value << std::endl; }
void printError(std::string key, std::string value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#elif TERM
void printValue(std::string key, std::string value) { std::cout << BLUE << key << " : " << END << value << std::endl; }
void printTitle(std::string TITLE) { std::cout << YELLOW << "[ " << TITLE << " ] " << END << std::endl; }
void printError(std::string key, std::string value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#else
void printValue(std::string key, std::string value) { std::cout << key << " : " << value << std::endl; }
void printTitle(std::string TITLE) { std::cout << "[ " << TITLE << " ] " << std::endl; }
void printError(std::string key, std::string value) { std::cerr << "[ ERROR ] : " << key << " : " << END << value << std::endl; }
#endif

template <typename T>
std::string vecToString(ft::vector<T> vec) {
    std::ostringstream out;
    typename ft::vector<T>::iterator it = vec.begin();
    for (; it != vec.end(); it++) { out << " - " << *it; }
    return out.str();
}

void testVector() {
    printTitle("----------------------------------------------");
    printTitle("|                   VECTOR                   |");
    printTitle("----------------------------------------------");

    ft::vector<std::string> vec;
    printTitle("creating empty vector");
    printValue("is empty?", std::to_string(vec.empty()));
    vec.push_back("frog");
    vec.push_back("toad");
    vec.push_back("hamburger");
    vec.push_back("caffeine");
    vec.push_back("pizza");
    printTitle("pushing some elements and iterating with iterator");
    ft::vector<std::string>::iterator it = vec.begin();
    for (; it != vec.end(); it++) {
        std::cout << " - " << *it;
    }
    std::cout << std::endl;

    printTitle("iterating with const iterator");
    ft::vector<std::string>::const_iterator cit = vec.begin();
    for (; cit != vec.end(); cit++) {
        std::cout << " - " << *cit;
    }
    std::cout << std::endl;

    printTitle("iterating with reverse_iterators");
    ft::vector<std::string>::reverse_iterator rit = vec.rbegin();
    for (; rit != vec.rend(); rit++) {
        std::cout << " - " << *rit;
    }
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("comparing the two iterators (should be the same)");
    printValue("it == cit", std::to_string(it == cit));
    printValue("it > cit ", std::to_string(it > cit));
    printValue("it < cit ", std::to_string(it < cit));
    printValue("it >= cit", std::to_string(it >= cit));
    printValue("it <= cit", std::to_string(it <= cit));

    printTitle("comparing reverse iterator with const_reverse_iterator (should be different)");
    ft::vector<std::string>::const_reverse_iterator crit = vec.rbegin();
    printValue("rit == crit", std::to_string(rit == crit));
    printValue("rit > crit ", std::to_string(rit > crit));
    printValue("rit < crit ", std::to_string(rit < crit));
    printValue("rit >= crit", std::to_string(rit >= crit));
    printValue("rit <= crit", std::to_string(rit <= crit));

    ///////////////////////////////////////////////////////////////////////////////////////////

    it = vec.begin();
    printTitle("access elements");
    printValue("third element using *(begin + 2)", *(it + 2));
    printValue("third element using operator[]", it[2]);
    printValue("return value of front()", vec.front());
    printValue("return value of back()", vec.back());

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("size, capacity, max_size");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("vector after pushing 3 new objects");
    vec.push_back("duck");
    vec.push_back("capybara");
    vec.push_back("lizard");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after pushing another object");
    vec.push_back("bruh");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after popping the last object");
    vec.pop_back();
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after resizing to 8");
    vec.resize(8);
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after resizing to 32");
    vec.resize(32);
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    ft::vector<std::string> v(8, "42");
    vec.assign(v.begin(), v.end());
    printTitle("after using assign to change contents");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    vec.insert(vec.end() - 2, "24");
    printTitle("after using insert(vec.end() - 2, \"24\") to change contents");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    vec.erase(vec.begin(), vec.begin() + 3);
    printTitle("after using erase(vec.begin(), vec.begin() + 3) to change contents");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after resizing to 4");
    vec.resize(4);
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("changing first and last element of vector using operator[]");
    vec[0] = "frorg";
    vec[3] = "dogue";
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("changing second of vector using at()");
    vec.at(1) = "21";
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    vec.reserve(42);
    printTitle("after using reserve(42)");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    ft::vector<std::string> ve;
    ve = vec;
    printTitle("after using operator=");
    printValue("vector", vecToString<std::string>(ve));
    printValue("vector size", std::to_string(ve.size()));
    printValue("vector capacity", std::to_string(ve.capacity()));
    printValue("vector max_size", std::to_string(ve.max_size()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("before swap");
    printValue("vector 1", vecToString<std::string>(ve));
    printValue("vector 2", vecToString<std::string>(vec));
    it = vec.begin();
    vec.swap(ve);
    printTitle("after swapping iterated with old iterator to make sure its valid");
    printValue("vector 1", vecToString<std::string>(ve));
    printValue("vector 2", vecToString<std::string>(vec));

    ///////////////////////////////////////////////////////////////////////////////////////////

    ft::vector<std::string> vect(vec.begin() + 1, vec.end() - 1);
    printTitle("creating vector with iterators constructor (begin() + 1, end() - 1)");
    printValue("vector", vecToString<std::string>(vect));

    printTitle("creating vector with a copy constructor");
    ft::vector<std::string> vector(vect);
    printValue("vector", vecToString<std::string>(vector));
}

int main(void) {
    // testVector();

//    ft::pair<std::string, std::string> a = ft::make_pair("el1", "el2");
//    printValue("first", a.first);
//    printValue("second", a.second);

    return 0;
}